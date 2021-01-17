#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>
#include <chrono>

int main()
{
	spdlog::info("Application started");
	spdlog::set_level(spdlog::level::debug);
	
	//cv::CAP_DSHOW or cv::CAP_MSMF or cv::CAP_V4L
	cv::VideoCapture capture;
	
	capture.open(0, cv::VideoCaptureAPIs::CAP_MSMF);
	if (!capture.isOpened())
	{
		spdlog::critical("Couldn't open capture device!");
		return 1;
	}
	
	spdlog::info("Camera captured successfully");
	
	cv::Mat frame;
	using namespace std::chrono;
	
	time_point<steady_clock> previousTime = steady_clock::now();
	float lag = 0.0f;
	const float desiredFrameRate = 0.016f;
	
	while (true)
	{
		time_point<steady_clock> currentTime = steady_clock::now();
		auto duration = currentTime - previousTime;
		const float delta = duration_cast<nanoseconds>(duration).count() / 1000000000.f;
		lag += delta;
		
		previousTime = currentTime;
		
		if (lag >= desiredFrameRate)
		{
			if (cv::waitKey(25) == 27)
			{
				break;
			}
			
			// Update
			if (capture.read(frame))
			{
				if (frame.empty())
				{
					spdlog::critical("Frame is empty!");
					break;
				}
				
				cv::imshow("Camera", frame);
				
				lag = 0.0f;
			}
		}
	}
	
	capture.release();
	return 0;
}