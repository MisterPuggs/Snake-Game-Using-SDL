cmake_minimum_required(VERSION 3.10)
project(Basic_GUI_in_CPP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

# Specify the path to SDL2 and SDL2_image installations
set(SDL2_INCLUDE_DIRS "C:/Libs/SDL2-2.28.5/include")
set(SDL2_LIBRARIES "C:/Libs/SDL2-2.28.5/lib/x64")
set(SDL2_IMAGE_INCLUDE_DIRS "C:/Libs/SDL2_image-2.8.2/include")
set(SDL2_IMAGE_LIBRARIES "C:/Libs/SDL2_image-2.8.2/lib/x64")

# Include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Basic_GUI_in_CPP
        src/Main.cpp
        src/SnakeElements.cpp
        src/IncludeElements.h
        src/SnakeElements.h
        src/Core.h
        src/Core.cpp)

target_link_libraries(${PROJECT_NAME} "${SDL2_LIBRARIES}/SDL2.lib" "${SDL2_IMAGE_LIBRARIES}/SDL2_image.lib")