#include "Main.h"

int main()
{
#if PROFILE_APP
//	EASY_PROFILER_ENABLE
#endif
	
	spdlog::info("Application started");
	spdlog::set_level(spdlog::level::debug);
	
	int screenWidth = 800;
	int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Eye Tracking Next");
	FaceTracker ft;
	
	Texture2D* mainTexture = nullptr;
	
	SetTargetFPS(60);
	
	while (!WindowShouldClose())
	{
		
		// Update
		ft.Update(GetFrameTime());
		
		cv::Mat currentFrame;
		if (ft.TryGetFrame(currentFrame))
		{
			if(!mainTexture) {
				Image imageFrame;
				imageFrame.format = UNCOMPRESSED_R8G8B8;
				imageFrame.height = ft.GetCameraHeight();
				imageFrame.width = ft.GetCameraWidth();
				imageFrame.mipmaps = 1;
				imageFrame.data = currentFrame.data;
				
				mainTexture = new Texture2D();
				*mainTexture = LoadTextureFromImage(imageFrame);
			} else {
				UpdateTexture(*mainTexture, currentFrame.data);
			}
		}
		
		// Draw
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
		if (mainTexture)
		{
			DrawTexture(
					*mainTexture, screenWidth - mainTexture->width - 60, screenHeight / 2 - mainTexture->height / 2, WHITE
			);
			DrawRectangleLines(
					screenWidth - mainTexture->width - 60, screenHeight / 2 - mainTexture->height / 2, mainTexture->width,
					mainTexture->height, BLACK
			);
		} else {
			DrawText("Loading...", 190, 200, 20, LIGHTGRAY);
		}
		
		EndDrawing();
	}

#if PROFILE_APP
//	std::string filename = fmt::format("profile.prof");
//	profiler::dumpBlocksToFile(filename.c_str());
#endif
	
	return 0;
}
