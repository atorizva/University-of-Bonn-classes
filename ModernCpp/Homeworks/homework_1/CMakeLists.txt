cmake_minimum_required(VERSION 3.16)

project(link_my_library)

# Locate Open3D Library dependency
find_package(Open3D REQUIRED HINTS ${CMAKE_CURRENT_SOURCE_DIR}/open3d/lib/cmake)

# Your Build System Code starts here
# 1. Adding library -> Create a binary file for the lib
# DON'T USE RELATIVE PATH!
add_library(my_viewer SHARED ${CMAKE_CURRENT_SOURCE_DIR}/my_viewer/my_viewer.cpp)
target_link_libraries(my_viewer PUBLIC Open3D::Open3D)

# 2. Add executable
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp)

# 3. Link library to executable
target_link_libraries(main PRIVATE my_viewer)
# 4. Point CMAKE to where to start looking for hpp files
target_include_directories(my_viewer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})