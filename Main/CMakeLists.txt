project(Main LANGUAGES CXX)

add_executable(Main
               src/Main.cpp
               src/Main.h
               )

target_link_libraries(Main PRIVATE Packages)

if (Python3_EXECUTABLE)
    
    add_custom_command(TARGET Main POST_BUILD
                       COMMENT "Executing post build scripts \"${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/post_build.py\""
                       COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/post_build.py ${Main_BINARY_DIR}
                       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

endif()