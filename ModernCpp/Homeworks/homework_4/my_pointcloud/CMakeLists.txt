add_library(my_pointcloud STATIC  Utilities.cpp)

target_link_libraries(my_pointcloud PUBLIC Open3D::Open3D Eigen3::Eigen)
target_include_directories(my_pointcloud PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_features(my_pointcloud PUBLIC cxx_std_17)