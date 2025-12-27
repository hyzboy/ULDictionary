cmake_minimum_required(VERSION 3.20)

project(ULDictionary 
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "ULDictionary - Cross-platform C++20 project"
)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform detection
if(WIN32)
    message(STATUS "Building for Windows")
elseif(APPLE)
    if(IOS)
        message(STATUS "Building for iOS")
    else()
        message(STATUS "Building for macOS")
    endif()
elseif(ANDROID)
    message(STATUS "Building for Android")
elseif(UNIX)
    message(STATUS "Building for Linux")
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add source files
set(SOURCES
    src/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Platform-specific settings
if(WIN32)
    # Windows specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WINDOWS)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    endif()
elseif(APPLE)
    # macOS/iOS specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_APPLE)
    if(IOS)
        target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_IOS)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "14.0"
        )
    else()
        target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_MACOS)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_DEPLOYMENT_TARGET "11.0"
        )
    endif()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(ANDROID)
    # Android specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_ANDROID)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(UNIX)
    # Linux specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_LINUX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
