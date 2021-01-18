//
// Created by capit on 1/18/2021.
//

#ifndef EYETRACKINGNEXT_EYETRACKER_H
#define EYETRACKINGNEXT_EYETRACKER_H

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <raylib.h>
#include <future>
#include <easy/profiler.h>

class EyeTracker
{
private:
	cv::VideoCapture VideoCaptureMain;
	cv::Mat Frame;
	bool VideoReady = false;
	std::thread LoadingThread;
	
	void LoadVideoCapture();

public:
	EyeTracker();
	
	EyeTracker(const EyeTracker&) = delete;
	
	EyeTracker operator=(const EyeTracker&) = delete;
	
	virtual ~EyeTracker();
	
	void Update(const float& deltaTime);
	
	bool TryGetFrame(cv::Mat& mat) const;
	
	int GetCameraWidth() const;
	
	int GetCameraHeight() const;
};

#endif //EYETRACKINGNEXT_EYETRACKER_H
