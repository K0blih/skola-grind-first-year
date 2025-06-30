// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// Image transformation from RGB to BW schema. 
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include "cuda_img.h"

// Demo kernel to transform RGB color schema to BW schema
__global__ void kernel_grayscale( CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img )
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    if ( l_y >= t_color_cuda_img.m_size.y ) return;
    if ( l_x >= t_color_cuda_img.m_size.x ) return;

    // Get point from color picture
    uchar3 l_bgr = t_color_cuda_img.m_p_uchar3[ l_y * t_color_cuda_img.m_size.x + l_x ];

    // Store BW point to new image
    t_bw_cuda_img.m_p_uchar1[ l_y * t_bw_cuda_img.m_size.x + l_x ].x = l_bgr.x * 0.11 + l_bgr.y * 0.59 + l_bgr.z * 0.30;
}

void cu_run_grayscale( CudaImg t_color_cuda_img, CudaImg t_bw_cuda_img )
{
    cudaError_t l_cerr;

    // Grid creation, size of grid must be equal or greater than images
    int l_block_size = 16;
    dim3 l_blocks( ( t_color_cuda_img.m_size.x + l_block_size - 1 ) / l_block_size, ( t_color_cuda_img.m_size.y + l_block_size - 1 ) / l_block_size );
    dim3 l_threads( l_block_size, l_block_size );
    kernel_grayscale<<< l_blocks, l_threads >>>( t_color_cuda_img, t_bw_cuda_img );

    if ( ( l_cerr = cudaGetLastError() ) != cudaSuccess )
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( l_cerr ) );

    cudaDeviceSynchronize();
}

__global__ void kernel_insert_image(CudaImg t_big_img, CudaImg t_small_img, int2 t_pos)
{
    // Calculate global thread coordinates
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    // Check if within small image bounds
    if (x < t_small_img.m_size.x && y < t_small_img.m_size.y) 
    {
        // Calculate target position in big image
        int targetX = x + t_pos.x;
        int targetY = y + t_pos.y;
        
        // Check if target position is within big image bounds
        if (targetX < t_big_img.m_size.x && targetY < t_big_img.m_size.y) 
        {
            // Copy pixel from small image to big image
            // We'll handle both RGB and grayscale cases
            if (t_big_img.m_p_uchar3 && t_small_img.m_p_uchar3) {
                // RGB to RGB
                t_big_img.at3(targetY, targetX) = t_small_img.at3(y, x);
            }
            else if (t_big_img.m_p_uchar1 && t_small_img.m_p_uchar1) {
                // Grayscale to Grayscale
                t_big_img.at1(targetY, targetX) = t_small_img.at1(y, x);
            }
            else if (t_big_img.m_p_uchar3 && t_small_img.m_p_uchar1) {
                // Grayscale to RGB
                uchar1 pixel = t_small_img.at1(y, x);
                uchar3 color;
                color.x = color.y = color.z = pixel.x;
                t_big_img.at3(targetY, targetX) = color;
            }
        }
    }
}

// Function to be called from main program
void cu_insert_image(CudaImg t_cuda_big_img, CudaImg t_cuda_small_img, int2 t_pos)
{
    // Define block and grid sizes
    dim3 blockSize(16, 16);
    dim3 gridSize(
        (t_cuda_small_img.m_size.x + blockSize.x - 1) / blockSize.x,
        (t_cuda_small_img.m_size.y + blockSize.y - 1) / blockSize.y
    );
    
    // Launch the kernel
    kernel_insert_image<<<gridSize, blockSize>>>(t_cuda_big_img, t_cuda_small_img, t_pos);
    
    // Wait for GPU to finish
    cudaDeviceSynchronize();
}

