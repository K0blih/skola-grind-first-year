// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage without unified memory.
//
// Simple animation with image rotation.
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <math.h>

#include "cuda_img.h"
#include "animation.h"

// Demo kernel to create chess board
__global__ void kernel_createGradient(CudaImg colorCudaImg)
{
    // X,Y coordinates and check image dimensions
    int y = blockDim.y * blockIdx.y + threadIdx.y;
    int x = blockDim.x * blockIdx.x + threadIdx.x;
    if (y >= colorCudaImg.m_size.y) return;
    if (x >= colorCudaImg.m_size.x) return;

    int dy = x * colorCudaImg.m_size.y / colorCudaImg.m_size.x + y - colorCudaImg.m_size.y;
    unsigned char color = 255 * abs(dy) / colorCudaImg.m_size.y;

    uchar3 bgr = (dy < 0) ? (uchar3){color, 255 - color, 0} : (uchar3){0, 255 - color, color};

    // Store point into image
    colorCudaImg.m_p_uchar3[y * colorCudaImg.m_size.x + x] = bgr;
}

// -----------------------------------------------------------------------------------------------

// Demo kernel to create picture with alpha channel gradient
__global__ void kernel_insertImage(CudaImg bigCudaImg, CudaImg smallCudaPic, int2 position)
{
    // X,Y coordinates and check image dimensions
    int y = blockDim.y * blockIdx.y + threadIdx.y;
    int x = blockDim.x * blockIdx.x + threadIdx.x;
    if (y >= smallCudaPic.m_size.y) return;
    if (x >= smallCudaPic.m_size.x) return;
    int by = y + position.y;
    int bx = x + position.x;
    if (by >= bigCudaImg.m_size.y || by < 0) return;
    if (bx >= bigCudaImg.m_size.x || bx < 0) return;

    // Get point from small image
    uchar4 fgBgra = smallCudaPic.m_p_uchar4[y * smallCudaPic.m_size.x + x];
    uchar3 bgBgr = bigCudaImg.m_p_uchar3[by * bigCudaImg.m_size.x + bx];
    uchar3 bgr = {0, 0, 0};

    // compose point from small and big image according alpha channel
    bgr.x = fgBgra.x * fgBgra.w / 255 + bgBgr.x * (255 - fgBgra.w) / 255;
    bgr.y = fgBgra.y * fgBgra.w / 255 + bgBgr.y * (255 - fgBgra.w) / 255;
    bgr.z = fgBgra.z * fgBgra.w / 255 + bgBgr.z * (255 - fgBgra.w) / 255;

    // Store point into image
    bigCudaImg.m_p_uchar3[by * bigCudaImg.m_size.x + bx] = bgr;
}

// New kernel for image rotation
__global__ void kernel_rotateImage(CudaImg origCudaImg, CudaImg rotateCudaImg, float sinAngle, float cosAngle)
{
    // X,Y coordinates and check image dimensions
    int rotateY = blockDim.y * blockIdx.y + threadIdx.y;
    int rotateX = blockDim.x * blockIdx.x + threadIdx.x;
    if (rotateY >= rotateCudaImg.m_size.y) return;
    if (rotateX >= rotateCudaImg.m_size.x) return;

    // Recalculation from image coordinates to centerpoint coordinates
    int crotateX = rotateX - rotateCudaImg.m_size.x / 2;
    int crotateY = rotateY - rotateCudaImg.m_size.y / 2;

    // Position in original image
    float corigX = cosAngle * crotateX - sinAngle * crotateY;
    float corigY = sinAngle * crotateX + cosAngle * crotateY;
    
    // Recalculation from centerpoint coordinates to image coordinates
    int origX = corigX + origCudaImg.m_size.x / 2;
    int origY = corigY + origCudaImg.m_size.y / 2;

    // Check if within original image boundaries
    if (origX < 0 || origX >= origCudaImg.m_size.x) return;
    if (origY < 0 || origY >= origCudaImg.m_size.y) return;

    // Copy pixel from original image to rotated image
    rotateCudaImg.m_p_uchar4[rotateY * rotateCudaImg.m_size.x + rotateX] = origCudaImg.m_p_uchar4[origY * origCudaImg.m_size.x + origX];
}

