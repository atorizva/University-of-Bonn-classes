add_executable(main main.cpp)
target_link_libraries(main PUBLIC Open3D::Open3D Eigen3::Eigen)
# target_link_libraries(main PUBLIC my_pointcloud)