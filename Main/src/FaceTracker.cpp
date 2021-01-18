//
// Created by capit on 1/18/2021.
//

#include "FaceTracker.h"

FaceTracker::FaceTracker()
{
	LoadingThread = std::thread(&FaceTracker::LoadVideoCapture, this);
}

void FaceTracker::LoadVideoCapture()
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

FaceTracker::~FaceTracker()
{
	LoadingThread.join();
	if (VideoReady)
	{
		VideoCaptureMain.release();
	}
}

void FaceTracker::Update(const float& deltaTime)
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

int FaceTracker::GetCameraHeight() const
{
	if (!VideoReady)
	{
		return 0;
	}
	return (int)VideoCaptureMain.get(cv::CAP_PROP_FRAME_HEIGHT);;
}

int FaceTracker::GetCameraWidth() const
{
	if (!VideoReady)
	{
		return 0;
	}
	
	return (int)VideoCaptureMain.get(cv::CAP_PROP_FRAME_WIDTH);;
}

bool FaceTracker::TryGetFrame(cv::Mat& mat) const
{
	if (VideoReady)
	{
		mat = Frame;
	}
	
	return VideoReady;
}
