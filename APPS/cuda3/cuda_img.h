// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage.
//
// Image interface for CUDA
//
// ***********************************************************************

#pragma once

#include <opencv2/core/mat.hpp>

// Structure definition for exchanging data between Host and Device
struct CudaImg
{
  uint3 m_size;             // size of picture
  union {
      void   *m_p_void;     // data of picture
      uchar1 *m_p_uchar1;   // data of picture
      uchar3 *m_p_uchar3;   // data of picture
      uchar4 *m_p_uchar4;   // data of picture
  };

  __host__ __device__ uchar1& at1(int y, int x) 
  { 
    return m_p_uchar1[y * m_size.x + x]; 
  }

  __host__ __device__ uchar3& at3(int y, int x) 
  { 
    return m_p_uchar3[y * m_size.x + x]; 
  }

  __host__ __device__ uchar4& at4(int y, int x) 
  { 
    return m_p_uchar4[y * m_size.x + x]; 
  }

  // Method to initialize from cv::Mat
  void fromMat(const cv::Mat& mat)
  {
    m_size.x = mat.cols;
    m_size.y = mat.rows;

    if (mat.type() == CV_8UC1)
      m_p_uchar1 = (uchar1*)mat.data;
    else if (mat.type() == CV_8UC3)
      m_p_uchar3 = (uchar3*)mat.data;
    else if (mat.type() == CV_8UC4)
      m_p_uchar4 = (uchar4*)mat.data;
  }

  // Constructor from cv::Mat
  CudaImg(const cv::Mat& mat)
  {
    fromMat(mat);
  }

  // Default constructor
  CudaImg() : m_p_void(nullptr) {
    m_size.x = m_size.y = m_size.z = 0;
  }
};