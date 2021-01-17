project(Packages)

add_library(Packages include/Packages.h src/Packages.cpp)

string(REPLACE ";" " " opencv_library_links "${OpenCV_LIBS}")

target_link_libraries(Packages
                      opencv_core
                      opencv_highgui
                      opencv_imgproc
                      opencv_video
                      opencv_videoio
                      opencv_objdetect
                      opencv_imgcodecs
                      opencv_flann
                      )

target_link_libraries(Packages fmt::fmt)
target_link_libraries(Packages spdlog::spdlog)

target_include_directories(Packages
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

message(STATUS "OpenCV Link: ${opencv_library_links}")