__global__ void kernel_insert_image_with_mask(CudaImg t_big_img, CudaImg t_small_img, int2 t_position, uchar3 t_mask)
{
    // X,Y coordinates and check image dimensions
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    
    if (l_y >= t_small_img.m_size.y || l_x >= t_small_img.m_size.x)
        return;
    
    // Calculate position in the big image
    int big_y = t_position.y + l_y;
    int big_x = t_position.x + l_x;
    
    // Check if the position is within the big image boundaries
    if (big_y >= t_big_img.m_size.y || big_x >= t_big_img.m_size.x)
        return;
    
    // Get the pixel values
    uchar3 small_pixel = t_small_img.at3(l_y, l_x);
    uchar3 big_pixel = t_big_img.at3(big_y, big_x);
    
    // Apply mask (either 0/1 multiplication or 0/255 AND operation)
    uchar3 result;
    
    // Check if mask is binary (0/1) or byte (0/255)
    if (t_mask.x <= 1 && t_mask.y <= 1 && t_mask.z <= 1) {
        // Using multiplication for 0/1 mask
        result.x = big_pixel.x * (1 - t_mask.x) + small_pixel.x * t_mask.x;
        result.y = big_pixel.y * (1 - t_mask.y) + small_pixel.y * t_mask.y;
        result.z = big_pixel.z * (1 - t_mask.z) + small_pixel.z * t_mask.z;
    } else {
        // Using AND for 0/255 mask
        result.x = (big_pixel.x & ~t_mask.x) | (small_pixel.x & t_mask.x);
        result.y = (big_pixel.y & ~t_mask.y) | (small_pixel.y & t_mask.y);
        result.z = (big_pixel.z & ~t_mask.z) | (small_pixel.z & t_mask.z);
    }
    
    // Save the result
    t_big_img.at3(big_y, big_x) = result;
}

// Function to insert image with color mask - runs on CPU
void cu_insert_image_with_mask(CudaImg t_cuda_big_img, CudaImg t_cuda_small_img, int2 t_pos, uchar3 t_mask)
{
    // Grid creation with calculated size
    cudaError_t l_cerr;
    
    // Grid size
    dim3 l_blocks((t_cuda_small_img.m_size.x + 15) / 16, (t_cuda_small_img.m_size.y + 15) / 16);
    dim3 l_threads(16, 16);
    
    // Call the kernel
    kernel_insert_image_with_mask<<<l_blocks, l_threads>>>(t_cuda_big_img, t_cuda_small_img, t_pos, t_mask);
    
    // Wait for all threads to complete
    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));
    
    cudaDeviceSynchronize();
}

// Implementation of image swap kernel (swaps regions between two images)
__global__ void kernel_swap_image_quadrants(CudaImg t_dest_img, CudaImg t_src_img1, CudaImg t_src_img2, int2 t_quadrant1, int2 t_quadrant2)
{
    // X,Y coordinates
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;
    
    // Calculate the quadrant size (half of each source image)
    int quad_width = t_src_img1.m_size.x / 2;
    int quad_height = t_src_img1.m_size.y / 2;
    
    if (l_y >= quad_height || l_x >= quad_width)
        return;
    
    // Calculate source positions
    int src1_y = t_quadrant1.y * quad_height + l_y;
    int src1_x = t_quadrant1.x * quad_width + l_x;
    
    int src2_y = t_quadrant2.y * quad_height + l_y;
    int src2_x = t_quadrant2.x * quad_width + l_x;
    
    // Calculate destination positions (swap quarters)
    int dest1_y = t_quadrant1.y * quad_height + l_y;
    int dest1_x = t_quadrant1.x * quad_width + l_x;
    
    int dest2_y = t_quadrant2.y * quad_height + l_y;
    int dest2_x = t_quadrant2.x * quad_width + l_x;
    
    // Perform the swap (copy source 1 to destination 2, source 2 to destination 1)
    t_dest_img.at3(dest2_y, dest2_x) = t_src_img1.at3(src1_y, src1_x);
    t_dest_img.at3(dest1_y, dest1_x) = t_src_img2.at3(src2_y, src2_x);
}

// Function to swap image quadrants - runs on CPU
void cu_swap_image_quadrants(CudaImg t_dest_img, CudaImg t_src_img1, CudaImg t_src_img2, int2 t_quadrant1, int2 t_quadrant2)
{
    // Grid creation with calculated size
    cudaError_t l_cerr;
    
    // Calculate quadrant size
    int quad_width = t_src_img1.m_size.x / 2;
    int quad_height = t_src_img1.m_size.y / 2;
    
    // Grid size (for one quadrant)
    dim3 l_blocks((quad_width + 15) / 16, (quad_height + 15) / 16);
    dim3 l_threads(16, 16);
    
    // Call the kernel
    kernel_swap_image_quadrants<<<l_blocks, l_threads>>>(t_dest_img, t_src_img1, t_src_img2, t_quadrant1, t_quadrant2);
    
    // Wait for all threads to complete
    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));
    
    cudaDeviceSynchronize();
}

__global__ void kernel_resize_nn_uchar3(uchar3* input, uchar3* output, int inW, int inH, int outW, int outH) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x < outW && y < outH) {
        float srcX = (float)x * inW / outW;
        float srcY = (float)y * inH / outH;
        int ix = min(int(srcX), inW - 1);
        int iy = min(int(srcY), inH - 1);
        output[y * outW + x] = input[iy * inW + ix];
    }
}

