project(Packages)

add_subdirectory(easy_profiler)
add_subdirectory(filesystem)

add_library(Packages STATIC include/Packages.h src/Packages.cpp)

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

target_link_libraries(Packages fmt::fmt) # Should come along with spdlog
target_link_libraries(Packages spdlog::spdlog)
target_link_libraries(Packages ${raylib_LIBRARIES})
target_link_libraries(Packages easy_profiler)
target_link_libraries(Packages ghc_filesystem)

target_include_directories(Packages
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           ${raylib_INCLUDE_DIRS}
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )
