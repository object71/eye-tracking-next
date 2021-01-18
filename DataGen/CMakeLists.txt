project(DataGen)

set(DataGenSources
    src/DataGen.cpp
    src/DataGen.h
    src/Filesystem.h
    )

add_executable(DataGen
               ${DataGenSources}
               )

target_link_libraries(DataGen PRIVATE Packages)

target_include_directories(DataGen
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )
