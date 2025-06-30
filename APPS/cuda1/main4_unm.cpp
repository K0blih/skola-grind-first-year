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
// Image manipulation is performed by OpenCV library. 
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>

#include "uni_mem_allocator.h"
#include "cuda_img.h"

namespace cv {
}

// Function prototype from .cu file
void cu_run_grayscale( CudaImg t_bgr_cuda_img, CudaImg t_bw_cuda_img );
void cu_insert_image(CudaImg t_cuda_big_img, CudaImg t_cuda_small_img, int2 t_pos);
void cu_swap_image_quadrants(CudaImg t_dest_img, CudaImg t_src_img1, CudaImg t_src_img2, int2 t_quadrant1, int2 t_quadrant2);
void cu_insert_image_with_mask(CudaImg t_cuda_big_img, CudaImg t_cuda_small_img, int2 t_pos, uchar3 t_mask);
void cu_resize(const CudaImg& in_img, CudaImg& out_img, bool bilinear);

int main( int t_numarg, char **t_arg )
{
    // Uniform Memory allocator for Mat
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator( &allocator );

    if ( t_numarg < 2 )
    {
        printf( "Enter picture filename!\n" );
        return 1;
    }

    // Load image
    // cv::Mat l_bgr_cv_img = cv::imread( t_arg[ 1 ], cv::IMREAD_COLOR ); // CV_LOAD_IMAGE_COLOR );
    // cv::Mat l_small_cv_img = cv::imread( t_arg[ 2 ], cv::IMREAD_COLOR ); // CV_LOAD_IMAGE_COLOR );
    cv::Mat l_img1 = cv::imread(t_arg[1], cv::IMREAD_COLOR);
    cv::Mat l_img2 = cv::imread(t_arg[2], cv::IMREAD_COLOR);

    if ( !l_img1.data )
    {
        printf( "Unable to read file '%s'\n", t_arg[ 1 ] );
        return 1;
    }

    if ( !l_img2.data )
    {
        printf( "Unable to read file '%s'\n", t_arg[ 1 ] );
        return 1;
    }

    // create empty BW image
    // cv::Mat l_bw_cv_img( l_img1.size(), CV_8U );

    // data for CUDA
    // CudaImg l_bgr_cuda_img(l_bgr_cv_img);
    // CudaImg l_small_cuda_img(l_small_cv_img);

    CudaImg l_cuda_img1(l_img1);
    CudaImg l_cuda_img2(l_img2);

    cv::Mat l_result_swap(l_img1.rows / 2, l_img1.cols / 2, CV_8UC3);
    CudaImg l_cuda_result_swap(l_result_swap);

    // Swap 1: Upper left quadrant of img1 with upper right quadrant of img2
    cu_swap_image_quadrants(l_cuda_result_swap, l_cuda_img1, l_cuda_img2, {0, 0}, {1, 0});
    // Swap 2: Upper right quadrant of img1 with lower left quadrant of img2
    cu_swap_image_quadrants(l_cuda_result_swap, l_cuda_img1, l_cuda_img2, {1, 0}, {0, 1});
    // Swap 3: Lower left quadrant of img1 with lower right quadrant of img2
    cu_swap_image_quadrants(l_cuda_result_swap, l_cuda_img1, l_cuda_img2, {0, 1}, {1, 1});
    // Swap 4: Lower right quadrant of img1 with upper left quadrant of img2
    cu_swap_image_quadrants(l_cuda_result_swap, l_cuda_img1, l_cuda_img2, {1, 1}, {0, 0});
    // Swap 5: Upper left quadrant of img1 with lower right quadrant of img1
    cu_swap_image_quadrants(l_cuda_result_swap, l_cuda_img1, l_cuda_img1, {0, 0}, {1, 1});
    // Swap 6: Upper right quadrant of img2 with lower left quadrant of img2
    cu_swap_image_quadrants(l_cuda_result_swap, l_cuda_img2, l_cuda_img2, {1, 0}, {0, 1});

    // Show the result of swap operations
    cv::imshow("Swap Result", l_result_swap);


    cv::Mat l_canvas(l_img1.rows * 2, l_img1.cols * 2, CV_8UC3, cv::Scalar(255, 255, 255));
    CudaImg l_cuda_canvas(l_canvas);
    
    // 1. Insert small image into large without color changes (all channels)
    uchar3 full_mask = {255, 255, 255}; // or {1, 1, 1} for multiplication
    cu_insert_image_with_mask(l_cuda_canvas, l_cuda_img1, {0, 0}, full_mask);
    
    // 2. Insert only R channel
    uchar3 red_mask = {1, 0, 0}; // or {1, 0, 0} for multiplication
    cu_insert_image_with_mask(l_cuda_canvas, l_cuda_img1, {l_img1.cols, 0}, red_mask);
    
    // 3. Insert only G channel
    uchar3 green_mask = {0, 1, 0}; // or {0, 1, 0} for multiplication
    cu_insert_image_with_mask(l_cuda_canvas, l_cuda_img1, {0, l_img1.rows}, green_mask);
    
    // 4. Insert only B channel
    uchar3 blue_mask = {0, 0, 1}; // or {0, 0, 1} for multiplication
    cu_insert_image_with_mask(l_cuda_canvas, l_cuda_img1, {l_img1.cols, l_img1.rows}, blue_mask);
    
    // Show the result of insert with mask
    cv::imshow("Insert with Mask", l_canvas);


    // cv::Mat resized(l_img1.size() * 2, CV_8UC3);
    // CudaImg resCuda(resized);

    // cu_resize(l_cuda_img1, resCuda, true);
    // cv::imshow("Resized NN", resized);

    // cu_resize(l_cuda_img1, resCuda, false);
    // cv::imshow("Resized MM", resized);

    // insert smaller image into image
    // int2 position = {30, 30};
    // cu_insert_image(l_bgr_cv_img, l_small_cuda_img, position);

    // Function calling from .cu file
    // cu_run_grayscale( l_bgr_cuda_img, l_bw_cuda_img );

    // Show the Color and BW image
    // cv::imshow( "Color", l_bgr_cv_img );
    // cv::imshow( "GrayScale", l_bw_cv_img );
    cv::waitKey( 0 );
}
