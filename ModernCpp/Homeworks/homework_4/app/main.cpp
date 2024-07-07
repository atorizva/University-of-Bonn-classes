#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Dense>
#include "open3d/Open3D.h"

std::vector<Eigen::Vector3d> getPointsFromFile(const std::string& filename) {
  open3d::geometry::PointCloud pcd;
  open3d::io::ReadPointCloud(filename, pcd);

  return pcd.points_;
}


int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cerr << "[ERROR] Please provide the path to a pointcloud" << std::endl;
        return 1;
    }
    const std::string& filename(argv[1]);

    std::vector<Eigen::Vector3d> points = getPointsFromFile(filename);

    std::cout << "Number of points: " << points.size() << std::endl;

    auto filter_points = [](const Eigen::Vector3d& vec) {
      // z coor below 0 or norm above 100
      return vec(2) < 0.0 || vec.norm() > 100.0;
    };
    auto new_end = std::remove_if(points.begin(), points.end(), filter_points);

    points.erase(new_end, points.end());

    std::cout << "Number of points after filtering: " << points.size() << std::endl;
    // std::cout << "It compiles!" << std::endl;

  return 0;
}