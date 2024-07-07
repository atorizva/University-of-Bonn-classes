cmake_minimum_required(VERSION 3.16)
project(my_pointcloud)

find_package(Eigen3 REQUIRED)
find_package(Open3D REQUIRED HINTS ../homework_1/open3d/lib/cmake)

# add_subdirectory(my_pointcloud)
add_subdirectory(app)