void cu_insertImage(CudaImg bigCudaImg, CudaImg smallCudaPic, int2 position)
{
    cudaError_t cerr;

    // Grid creation, size of grid must be equal or greater than images
    int blockSize = 32;
    dim3 blocks((smallCudaPic.m_size.x + blockSize - 1) / blockSize,
                (smallCudaPic.m_size.y + blockSize - 1) / blockSize);
    dim3 threads(blockSize, blockSize);
    kernel_insertImage<<<blocks, threads>>>(bigCudaImg, smallCudaPic, position);

    if ((cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));

    cudaDeviceSynchronize();
}

// New function for rotating images
void cu_rotateImage(CudaImg origCudaImg, CudaImg rotateCudaImg, float angle)
{
    cudaError_t cerr;

	float angleRad = angle * 3.14159265f / 180.0f;

    // Pre-calculate sin and cos values for the kernel
    float sinAngle = sinf(angleRad);
    float cosAngle = cosf(angleRad);

    // Grid creation, size of grid must be equal or greater than rotated image
    int blockSize = 32;
    dim3 blocks((rotateCudaImg.m_size.x + blockSize - 1) / blockSize,
                (rotateCudaImg.m_size.y + blockSize - 1) / blockSize);
    dim3 threads(blockSize, blockSize);
    
    // Call kernel with pre-calculated sin/cos values
    kernel_rotateImage<<<blocks, threads>>>(origCudaImg, rotateCudaImg, sinAngle, cosAngle);

    if ((cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));

    cudaDeviceSynchronize();
}

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

void Animation::start(CudaImg bgCudaImg, CudaImg insCudaImg)
{
    if (m_initialized) return;
    cudaError_t cerr;

    m_bg_cuda_img = bgCudaImg;
    m_res_cuda_img = bgCudaImg;
    m_ins_cuda_img = insCudaImg;
    
    // Allocate memory for rotated ball image
    m_rot_cuda_img.m_size = insCudaImg.m_size;
    cerr = cudaMalloc(&m_rot_cuda_img.m_p_void, m_rot_cuda_img.m_size.x * m_rot_cuda_img.m_size.y * sizeof(uchar4));
    if (cerr != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));

    // Memory allocation in GPU device
    // Memory for background
    cerr = cudaMalloc(&m_bg_cuda_img.m_p_void, m_bg_cuda_img.m_size.x * m_bg_cuda_img.m_size.y * sizeof(uchar3));
    if (cerr != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));

    // Memory for result
    cerr = cudaMalloc(&m_res_cuda_img.m_p_void, m_res_cuda_img.m_size.x * m_res_cuda_img.m_size.y * sizeof(uchar3));
    if (cerr != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));

    // Creation of background gradient
    int blockSize = 32;
    dim3 blocks((m_bg_cuda_img.m_size.x + blockSize - 1) / blockSize,
                (m_bg_cuda_img.m_size.y + blockSize - 1) / blockSize);
    dim3 threads(blockSize, blockSize);
    kernel_createGradient<<<blocks, threads>>>(m_bg_cuda_img);

    m_initialized = 1;
}

void Animation::next(CudaImg resCudaImg, int2 position, float angleDeg)
{
    if (!m_initialized) return;

    cudaError_t cerr;

    // Copy data internally GPU from background into result
    cerr = cudaMemcpy(m_res_cuda_img.m_p_void, m_bg_cuda_img.m_p_void, 
                     m_bg_cuda_img.m_size.x * m_bg_cuda_img.m_size.y * sizeof(uchar3), 
                     cudaMemcpyDeviceToDevice);
    if (cerr != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));

    // Rotate the ball based on its position
    // static float rotationAngle = 0.0f;
    // rotationAngle = position.x * 0.01f; // Adjust rotation speed based on X position
    
    // Rotate the image
    cu_rotateImage(m_ins_cuda_img, m_rot_cuda_img, angleDeg);
    
    // Insert the rotated image
    cu_insertImage(m_res_cuda_img, m_rot_cuda_img, position);

    // Copy data to GPU device
    cerr = cudaMemcpy(resCudaImg.m_p_void, m_res_cuda_img.m_p_void, 
                     m_res_cuda_img.m_size.x * m_res_cuda_img.m_size.y * sizeof(uchar3), 
                     cudaMemcpyDeviceToHost);
    if (cerr != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(cerr));
}

void Animation::stop()
{
    if (!m_initialized) return;

    cudaFree(m_bg_cuda_img.m_p_void);
    cudaFree(m_res_cuda_img.m_p_void);
    cudaFree(m_ins_cuda_img.m_p_void);
    cudaFree(m_rot_cuda_img.m_p_void); // Free memory for rotated image

    m_initialized = 0;
}