#include <iostream>

#include "my_pointcloud/MyPointCloud.hpp"
#include "my_pointcloud/Utilities.hpp"
#include <Eigen/Dense>

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cerr << "[ERROR] Please provide the path to a pointcloud\n";
        return 1;
    }
    const std::string& filename(argv[1]);

    // How to load your cloud
    MyPointCloud my_pcd = loadCloud(filename);
    // std::cout << my_pcd[0].transpose() << std::endl;

    // TODO: Put Here your code to modify the point cloud

    std::cout << "Number of elements: " << my_pcd.Size() << std::endl;
    // viewCloud(my_pcd);
// 
    // MyPointCloud voxelized_pcd = my_pcd.VoxelDownSample(0.1, 10);
    // std::cout << "Number of elements after Voxel Down Sample operation: " << voxelized_pcd.Size() << std::endl;
    // viewCloud(voxelized_pcd);

    // MyPointCloud no_duplicates_pcd = my_pcd.RemoveDuplicatePoints();
    // std::cout << "Number of elements after removing duplicates: " << no_duplicates_pcd.Size() << std::endl;
    // viewCloud(no_duplicates_pcd);

    Eigen::Vector3d a = my_pcd.ComputeGroundNormal();

    return 0;
}
