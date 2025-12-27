# ULDictionary

Cross-platform C++20 CMake project with Qt6 support for Windows, Linux, and macOS.

## Requirements

- CMake 3.20 or higher
- Qt6 (Core and Widgets modules)
- C++20 compatible compiler:
  - Windows: Visual Studio 2019 16.11+ or MSVC 19.29+
  - Linux: GCC 10+ or Clang 13+
  - macOS: Xcode 13+ (Apple Clang 13+)

## Installing Qt6

### Windows
Download and install Qt6 from [Qt official website](https://www.qt.io/download) or use package managers:
```cmd
choco install qt6
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install qt6-base-dev
```

### macOS
```bash
brew install qt@6
```

## Building

### Windows

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Or using Visual Studio with Qt6:
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2019_64"
cmake --build . --config Release
```

### Linux

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

If Qt6 is installed in a custom location:
```bash
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
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

If Qt6 is installed via Homebrew:
```bash
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt@6)
```

## Running

After building, the executable will be in:
- Windows/Linux: `build/bin/ULDictionary` (or `build/bin/Release/ULDictionary.exe` on Windows)
- macOS: `build/bin/ULDictionary.app`

```bash
./build/bin/ULDictionary
```

## Project Structure

```
ULDictionary/
├── CMakeLists.txt          # Main CMake configuration with Qt6
├── src/                    # Source files
│   └── main.cpp           # Main entry point (Qt6 GUI)
├── .gitignore             # Git ignore rules
└── README.md              # This file
```

## Features

- C++20 standard compliance
- Qt6 integration (Core and Widgets)
- Cross-platform support (Windows, Linux, macOS)
- CMake-based build system
- Platform detection and conditional compilation
- Modern C++ and Qt features enabled
- GUI application with Qt Widgets

## License

[Add your license here]

## Contributing

[Add contribution guidelines here]
