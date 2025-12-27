#include <iostream>
#include <string>
#include <format>

int main(int argc, char* argv[]) {
    std::cout << "ULDictionary - Cross-platform C++20 Application" << std::endl;
    std::cout << std::format("Compiled with C++{}", __cplusplus) << std::endl;
    
#ifdef PLATFORM_WINDOWS
    std::cout << "Platform: Windows" << std::endl;
#elif defined(PLATFORM_IOS)
    std::cout << "Platform: iOS" << std::endl;
#elif defined(PLATFORM_MACOS)
    std::cout << "Platform: macOS" << std::endl;
#elif defined(PLATFORM_ANDROID)
    std::cout << "Platform: Android" << std::endl;
#elif defined(PLATFORM_LINUX)
    std::cout << "Platform: Linux" << std::endl;
#else
    std::cout << "Platform: Unknown" << std::endl;
#endif
    
    std::cout << "Arguments: " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "  [" << i << "]: " << argv[i] << std::endl;
    }
    
    return 0;
}
