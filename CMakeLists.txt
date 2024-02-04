cmake_minimum_required(VERSION 3.28)
project(tracer)

set(CMAKE_CXX_STANDARD 20)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

include_directories(include)
add_executable(tracer main.cpp src/vec3f.cpp
        include/math/vec3f.hpp src/image.cpp include/image.hpp
        src/png_saver.cpp
        src/renderer.cpp)
target_link_libraries(${PROJECT_NAME} PNG::PNG)
