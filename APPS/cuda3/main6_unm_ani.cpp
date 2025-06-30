// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage without unified memory.
//
// Simple animation.
// Image manipulation is performed by OpenCV library.
//
// ***********************************************************************
#include <stdio.h>
#include <sys/time.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "uni_mem_allocator.h"
#include "cuda_img.h"
#include "animation.h"

int main(int numArg, char **arg)
{
	// Initialize random seed
	srand(time(NULL));
    
	// Uniform Memory allocator for Mat
	UniformAllocator allocator;
	cv::Mat::setDefaultAllocator(&allocator);

	Animation animation;
	// Output image dimensions
	int screenWidth = 888;
	int screenHeight = 777;
	 
	// Output image
	cv::Mat animationCvImg(screenHeight, screenWidth, CV_8UC3);
	 
	// Random scaling factor for the ball (between 0.5 and 1.5)
	float scaleFactor = 0.5f + (float)(rand() % 100) / 100.0f;
	printf("Ball scale factor: %.2f\n", scaleFactor);

	// Ball image
	cv::Mat ballCvImg = cv::imread("penguin.png", cv::IMREAD_UNCHANGED);
	printf("ball channels %d\n", ballCvImg.channels());
	
	// Scale the ball image
	cv::Mat scaledBallCvImg((int)(ballCvImg.rows * scaleFactor), (int)(ballCvImg.cols * scaleFactor), CV_8UC4);
	// cv::Mat scaledBallCvImg;
	// cv::resize(ballCvImg, scaledBallCvImg, cv::Size(), scaleFactor, scaleFactor);

	// Data for CUDA
	CudaImg animationCudaImg(animationCvImg);
	CudaImg ballCudaImg(ballCvImg);
	CudaImg scaledBallCudaImg(scaledBallCvImg);
	cu_scale(ballCudaImg, scaledBallCudaImg);
	
	// Prepare data for animation
	animation.start(animationCudaImg, scaledBallCudaImg);
	
	// Tennis ball simulation parameters
	float ballSpeed = 300.0f;  // pixels per second
	float rotationSpeed = 10.0f;  // radians per second
	
	// Initial position (start from left edge)
	float posX = 0.0f;
	float posY = screenHeight / 2.0f - scaledBallCvImg.rows / 2.0f;
	// float posY = screenHeight - scaledBallCvImg.rows; // start on bottom left to bottom right
	// Initial position (start from right edge)
	// float posX = screenWidth;
	// float posY = screenHeight / 2.0f - scaledBallCvImg.rows / 2.0f;
	// top to down
	// float posX = screenWidth / 2.0f - scaledBallCvImg.cols / 2.0f;
	// float posY = -scaledBallCvImg.rows;
	// down to top
	// float posX = screenWidth / 2.0f - scaledBallCvImg.cols / 2.0;
	// float posY = screenHeight;

	// Animation time control
	int runSimulation = 1;
	float time = 0;
	timeval startTime, curTime, oldTime, deltaTime;
	gettimeofday(&oldTime, NULL);
	startTime = oldTime;
	
	while (runSimulation)
	{
		cv::waitKey(1);
		
		// Time measuring
		gettimeofday(&curTime, NULL);
		timersub(&curTime, &oldTime, &deltaTime);
		if (deltaTime.tv_usec < 1000) continue; // Too short time
		oldTime = curTime;
		float deltaSec = (float)deltaTime.tv_usec / 1E6; // Time in seconds
		time += deltaSec;

		// float angleDeg = sinf(time * rotationSpeed) * 30.0f; // swing between -20° and +20°
		float angleDeg = time * ballSpeed; // spin

		// Update ball position
		posX += ballSpeed * deltaSec; // left to right
		// posX -= ballSpeed * deltaSec; // right to left
		// posY += ballSpeed * deltaSec; // top to down
		// posY -= ballSpeed * deltaSec; // down to top

		// Check if ball has moved off screen left to right
		if (posX > screenWidth)
		{
			runSimulation = 0;
		}
		// if (posX < -scaledBallCvImg.cols) // off-screen right to left
		// {
		// 	runSimulation = 0;
		// }
		// if (posY > screenHeight) // off-screen top to down
		// {
		// 	runSimulation = 0;
		// }
		// if (posY < -scaledBallCvImg.rows) // down to top
		// {
		// 	runSimulation = 0;
		// }

		// Update animation
		animation.next(animationCudaImg, {(int)posX, (int)posY}, angleDeg);
		cv::imshow("Tennis Ball Animation", animationCvImg);
	}
	 
	// Stop animation and clean up
	animation.stop();
	
	// Calculate total animation time
	gettimeofday(&curTime, NULL);
	timersub(&curTime, &startTime, &deltaTime);
	int deltaMs = deltaTime.tv_sec * 1000 + deltaTime.tv_usec / 1000;
	printf("The whole animation time: %d ms.\n", deltaMs);
	
	// Keep window open until key press
	cv::waitKey(0);
	
	return 0;
}