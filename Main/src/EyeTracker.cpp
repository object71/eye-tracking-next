//
// Created by capit on 1/18/2021.
//

#include "EyeTracker.h"

EyeTracker::EyeTracker()
{
	LoadingThread = std::thread(&EyeTracker::LoadVideoCapture, this);
}

void EyeTracker::LoadVideoCapture()
{
	VideoCaptureMain.open(0, cv::VideoCaptureAPIs::CAP_MSMF);
	if (!VideoCaptureMain.isOpened())
	{
		spdlog::critical("Couldn't open capture device!");
		return;
	}
	
	spdlog::info("Camera captured successfully");
	
	VideoReady = true;
}

EyeTracker::~EyeTracker()
{
	LoadingThread.join();
	if (VideoReady)
	{
		VideoCaptureMain.release();
	}
}

void EyeTracker::Update(const float& deltaTime)
{
	if (VideoReady)
	{
		VideoCaptureMain >> Frame;
		cv::cvtColor(Frame, Frame, cv::COLOR_BGR2RGB);
		
		if (Frame.empty())
		{
			spdlog::critical("Frame is empty!");
			VideoReady = false;
		}
	}
}

int EyeTracker::GetCameraHeight() const
{
	if (!VideoReady)
	{
		return 0;
	}
	return (int)VideoCaptureMain.get(cv::CAP_PROP_FRAME_HEIGHT);;
}

int EyeTracker::GetCameraWidth() const
{
	if (!VideoReady)
	{
		return 0;
	}
	
	return (int)VideoCaptureMain.get(cv::CAP_PROP_FRAME_WIDTH);;
}

bool EyeTracker::TryGetFrame(cv::Mat& mat) const
{
	if (VideoReady)
	{
		mat = Frame;
	}
	
	return VideoReady;
}
