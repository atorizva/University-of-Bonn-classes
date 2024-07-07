#include "Utilities.hpp"

#include <open3d/Open3D.h>

#include <string>

#include "MyPointCloud.hpp"

MyPointCloud loadCloud(const std::string& filename) {
    open3d::geometry::PointCloud pcd;
    auto success = open3d::io::ReadPointCloud(filename, pcd);
    if (!success) {
        std::cerr << "[ERROR] Impossible to load the point cloud at the given location: "
                  << filename << "\n";
        exit(1);
    }

    return MyPointCloud(pcd.points_);
}

// TODO: Display Axis in visualization
// void viewCloud(const MyPointCloud& pcd) {
//     open3d::visualization::RenderOption Options;
//     Options.show_coordinate_frame_ = true;
//     open3d::geometry::PointCloud o3d_pcd(pcd.GetPoints());
//     open3d::visualization::DrawGeometries(
//         {std::make_shared<open3d::geometry::PointCloud>(o3d_pcd)});
// }

void viewCloud(const MyPointCloud& pcd) {
    // Convert MyPointCloud to Open3D PointCloud
    open3d::geometry::PointCloud o3d_pcd(pcd.GetPoints());
    
    // Create a Visualizer object
    open3d::visualization::Visualizer vis;
    vis.CreateVisualizerWindow("Point Cloud Viewer");

    // Add the PointCloud to the Visualizer
    vis.AddGeometry(std::make_shared<open3d::geometry::PointCloud>(o3d_pcd));
    
    // Get the RenderOption and enable the coordinate frame
    open3d::visualization::RenderOption &opt = vis.GetRenderOption();
    opt.show_coordinate_frame_ = true;

    // Run the visualizer
    vis.Run();
    vis.DestroyVisualizerWindow();
}