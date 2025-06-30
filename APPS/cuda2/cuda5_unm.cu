// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage wit unified memory.
// Image transformation from RGB to BW schema. 
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include "cuda_img.h"

#include "font24x40_lsb.h"

// Demo kernel to create chess board
__global__ void kernel_chessboard( CudaImg t_color_cuda_img )
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if ( l_y >= t_color_cuda_img.m_size.y ) return;
    if ( l_x >= t_color_cuda_img.m_size.x ) return;

    unsigned char b_or_w = 255 * ( ( blockIdx.x + blockIdx.y ) & 1 );

    // Store point into image
    t_color_cuda_img.m_p_uchar3[ l_y * t_color_cuda_img.m_size.x + l_x ] = { b_or_w, b_or_w, b_or_w };
}

void cu_create_chessboard( CudaImg t_color_cuda_img, int t_square_size )
{
    cudaError_t l_cerr;

    // Grid creation, size of grid must be equal or greater than images
    dim3 l_blocks( ( t_color_cuda_img.m_size.x + t_square_size - 1 ) / t_square_size,
                   ( t_color_cuda_img.m_size.y + t_square_size - 1 ) / t_square_size );
    dim3 l_threads( t_square_size, t_square_size );
    kernel_chessboard<<< l_blocks, l_threads >>>( t_color_cuda_img );

    if ( ( l_cerr = cudaGetLastError() ) != cudaSuccess )
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( l_cerr ) );

    cudaDeviceSynchronize();
}

// -----------------------------------------------------------------------------------------------

// Demo kernel to create picture with alpha channel gradient
__global__ void kernel_alphaimg( CudaImg t_color_cuda_img, uchar3 t_color )
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if ( l_y >= t_color_cuda_img.m_size.y ) return;
    if ( l_x >= t_color_cuda_img.m_size.x ) return;

    int l_diagonal = sqrtf( t_color_cuda_img.m_size.x * t_color_cuda_img.m_size.x + t_color_cuda_img.m_size.y * t_color_cuda_img.m_size.y );
    int l_dx = l_x - t_color_cuda_img.m_size.x / 2;
    int l_dy = l_y - t_color_cuda_img.m_size.y / 2;
    int l_dxy = sqrtf( l_dx * l_dx + l_dy * l_dy ) - l_diagonal / 2;

    // Store point into image
    t_color_cuda_img.m_p_uchar4[ l_y * t_color_cuda_img.m_size.x + l_x ] =
        { t_color.x, t_color.y, t_color.z, ( unsigned char ) ( 255 - 255 * l_dxy / ( l_diagonal / 2 ) ) };
}

void cu_create_alphaimg( CudaImg t_color_cuda_img, uchar3 t_color )
{
    cudaError_t l_cerr;

    // Grid creation, size of grid must be equal or greater than images
    int l_block_size = 32;
    dim3 l_blocks( ( t_color_cuda_img.m_size.x + l_block_size - 1 ) / l_block_size,
                   ( t_color_cuda_img.m_size.y + l_block_size - 1 ) / l_block_size );
    dim3 l_threads( l_block_size, l_block_size );
    kernel_alphaimg<<< l_blocks, l_threads >>>( t_color_cuda_img, t_color );

    if ( ( l_cerr = cudaGetLastError() ) != cudaSuccess )
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( l_cerr ) );

    cudaDeviceSynchronize();
}

// Kernel for inserting small BGRA image into a 3-channel BGR target
__global__ void kernel_insertimage(CudaImg t_big_cuda_pic, CudaImg t_small_cuda_pic, int2 t_position) {
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    
    if (l_y >= t_small_cuda_pic.m_size.y) return;
    if (l_x >= t_small_cuda_pic.m_size.x) return;
    
    int l_by = l_y + t_position.y;
    int l_bx = l_x + t_position.x;
    if (l_by >= t_big_cuda_pic.m_size.y || l_by < 0) return;
    if (l_bx >= t_big_cuda_pic.m_size.x || l_bx < 0) return;
    
    // Handle both 3-channel and 4-channel source images
    uchar3 l_bg = t_big_cuda_pic.at3(l_by, l_bx);
    uchar3 l_fg;
    float alpha = 1.0f; // Default to opaque
    
    if (t_small_cuda_pic.m_p_uchar4) {
        uchar4 fg_pixel = t_small_cuda_pic.at4(l_y, l_x);
        l_fg = make_uchar3(fg_pixel.x, fg_pixel.y, fg_pixel.z);
        alpha = fg_pixel.w / 255.0f; // Normalize alpha
    } else {
        l_fg = t_small_cuda_pic.at3(l_y, l_x);
    }
    
    // Alpha blending
    uchar3 l_result;
    l_result.x = l_fg.x * alpha + l_bg.x * (1 - alpha);
    l_result.y = l_fg.y * alpha + l_bg.y * (1 - alpha);
    l_result.z = l_fg.z * alpha + l_bg.z * (1 - alpha);
    
    t_big_cuda_pic.at3(l_by, l_bx) = l_result;
}

