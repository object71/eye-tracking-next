#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <raylib.h>

int main()
{
	spdlog::info("Application started");
	spdlog::set_level(spdlog::level::debug);
	
	int screenWidth = 800;
	int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Eye Tracking Next");
	
	//cv::CAP_DSHOW or cv::CAP_MSMF or cv::CAP_V4L
	cv::VideoCapture capture;
	
	capture.open(0, cv::VideoCaptureAPIs::CAP_MSMF);
	if (!capture.isOpened())
	{
		spdlog::critical("Couldn't open capture device!");
		return 1;
	}
	
	spdlog::info("Camera captured successfully");
	
	
	
	cv::Mat frame
			(
					(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT),
					(int)capture.get(cv::CAP_PROP_FRAME_WIDTH),
					(int)capture.get(cv::CAP_PROP_FORMAT)
			);
	
	Image imageFrame;
	imageFrame.format = UNCOMPRESSED_R8G8B8;
	imageFrame.height = (int)capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	imageFrame.width = (int)capture.get(cv::CAP_PROP_FRAME_WIDTH);
	imageFrame.mipmaps = 1;
	imageFrame.data = frame.data;
	
	Texture2D mainTexture = LoadTextureFromImage(imageFrame);
	
	SetTargetFPS(60);
	
	while (!WindowShouldClose())
	{
		
		// Update
		capture >> frame;
		
		if (frame.empty())
		{
			spdlog::critical("Frame is empty!");
			break;
		}
		
		UpdateTexture(mainTexture, frame.data);
		
		// Draw
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
		DrawTexture(
				mainTexture, screenWidth - mainTexture.width - 60, screenHeight / 2 - mainTexture.height / 2, WHITE
		);
		DrawRectangleLines(
				screenWidth - mainTexture.width - 60, screenHeight / 2 - mainTexture.height / 2, mainTexture.width,
				mainTexture.height, BLACK
		);
		
		EndDrawing();
	}
	
	capture.release();
	
	return 0;
}