__global__ void kernel_resize_nn_uchar1(uchar1* input, uchar1* output, int inW, int inH, int outW, int outH) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x < outW && y < outH) {
        float srcX = (float)x * inW / outW;
        float srcY = (float)y * inH / outH;
        int ix = min(int(srcX), inW - 1);
        int iy = min(int(srcY), inH - 1);
        output[y * outW + x].x = input[iy * inW + ix].x;
    }
}

__global__ void kernel_resize_bilinear_uchar3(uchar3* input, uchar3* output, int inW, int inH, int outW, int outH) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < outW && y < outH) {
        float gx = (float)x * inW / outW;
        float gy = (float)y * inH / outH;
        int ix = floor(gx);
        int iy = floor(gy);
        float dx = gx - ix;
        float dy = gy - iy;
        ix = min(ix, inW - 2);
        iy = min(iy, inH - 2);
        uchar3 c00 = input[iy * inW + ix];
        uchar3 c10 = input[iy * inW + ix + 1];
        uchar3 c01 = input[(iy + 1) * inW + ix];
        uchar3 c11 = input[(iy + 1) * inW + ix + 1];
        float3 top = make_float3(c00.x + dx * (c10.x - c00.x), c00.y + dx * (c10.y - c00.y), c00.z + dx * (c10.z - c00.z));
        float3 bottom = make_float3(c01.x + dx * (c11.x - c01.x), c01.y + dx * (c11.y - c01.y), c01.z + dx * (c11.z - c01.z));
        float3 value = make_float3(top.x + dy * (bottom.x - top.x), top.y + dy * (bottom.y - top.y), top.z + dy * (bottom.z - top.z));
        output[y * outW + x] = make_uchar3((unsigned char)value.x, (unsigned char)value.y, (unsigned char)value.z);
    }
    }

__global__ void kernel_resize_bilinear_uchar1(uchar1* input, uchar1* output, int inW, int inH, int outW, int outH) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < outW && y < outH) {
        float gx = (float)x * inW / outW;
        float gy = (float)y * inH / outH;
        int ix = floor(gx);
        int iy = floor(gy);
        float dx = gx - ix;
        float dy = gy - iy;
        ix = min(ix, inW - 2);
        iy = min(iy, inH - 2);
        unsigned char v00 = input[iy * inW + ix].x;
        unsigned char v10 = input[iy * inW + ix + 1].x;
        unsigned char v01 = input[(iy + 1) * inW + ix].x;
        unsigned char v11 = input[(iy + 1) * inW + ix + 1].x;
        float top = v00 + dx * (v10 - v00);
        float bottom = v01 + dx * (v11 - v01);
        unsigned char value = (unsigned char)(top + dy * (bottom - top));
        output[y * outW + x].x = value;
    }
}

void cu_resize(const CudaImg& in_img, CudaImg& out_img, bool bilinear) {
    int inW = in_img.m_size.x;
    int inH = in_img.m_size.y;
    int outW = out_img.m_size.x;
    int outH = out_img.m_size.y;
    dim3 blockDim(16, 16);
    dim3 gridDim((outW + blockDim.x - 1) / blockDim.x, (outH + blockDim.y - 1) / blockDim.y);

    if (bilinear) {
        if (in_img.m_p_uchar3 && out_img.m_p_uchar3) {
            kernel_resize_bilinear_uchar3<<<gridDim, blockDim>>>(in_img.m_p_uchar3, out_img.m_p_uchar3, inW, inH, outW, outH);
        } 
        else if (in_img.m_p_uchar1 && out_img.m_p_uchar1) {
            kernel_resize_bilinear_uchar1<<<gridDim, blockDim>>>(in_img.m_p_uchar1, out_img.m_p_uchar1, inW, inH, outW, outH);
        }
    } 
    else {
        if (in_img.m_p_uchar3 && out_img.m_p_uchar3) {
            kernel_resize_nn_uchar3<<<gridDim, blockDim>>>(in_img.m_p_uchar3, out_img.m_p_uchar3,inW, inH, outW, outH);
        } 
        else if (in_img.m_p_uchar1 && out_img.m_p_uchar1) {
            kernel_resize_nn_uchar1<<<gridDim, blockDim>>>(in_img.m_p_uchar1, out_img.m_p_uchar1,inW, inH, outW, outH);
        }
    }

    cudaDeviceSynchronize();
}

