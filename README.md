# ULDictionary

Cross-platform C++20 CMake project with Qt6 and Gumbo HTML parser support for Windows, Linux, and macOS.

## Requirements

- CMake 3.20 or higher
- Qt6 (Core and Widgets modules)
- Gumbo HTML parser library
- C++20 compatible compiler:
  - Windows: Visual Studio 2019 16.11+ or MSVC 19.29+
  - Linux: GCC 10+ or Clang 13+
  - macOS: Xcode 13+ (Apple Clang 13+)

## Installing Dependencies

### Qt6

#### Windows
Download and install Qt6 from [Qt official website](https://www.qt.io/download) or use package managers:
```cmd
choco install qt6
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install qt6-base-dev libgumbo-dev
```

#### macOS
```bash
brew install qt@6 gumbo-parser
```

### Gumbo Parser

#### Windows
Download and build from [Google Gumbo Parser GitHub](https://github.com/google/gumbo-parser), or use vcpkg:
```cmd
vcpkg install gumbo
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libgumbo-dev
```

#### macOS
```bash
brew install gumbo-parser
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
├── CMakeLists.txt          # Main CMake configuration with Qt6 and Gumbo
├── src/                    # Source files
│   └── main.cpp           # Main entry point (Qt6 GUI with Gumbo parser demo)
├── .gitignore             # Git ignore rules
└── README.md              # This file
```

## Features

- C++20 standard compliance
- Qt6 integration (Core and Widgets)
- Gumbo HTML5 parser integration for HTML parsing
- Cross-platform support (Windows, Linux, macOS)
- CMake-based build system with pkg-config support
- Platform detection and conditional compilation
- Modern C++ and Qt features enabled
- GUI application with Qt Widgets
- HTML parsing demonstration with Gumbo

## CI/CD and Releases

This project uses GitHub Actions for automated building and releasing.

### Continuous Integration

Every push to the repository triggers the CI workflow that:
- Builds the application on Linux, Windows, and macOS
- Verifies the executable is created successfully
- Ensures cross-platform compatibility

### Creating Releases

To create a new release with pre-built executables:

1. Create and push a version tag:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```

2. GitHub Actions will automatically:
   - Build the application for all three platforms
   - Package the executables with dependencies
   - Create a GitHub Release with downloadable binaries

### Manual Build Trigger

You can also manually trigger a build from the GitHub Actions tab without creating a release.

### Download Pre-built Binaries

Pre-built binaries are available in the [Releases](../../releases) section:
- **Linux**: `ULDictionary-Linux-x86_64.tar.gz`
- **Windows**: `ULDictionary-Windows-x86_64.zip` (includes Qt6 DLLs)
- **macOS**: `ULDictionary-macOS-x86_64.tar.gz` (includes Qt6 frameworks)

## License

[Add your license here]

## Contributing

[Add contribution guidelines here]