// Function to handle image insertion with channel detection
void cu_insertimage(CudaImg &t_big_cuda_pic, CudaImg &t_small_cuda_pic, int2 t_position)
{
    cudaError_t l_cerr;
    
    // Grid creation, size of grid must be equal or greater than small image
    int l_block_size = 32;
    dim3 l_blocks((t_small_cuda_pic.m_size.x + l_block_size - 1) / l_block_size,
                 (t_small_cuda_pic.m_size.y + l_block_size - 1) / l_block_size);
    dim3 l_threads(l_block_size, l_block_size);
    
    kernel_insertimage<<<l_blocks, l_threads>>>(t_big_cuda_pic, t_small_cuda_pic, t_position);
    
    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));
    
    cudaDeviceSynchronize();
}

// -----------------------------------------------------------------------------------------------

// t_direction = 1 -> 90° clockwise
// t_direction = -1 -> 90° counter-clockwise
__global__ void kernel_rotate90_4ch(CudaImg t_img_in, CudaImg t_img_out, int t_direction)
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if (l_y >= t_img_in.m_size.y) return;
    if (l_x >= t_img_in.m_size.x) return;

    // Calculate new coordinates after rotation
    int l_new_x, l_new_y;
    
    if (t_direction == 1) {
        // 90° clockwise: (x,y) -> (y, width-1-x)
        l_new_x = l_y;
        l_new_y = t_img_in.m_size.x - 1 - l_x;
    } else {
        // 90° counter-clockwise: (x,y) -> (height-1-y, x)
        l_new_x = t_img_in.m_size.y - 1 - l_y;
        l_new_y = l_x;
    }

    // Get source pixel using at4
    uchar4 l_color = t_img_in.at4(l_y, l_x);
    
    // Place it in rotated position in output image using at4
    t_img_out.at4(l_new_y, l_new_x) = l_color;
}

// Kernel for 3-channel image rotation
__global__ void kernel_rotate90(CudaImg t_img_in, CudaImg t_img_out, int t_direction)
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if (l_y >= t_img_in.m_size.y) return;
    if (l_x >= t_img_in.m_size.x) return;

    // Calculate new coordinates after rotation
    int l_new_x, l_new_y;
    
    if (t_direction == 1) {
        // 90° clockwise: (x,y) -> (y, width-1-x)
        l_new_x = l_y;
        l_new_y = t_img_in.m_size.x - 1 - l_x;
    } else {
        // 90° counter-clockwise: (x,y) -> (height-1-y, x)
        l_new_x = t_img_in.m_size.y - 1 - l_y;
        l_new_y = l_x;
    }

    // Get source pixel using at3
    uchar3 l_color = t_img_in.at3(l_y, l_x);
    
    // Place it in rotated position in output image using at3
    t_img_out.at3(l_new_y, l_new_x) = l_color;
}

