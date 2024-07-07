#include "my_viewer.hpp"

#include <open3d/Open3D.h>

#include <utility>

void viewCloud(const open3d::geometry::PointCloud& pcd) {
    open3d::visualization::DrawGeometries({std::make_shared<open3d::geometry::PointCloud>(pcd)});
}
