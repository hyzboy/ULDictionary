# ULDictionary

Cross-platform C++20 CMake project supporting Windows, Linux, macOS, iOS, and Android.

## Requirements

- CMake 3.20 or higher
- C++20 compatible compiler:
  - Windows: Visual Studio 2019 16.11+ or MSVC 19.29+
  - Linux: GCC 10+ or Clang 13+
  - macOS: Xcode 13+ (Apple Clang 13+)
  - iOS: Xcode 13+
  - Android: NDK r21+ with Clang

## Building

### Windows

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Or using Visual Studio:
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Linux

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### macOS

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Or using Xcode:
```bash
mkdir build
cd build
cmake .. -G Xcode
cmake --build .
```

### iOS

```bash
mkdir build-ios
cd build-ios
cmake .. -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=14.0 \
    -DIOS=ON
cmake --build .
```

For iOS Simulator:
```bash
mkdir build-ios-sim
cd build-ios-sim
cmake .. -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_ARCHITECTURES=x86_64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=14.0 \
    -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DIOS=ON
cmake --build .
```

### Android

Using Android NDK:
```bash
mkdir build-android
cd build-android
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-21 \
    -DANDROID_STL=c++_shared
cmake --build .
```

Supported Android ABIs:
- `arm64-v8a` (64-bit ARM)
- `armeabi-v7a` (32-bit ARM)
- `x86` (32-bit Intel)
- `x86_64` (64-bit Intel)

## Running

After building, the executable will be in:
- Windows/Linux/macOS: `build/bin/ULDictionary`
- iOS: Build generates app bundle
- Android: Build generates shared library or executable

```bash
./build/bin/ULDictionary
```

## Project Structure

```
ULDictionary/
├── CMakeLists.txt          # Main CMake configuration
├── src/                    # Source files
│   └── main.cpp           # Main entry point
├── .gitignore             # Git ignore rules
└── README.md              # This file
```

## Features

- C++20 standard compliance
- Cross-platform support (Windows, Linux, macOS, iOS, Android)
- CMake-based build system
- Platform detection and conditional compilation
- Modern C++ features enabled

## License

[Add your license here]

## Contributing

[Add contribution guidelines here]
