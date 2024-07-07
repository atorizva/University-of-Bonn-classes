#include "MyPointCloud.hpp"
#include <unordered_map>


MyPointCloud MyPointCloud::Transfrom(const Eigen::Matrix4d &T) const {
  std::vector<Eigen::Vector3d> transformed_points = {};

  // Allocate space beforehand
  transformed_points.reserve(Size());
  // Transform PointCloud
  for (const auto &pt : this->_points) {
    // Point in homogenous coordinates
    Eigen::Vector4d pt_homogenous = {pt.x(), pt.y(), pt.z(), 1.0};
    // Apply transformation
    pt_homogenous = T * pt_homogenous;
    // Normalize
    pt_homogenous = pt_homogenous / pt_homogenous(3);
    // Take first 3 elements.
    transformed_points.emplace_back(pt_homogenous.head(3));
  }
  // Free memory that is not being use, useful when you don't know
  // the final dimensions.
  transformed_points.shrink_to_fit();

  return MyPointCloud(transformed_points);
}

Eigen::Vector3d MyPointCloud::GetMinBound() const {

  double min_x = 10000.0;
  double min_y = 10000.0;
  double min_z = 10000.0;

  for (const auto &pt : this->_points) {
    // 
    if (pt.x() < min_x)
      min_x = pt.x();
    if (pt.y() < min_y)
      min_y = pt.y();
    if (pt.z() < min_z)
      min_z = pt.z();
  }

  return Eigen::Vector3d(min_x, min_y, min_z);
}

Eigen::Vector3d MyPointCloud::GetMaxBound() const {

  double max_x = 0.0;
  double max_y = 0.0;
  double max_z = 0.0;

  for (const auto &pt : this->_points) {
    // 
    if (pt.x() > max_x)
      max_x = pt.x();
    if (pt.y() > max_y)
      max_y = pt.y();
    if (pt.z() > max_z)
      max_z = pt.z();
  }

  return Eigen::Vector3d(max_x, max_y,max_z);
}


MyPointCloud MyPointCloud::VoxelDownSample(const double voxel_size,
                                          const int n_points) const {
  std::vector<Eigen::Vector3d> filtered_points = {};

  // Voxels as keys with number of points as values
  std::unordered_map<Voxel, int> voxel_map;
  filtered_points.reserve(this->_points.size());

  for (const auto &pt : this->_points) {
    // Creates a voxel around the point
    const Voxel voxel = Voxel(pt, voxel_size);
    const auto found = voxel_map.find(voxel);

    // If voxel is already in the unordered map
    if (found == voxel_map.end()) {
      voxel_map[voxel] = 1;
      filtered_points.emplace_back(pt);
    } else {
      if (voxel_map[voxel] < n_points) {
        filtered_points.emplace_back(pt);
        voxel_map[voxel]++;
      }
    }
  }

  filtered_points.shrink_to_fit();
  return MyPointCloud(filtered_points);
};


// WHY? That just gets rid of everything
MyPointCloud MyPointCloud::RemoveDuplicatePoints() const {
  return MyPointCloud::VoxelDownSample(1e-10, 1);
}

std::tuple<Eigen::Vector3d, Eigen::Matrix3d>
MyPointCloud::ComputeMeanAndCovariance() const {
  Eigen::Vector3d mean = Eigen::Vector3d::Zero();
  Eigen::Matrix3d covariance = Eigen::Matrix3d::Zero();

  for (const auto &pt : this->_points) {
    mean += pt;
  }
  mean /= this->_points.size();

  for (const auto &pt : this->_points) {
    const Eigen::Vector3d variance = pt - mean;
    covariance += variance * variance.transpose();
  }
  covariance /= this->_points.size();

  // return {mean, covariance};  // Implicit tuple
  return std::make_tuple(mean, covariance);
};


// TODO: Ask if it is correct
Eigen::Vector3d MyPointCloud::ComputeGroundNormal() const {
  const auto& [mean, covariance] = ComputeMeanAndCovariance();

  Eigen::EigenSolver<Eigen::Matrix3d> eigen_solver;
  eigen_solver.compute(covariance);

  // return Eigen::Vector3d::Zero();
  return eigen_solver.eigenvectors().col(0).real();
}