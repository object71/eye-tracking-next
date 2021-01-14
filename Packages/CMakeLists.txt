project(Packages)

add_library(Packages include/Packages.h src/Packages.cpp)

target_link_libraries(Packages ${OpenCV_LIBS})

target_include_directories(Packages
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )
