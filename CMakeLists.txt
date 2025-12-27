cmake_minimum_required(VERSION 3.20)

project(ULDictionary 
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "ULDictionary - Cross-platform C++20 Qt6 project"
)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable Qt MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Platform detection
if(WIN32)
    message(STATUS "Building for Windows")
elseif(APPLE)
    message(STATUS "Building for macOS")
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

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# Platform-specific settings
if(WIN32)
    # Windows specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WINDOWS)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    endif()
    # Set Windows subsystem for GUI application
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )
elseif(APPLE)
    # macOS specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_MACOS)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_DEPLOYMENT_TARGET "11.0"
        MACOSX_BUNDLE ON
    )
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
    BUNDLE DESTINATION .
)
