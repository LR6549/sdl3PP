cmake_minimum_required(VERSION 3.20)
project(SDL3++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message(STATUS "Running on Windows")
    list(APPEND CMAKE_MODULE_PATH "F:/Dropbox/Dropbox/CompilerUndScripts/CMake/modules")
    include(osSpecificLibs)

elseif(UNIX)
    message(STATUS "Running on Linux / Unix")
    list(APPEND CMAKE_MODULE_PATH "/home/lr6549/Dropbox/CompilerUndScripts/CMake/Modules")
    include(osSpecificLibs)
endif()



include_directories(.)
include_directories(subLibs)
include_directories(classes)
include_directories(classes/widget)

add_library(${PROJECT_NAME} STATIC
        SDL3++.hpp
        SDL3++.cpp


        classes/widget/Widget.cpp
        classes/widget/Widget.hpp
        classes/widget/widgetCommand/WidgetCommand.cpp
        classes/widget/widgetCommand/WidgetCommand.hpp



        subLibs/SDL3++TextureHandler/textureHandler.hpp
        subLibs/SDL3++TextureHandler/textureHandler.cpp
        subLibs/SDL3++TextRenderer/TextRenderer.hpp
        subLibs/SDL3++TextRenderer/TextRenderer.cpp
        subLibs/SDL3++AudioHandler/AudioHandler.hpp
        subLibs/SDL3++AudioHandler/AudioHandler.cpp
        subLibs/SDL3++WidgetHandler/WidgetHandler.hpp
        subLibs/SDL3++WidgetHandler/WidgetHandler.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_STATIC)

# ---- Link libraries ----
target_link_libraries(${PROJECT_NAME} PRIVATE
        osSpecificLibs
        SDL3.lib
        SDL3_image.lib
        SDL3_mixer.lib
        SDL3_net.lib
        SDL3_ttf.lib
        SDL3_rtf.lib
        user32
        winmm
        setupapi
        cfgmgr32
        version
        imm32
)