// Function to handle the image rotation with channel detection
void cu_rotate90(CudaImg &t_cu_img, CudaImg &t_cu_img_rotated, int t_direction)
{
    cudaError_t l_cerr;

    // Grid creation, size of grid must be equal or greater than image
    int l_block_size = 32;
    dim3 l_blocks((t_cu_img.m_size.x + l_block_size - 1) / l_block_size,
                 (t_cu_img.m_size.y + l_block_size - 1) / l_block_size);
    dim3 l_threads(l_block_size, l_block_size);
    
    // Check if we're dealing with a 3-channel or 4-channel image
    // This could be determined by examining the cv::Mat type or passing an additional parameter
    // For this implementation, we'll check if m_p_uchar4 is not null
    bool is_4ch = (t_cu_img.m_p_uchar4 != nullptr);
    
    if (is_4ch) {
        kernel_rotate90_4ch<<<l_blocks, l_threads>>>(t_cu_img, t_cu_img_rotated, t_direction);
    } else {
        kernel_rotate90<<<l_blocks, l_threads>>>(t_cu_img, t_cu_img_rotated, t_direction);
    }

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

// -----------------------------------------------------------------------------------------------
// 2. Kernel to scale a 4-channel image using bilinear interpolation
__global__ void kernel_scale_4ch(CudaImg t_img_in, CudaImg t_img_out)
{
    // X,Y coordinates and check output image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if (l_y >= t_img_out.m_size.y) return;
    if (l_x >= t_img_out.m_size.x) return;

    // Calculate scaling factors
    float l_scale_x = (float)t_img_in.m_size.x / t_img_out.m_size.x;
    float l_scale_y = (float)t_img_in.m_size.y / t_img_out.m_size.y;
    
    // Calculate source position in original image
    float l_orig_x = l_x * l_scale_x;
    float l_orig_y = l_y * l_scale_y;
    
    // Get the four surrounding pixels
    int l_x0 = (int)l_orig_x;
    int l_y0 = (int)l_orig_y;
    int l_x1 = min(l_x0 + 1, (int)t_img_in.m_size.x - 1);
    int l_y1 = min(l_y0 + 1, (int)t_img_in.m_size.y - 1);
    
    // Calculate interpolation weights
    float l_dx = l_orig_x - l_x0;
    float l_dy = l_orig_y - l_y0;
    
    // Get the four surrounding colors using at4
    uchar4 l_c00 = t_img_in.at4(l_y0, l_x0);
    uchar4 l_c10 = t_img_in.at4(l_y0, l_x1);
    uchar4 l_c01 = t_img_in.at4(l_y1, l_x0);
    uchar4 l_c11 = t_img_in.at4(l_y1, l_x1);
    
    // Interpolate to get the output color
    uchar4 l_result;
    
    // Interpolate for each channel (RGB + alpha)
    // R channel
    float l_s0_r = l_c00.x * (1 - l_dx) + l_c10.x * l_dx;
    float l_s1_r = l_c01.x * (1 - l_dx) + l_c11.x * l_dx;
    l_result.x = (unsigned char)(l_s0_r * (1 - l_dy) + l_s1_r * l_dy);
    
    // G channel
    float l_s0_g = l_c00.y * (1 - l_dx) + l_c10.y * l_dx;
    float l_s1_g = l_c01.y * (1 - l_dx) + l_c11.y * l_dx;
    l_result.y = (unsigned char)(l_s0_g * (1 - l_dy) + l_s1_g * l_dy);
    
    // B channel
    float l_s0_b = l_c00.z * (1 - l_dx) + l_c10.z * l_dx;
    float l_s1_b = l_c01.z * (1 - l_dx) + l_c11.z * l_dx;
    l_result.z = (unsigned char)(l_s0_b * (1 - l_dy) + l_s1_b * l_dy);
    
    // Alpha channel
    float l_s0_a = l_c00.w * (1 - l_dx) + l_c10.w * l_dx;
    float l_s1_a = l_c01.w * (1 - l_dx) + l_c11.w * l_dx;
    l_result.w = (unsigned char)(l_s0_a * (1 - l_dy) + l_s1_a * l_dy);
    
    // Store result in output image using at4
    t_img_out.at4(l_y, l_x) = l_result;
}

// Kernel to scale a 3-channel image using bilinear interpolation
__global__ void kernel_scale(CudaImg t_img_in, CudaImg t_img_out)
{
    // X,Y coordinates and check output image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if (l_y >= t_img_out.m_size.y) return;
    if (l_x >= t_img_out.m_size.x) return;

    // Calculate scaling factors
    float l_scale_x = (float)t_img_in.m_size.x / t_img_out.m_size.x;
    float l_scale_y = (float)t_img_in.m_size.y / t_img_out.m_size.y;
    
    // Calculate source position in original image
    float l_orig_x = l_x * l_scale_x;
    float l_orig_y = l_y * l_scale_y;
    
    // Get the four surrounding pixels
    int l_x0 = (int)l_orig_x;
    int l_y0 = (int)l_orig_y;
    int l_x1 = min(l_x0 + 1, (int)t_img_in.m_size.x - 1);
    int l_y1 = min(l_y0 + 1, (int)t_img_in.m_size.y - 1);
    
    // Calculate interpolation weights
    float l_dx = l_orig_x - l_x0;
    float l_dy = l_orig_y - l_y0;
    
    // Get the four surrounding colors using at3
    uchar3 l_c00 = t_img_in.at3(l_y0, l_x0);
    uchar3 l_c10 = t_img_in.at3(l_y0, l_x1);
    uchar3 l_c01 = t_img_in.at3(l_y1, l_x0);
    uchar3 l_c11 = t_img_in.at3(l_y1, l_x1);
    
    // Interpolate to get the output color
    uchar3 l_result;
    
    // Interpolate for each channel (RGB)
    // R channel
    float l_s0_r = l_c00.x * (1 - l_dx) + l_c10.x * l_dx;
    float l_s1_r = l_c01.x * (1 - l_dx) + l_c11.x * l_dx;
    l_result.x = (unsigned char)(l_s0_r * (1 - l_dy) + l_s1_r * l_dy);
    
    // G channel
    float l_s0_g = l_c00.y * (1 - l_dx) + l_c10.y * l_dx;
    float l_s1_g = l_c01.y * (1 - l_dx) + l_c11.y * l_dx;
    l_result.y = (unsigned char)(l_s0_g * (1 - l_dy) + l_s1_g * l_dy);
    
    // B channel
    float l_s0_b = l_c00.z * (1 - l_dx) + l_c10.z * l_dx;
    float l_s1_b = l_c01.z * (1 - l_dx) + l_c11.z * l_dx;
    l_result.z = (unsigned char)(l_s0_b * (1 - l_dy) + l_s1_b * l_dy);
    
    // Store result in output image using at3
    t_img_out.at3(l_y, l_x) = l_result;
}

// Function to handle the image scaling with channel detection
void cu_scale(CudaImg &t_cu_orig, CudaImg &t_cu_scaled)
{
    cudaError_t l_cerr;

    // Grid creation, size of grid must be equal or greater than output image
    int l_block_size = 32;
    dim3 l_blocks((t_cu_scaled.m_size.x + l_block_size - 1) / l_block_size,
                 (t_cu_scaled.m_size.y + l_block_size - 1) / l_block_size);
    dim3 l_threads(l_block_size, l_block_size);
    
    // Check if we're dealing with a 3-channel or 4-channel image
    bool is_4ch = (t_cu_orig.m_p_uchar4 != nullptr);
    
    if (is_4ch) {
        kernel_scale_4ch<<<l_blocks, l_threads>>>(t_cu_orig, t_cu_scaled);
    } else {
        kernel_scale<<<l_blocks, l_threads>>>(t_cu_orig, t_cu_scaled);
    }

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

// -----------------------------------------------------------------------------------------------

// 3. Implementation of LCD font drawing
__global__ void kernel_insertChar(CudaImg big_img, int2 pos, char c, const uint32_t font[256][40]) {
    int x = threadIdx.x; // 0-23
    int y = threadIdx.y; // 0-39

    if (x >= 24 || y >= 40) return;

    uint32_t row = font[(uint8_t)c][y];

    if (row & (1 << x)) {
        int img_x = pos.x + x;
        int img_y = pos.y + y;

        if (img_x < 0 || img_y < 0 || img_x >= big_img.m_size.x || img_y >= big_img.m_size.y)
            return;
        
        if (big_img.m_p_uchar4) {
            // For 4-channel images, set black with full opacity
            big_img.at4(img_y, img_x) = make_uchar4(0, 0, 0, 255);
        }
        else if (big_img.m_p_uchar3) {
            // For 3-channel images, simple black
            big_img.at3(img_y, img_x) = make_uchar3(0, 0, 0);
        }
    }
}

void insertText(CudaImg &big_img, int2 pos, const char *text, const uint32_t font[256][40]) {
    // Allocate font data on device once
    uint32_t (*d_font)[40];
    cudaMalloc(&d_font, 256 * 40 * sizeof(uint32_t));
    cudaMemcpy(d_font, font, 256 * 40 * sizeof(uint32_t), cudaMemcpyHostToDevice);

    CudaImg d_big_img;
    size_t img_size = big_img.m_size.x * big_img.m_size.y * (big_img.m_p_uchar3 ? sizeof(uchar3) : sizeof(uchar4));
    cudaMalloc(&d_big_img.m_p_void, img_size);
    d_big_img.m_size = big_img.m_size;
    
    int2 current_pos = pos;
    while (*text) {
        // Copy image to device for each character (since it may have changed)
        cudaMemcpy(d_big_img.m_p_void, big_img.m_p_void, img_size, cudaMemcpyHostToDevice);

        dim3 block(24, 40);
        kernel_insertChar<<<1, block>>>(d_big_img, current_pos, *text, d_font);
        cudaDeviceSynchronize();

        // Copy back after each character
        cudaMemcpy(big_img.m_p_void, d_big_img.m_p_void, img_size, cudaMemcpyDeviceToHost);
        
        current_pos.x += 26;
        ++text;
    }

    // Free device memory
    cudaFree(d_big_img.m_p_void);
    cudaFree(d_font);
}