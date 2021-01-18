project(Main LANGUAGES CXX)

add_executable(Main
               src/Main.cpp
               src/Main.h
               src/FaceTracker.cpp src/FaceTracker.h)

target_link_libraries(Main PRIVATE Packages)