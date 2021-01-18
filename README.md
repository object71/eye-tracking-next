# Setup

To be able to build the project you would need to:

```
./vcpkg/bootstrap-vcpkg.bat
./vcpkg/vcpkg.exe install opencv:x64-windows
./vcpkg/vcpkg.exe install spdlog:x64-windows
./vcpkg/vcpkg.exe install raylib:x64-windows
./vcpkg/vcpkg.exe install qt5:x64-windows

cmake -S . -B build "-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake"
```

# Build

```
cmake --build build
```