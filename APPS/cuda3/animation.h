#ifndef ANIMATION_H
#define ANIMATION_H

#include "cuda_img.h"

class Animation
{
public:
    int m_initialized;
    CudaImg m_bg_cuda_img, m_ins_cuda_img, m_res_cuda_img, m_rot_cuda_img;
    // Constructor
    Animation() : m_initialized(0) {}
    
    // Start animation - initialize CUDA memory
    void start(CudaImg bgCudaImg, CudaImg insCudaImg);
    
    // Create next frame of animation
    void next(CudaImg resCudaImg, int2 position, float angleDeg);
    
    // Stop animation - free CUDA memory
    void stop();

};

// Helper function prototypes
void cu_insertImage(CudaImg bigCudaImg, CudaImg smallCudaPic, int2 position);
void cu_rotateImage(CudaImg origCudaImg, CudaImg rotateCudaImg, float angle);
void cu_scale(CudaImg &t_cu_orig, CudaImg &t_cu_scaled);

#endif // ANIMATION_H