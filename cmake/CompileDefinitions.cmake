if (WIN32)
    add_compile_definitions(WINDOWS=1)
endif ()

if (UNIX AND NOT APPLE)
    add_compile_definitions(LINUX=1)
endif ()

if (APPLE)
    add_compile_definitions(APPLE=1)
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_compile_definitions(_DEBUG=1)
else ()
    add_compile_definitions(NDEBUG=1)
endif (${CMAKE_BUILD_TYPE} MATCHES Debug)

if (PROFILE_APP)
    add_compile_definitions(PROFILE_APP=1)
endif ()