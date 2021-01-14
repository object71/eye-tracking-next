# Setup

To be able to build the project you would need to:

```
./vcpkg/bootstrap-vcpkg.bat
./vcpkg/vcpkg.exe install opencv:x64-windows

cmake -S . -B build
```

# Build

```
cmake --build build
```