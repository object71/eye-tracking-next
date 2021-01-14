#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int main()
{
	std::cout << "Application started" << std::endl;
	
	cv::Mat peaceImage = cv::imread("./data/peace.jpg", cv::IMREAD_UNCHANGED);
	
	if(peaceImage.empty()) return 1;
	
	cv::imshow("Peace", peaceImage);
	cv::waitKey(0);

    return 0;
}