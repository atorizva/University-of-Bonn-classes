#include <iostream>
#include <string>

#include "my_viewer/my_viewer.hpp"
#include "open3d/Open3D.h"

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cerr << "[ERROR] Please provide the path to a pointcloud" << std::endl;
        return 1;
    }
    const std::string& filename(argv[1]);

    open3d::geometry::PointCloud pcd;
    open3d::io::ReadPointCloud(filename, pcd);
    viewCloud(pcd);
    return 0;
}
