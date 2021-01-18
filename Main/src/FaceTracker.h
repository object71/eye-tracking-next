//
// Created by capit on 1/18/2021.
//

#ifndef EYETRACKINGNEXT_FACETRACKER_H
#define EYETRACKINGNEXT_FACETRACKER_H

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <raylib.h>
#include <future>
#include <easy/profiler.h>

class FaceTracker
{
private:
	cv::VideoCapture VideoCaptureMain;
	cv::Mat Frame;
	bool VideoReady = false;
	std::thread LoadingThread;
	
	void LoadVideoCapture();

public:
	FaceTracker();
	
	FaceTracker(const FaceTracker&) = delete;
	
	FaceTracker operator=(const FaceTracker&) = delete;
	
	virtual ~FaceTracker();
	
	void Update(const float& deltaTime);
	
	bool TryGetFrame(cv::Mat& mat) const;
	
	int GetCameraWidth() const;
	
	int GetCameraHeight() const;
};

#endif //EYETRACKINGNEXT_FACETRACKER_H