// Example usage in main.cpp for resize:
// // Define target size or compute scale factor
// cv::Mat resized(targetW, targetH, input.type());
// CudaImg inCuda(input);
// CudaImg resCuda(resized);
// // Nearest neighbour
// cu_resize(inCuda, resCuda, false);
// cv::imshow("Resized NN", resized);
// // Bilinear interpolation
// cu_resize(inCuda, resCuda, true);
// cv::imshow("Resized Bilinear", resized);

__global__ void kernel_remove_color_channel(CudaImg t_cuda_img, int number){
    int l_y = blockDim.y * blockIdx.y + threadIdx.y;
    int l_x = blockDim.x * blockIdx.x + threadIdx.x;

    if (l_x >= t_cuda_img.m_size.x || l_y >= t_cuda_img.m_size.y){ 
        return;
    }

    uchar3 here = t_cuda_img.m_p_uchar3[l_y * t_cuda_img.m_size.x + l_x];

    if (number == 1){
        here.x = 0;
    }else if (number == 2){
        here.x = 0;
        here.y = 0;
    }else if (number == 3){
        here.x = 0;
        here.y = 0;
        here.z = 0;
    }

    t_cuda_img.m_p_uchar3[l_y * t_cuda_img.m_size.x + l_x] = here;
}

void cu_run_remove_color_channel(CudaImg t_cuda_img, int number){
    cudaError_t l_cerr;

    int t_block_size = 16;

    dim3 l_grid((t_cuda_img.m_size.x + t_block_size - 1) / t_block_size,

        (t_cuda_img.m_size.y + t_block_size - 1) / t_block_size);

    dim3 l_threads(t_block_size, t_block_size);

    kernel_remove_color_channel <<< l_grid, l_threads >>> (t_cuda_img, number);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess) {

        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    }

    cudaDeviceSynchronize();

}

__global__ void kernel_mirror_image(CudaImg t_src_img, CudaImg t_dst_img, int mirror_direction)
{
    // Calculate global thread coordinates
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    // Check if within image bounds
    if (x < t_src_img.m_size.x && y < t_src_img.m_size.y)
    {
        // Calculate mirrored coordinates
        int mirrored_x = x;
        int mirrored_y = y;
        
        if (mirror_direction == 1) {
            // Horizontal mirroring (flip along y-axis)
            mirrored_x = t_src_img.m_size.x - 1 - x;
        } else if (mirror_direction == 2) {
            // Vertical mirroring (flip along x-axis)
            mirrored_y = t_src_img.m_size.y - 1 - y;
        }
        
        // Copy the pixel from source to destination (with mirroring)
        // Handle different image types (color or grayscale)
        if (t_src_img.m_p_uchar3 && t_dst_img.m_p_uchar3) {
            // RGB to RGB
            t_dst_img.at3(y, x) = t_src_img.at3(mirrored_y, mirrored_x);
        }
        else if (t_src_img.m_p_uchar1 && t_dst_img.m_p_uchar1) {
            // Grayscale to Grayscale
            t_dst_img.at1(y, x) = t_src_img.at1(mirrored_y, mirrored_x);
        }
        else if (t_dst_img.m_p_uchar3 && t_src_img.m_p_uchar1) {
            // Grayscale to RGB
            uchar1 pixel = t_src_img.at1(mirrored_y, mirrored_x);
            uchar3 color;
            color.x = color.y = color.z = pixel.x;
            t_dst_img.at3(y, x) = color;
        }
        else if (t_dst_img.m_p_uchar1 && t_src_img.m_p_uchar3) {
            // RGB to Grayscale - use a simple average for conversion
            uchar3 pixel = t_src_img.at3(mirrored_y, mirrored_x);
            uchar1 gray;
            gray.x = (pixel.x + pixel.y + pixel.z) / 3;
            t_dst_img.at1(y, x) = gray;
        }
    }
}

// Function to be called from main program - mirrors the image
void cu_mirror_image(CudaImg &t_src_img, CudaImg &t_dst_img, int mirror_direction)
{
    // Define block and grid sizes
    dim3 blockSize(16, 16);
    dim3 gridSize(
        (t_src_img.m_size.x + blockSize.x - 1) / blockSize.x,
        (t_src_img.m_size.y + blockSize.y - 1) / blockSize.y
    );
    
    // Launch the kernel
    kernel_mirror_image<<<gridSize, blockSize>>>(t_src_img, t_dst_img, mirror_direction);
    
    // Wait for GPU to finish
    cudaDeviceSynchronize();
}