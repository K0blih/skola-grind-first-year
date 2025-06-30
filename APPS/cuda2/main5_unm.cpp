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

#include "font24x40_lsb.h"
#include <string>
#include <random>

// Function prototype from .cu file
void cu_create_chessboard( CudaImg t_color_cuda_img, int t_square_size );
void cu_create_alphaimg( CudaImg t_color_cuda_img, uchar3 t_color );
void cu_insertimage(CudaImg &t_big_cuda_pic, CudaImg &t_small_cuda_pic, int2 t_position);

void cu_rotate90(CudaImg &t_cu_img, CudaImg &t_cu_img_rotated, int t_direction);
void cu_scale(CudaImg &t_cu_orig, CudaImg &t_cu_scaled);
void insertText(CudaImg &big_img, int2 pos, const char *text, const uint32_t font[256][40]);

int main( int t_numarg, char **t_arg )
{
    // Uniform Memory allocator for Mat
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator( &allocator );

    // cv::Mat l_chessboard_cv_img( 511, 515, CV_8UC3 );
    // CudaImg l_chessboard_cuda_img(l_chessboard_cv_img);

    // cu_create_chessboard( l_chessboard_cuda_img, 21 );
    // cv::imshow( "Chess Board", l_chessboard_cv_img );

    // cv::Mat l_alphaimg_cv_img( 211, 191, CV_8UC4 );
    // CudaImg l_alphaimg_cuda_img(l_alphaimg_cv_img);

    // cu_create_alphaimg( l_alphaimg_cuda_img, { 0, 0, 255 } );
    // cv::imshow( "Alpha channel", l_alphaimg_cv_img );

    // cu_insertimage( l_chessboard_cuda_img, l_alphaimg_cuda_img, { 11, 23 } );
    // cv::imshow( "Result I", l_chessboard_cv_img );

    // // some argument?
    // if ( t_numarg > 1 )
    // {
    //     // Load image
    //     cv::Mat l_bgra_cv_img = cv::imread( t_arg[ 1 ], cv::IMREAD_UNCHANGED ); // CV_LOAD_IMAGE_UNCHANGED );

    //     if ( !l_bgra_cv_img.data )
    //         printf( "Unable to read file '%s'\n", t_arg[ 1 ] );

    //     else if ( l_bgra_cv_img.channels() != 4 )
    //         printf( "Image does not contain alpha channel!\n" );

    //     else
    //     {
    //         // insert loaded image
    //         CudaImg l_bgra_cuda_img(l_bgra_cv_img);
    //         cu_insertimage( l_chessboard_cuda_img, l_bgra_cuda_img, { ( int ) l_chessboard_cuda_img.m_size.x / 2, ( int ) l_chessboard_cuda_img.m_size.y / 2 } );

    //         cv::imshow( "Result II", l_chessboard_cv_img );
    //     }
    // }





    // cv::Mat img_1_cv = cv::imread( t_arg[ 1 ], cv::IMREAD_UNCHANGED );
    // CudaImg img_1_cuda(img_1_cv);

    // cv::Mat img_1_rotated_cw_img_cv(img_1_cv.rows, img_1_cv.cols, CV_8UC4);
    // cv::Mat img_1_rotated_ccw_img_cv(img_1_cv.rows, img_1_cv.cols, CV_8UC4);
    // CudaImg img_1_cuda_rotated_1(img_1_rotated_cw_img_cv);
    // CudaImg img_1_cuda_rotated_2(img_1_rotated_ccw_img_cv);
    
    // cu_rotate90(img_1_cuda, img_1_cuda_rotated_1, 1);

    // // Získání šířky obrázku po rotaci
    // int width = img_1_cuda_rotated_1.m_size.x;
    // std::string width_str = std::to_string(width);
    // int2 text_pos = {10, 10};
    // insertText(img_1_cuda_rotated_1, text_pos, width_str.c_str(), font);

    // cv::imshow("Rotated Clockwise", img_1_rotated_cw_img_cv);

    // cu_rotate90(img_1_cuda, img_1_cuda_rotated_2, -1);
    // cv::imshow("Rotated Counter-Clockwise", img_1_rotated_ccw_img_cv);

    // cv::Mat img_1_scaled_cv(img_1_cv.rows * 2, img_1_cv.cols * 2, CV_8UC4);
    // CudaImg img_1_scaled_cuda(img_1_scaled_cv);
    
    // cu_scale(img_1_cuda, img_1_scaled_cuda);
    // cu_insertimage(img_1_scaled_cuda, img_1_cuda_rotated_1, {50, 50});
    // cv::imshow("Scaled Image", img_1_scaled_cv);

    cv::Mat bg_img = cv::imread(t_arg[1], cv::IMREAD_COLOR);
    cv::Mat ball_img = cv::imread(t_arg[ 2 ], cv::IMREAD_UNCHANGED);

    // Convert nature image to BGRA if needed
    // if (bg_img.channels() == 3) {
    //     cv::cvtColor(bg_img, bg_img, cv::COLOR_BGR2BGRA);
    // }

    // Create CudaImg objects
    CudaImg bg_cuda(bg_img);
    CudaImg ball_cuda(ball_img);

    // Random width
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(100, 300);
    int new_width = distr(gen);
    
    // Calculate WIDTH
    // float aspect_ratio = (float)ball_cuda.cols / ball_cuda.rows;
    // int new_width = static_cast<int>(new_height * aspect_ratio);

    // Calculate height maintaining aspect ratio
    float aspect_ratio = (float)ball_img.rows / ball_img.cols;
    int new_height = (int)(new_width * aspect_ratio);

    // Create scaled version
    cv::Mat ball_scaled_cv(new_height, new_width, CV_8UC4);
    CudaImg ball_scaled_cuda(ball_scaled_cv);
    cu_scale(ball_cuda, ball_scaled_cuda);

    // Add width text to scaled image
    std::string width_str = std::to_string(new_width);
    insertText(ball_scaled_cuda, {10, 10}, width_str.c_str(), font);

    // Create rotated version (90° clockwise)
    cv::Mat ball_rotated_cv(ball_scaled_cv.cols, ball_scaled_cv.rows, CV_8UC4);
    CudaImg ball_rotated_cuda(ball_rotated_cv);
    cu_rotate90(ball_scaled_cuda, ball_rotated_cuda, 1);

    // Add rotated width text
    std::string rotated_width_str = std::to_string(ball_rotated_cv.cols);
    insertText(ball_rotated_cuda, {10, 10}, rotated_width_str.c_str(), font);

    // Insert into nature image
    int2 position = {distr(gen) % (bg_img.cols - new_width), distr(gen) % (bg_img.rows - new_height)};
    cu_insertimage(bg_cuda, ball_scaled_cuda, position);

    position = {distr(gen) % (bg_img.cols - new_width), distr(gen) % (bg_img.rows - new_height)};
    cu_insertimage(bg_cuda, ball_rotated_cuda, position);

    // Display results
    cv::imshow("Balls in bg", bg_img);

    // while (cv::waitKey(0) != 'q') {
    //     int new_height = distr(gen);
    //     int new_width = (int)(new_height * aspect_ratio);
        
    //     ball_scaled_cv.create(new_height, new_width, CV_8UC4);
    //     ball_scaled_cuda = CudaImg(ball_scaled_cv);
    //     cu_scale(ball_cuda, ball_scaled_cuda);
        
    //     std::string height_str = std::to_string(new_height);
    //     insertText(ball_scaled_cuda, {10, 10}, height_str.c_str(), font);
        
    //     position.x = distr(gen) % (bg_img.cols - new_width);
    //     position.y = distr(gen) % (bg_img.rows - new_height);
    //     cu_insertimage(bg_cuda, ball_scaled_cuda, position);
        
    //     cv::imshow("Balls in bg", bg_img);
    // }

    cv::waitKey( 0 );
}

