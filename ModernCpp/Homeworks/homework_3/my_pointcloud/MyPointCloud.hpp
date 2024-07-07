#pragma once

#include <Eigen/Dense>
#include <vector>

// Single Voxel to use for voxel down sample
struct Voxel {
    Voxel(int x, int y, int z) : i(x), j(y), k(z) {}
    Voxel(const Eigen::Vector3d &point, double voxel_size)
        : i(static_cast<int>(point[0] / voxel_size)),
          j(static_cast<int>(point[1] / voxel_size)),
          k(static_cast<int>(point[2] / voxel_size)) {}
    // We need the following operator to be able to compare voxels
    // as keys in an unordered map
    bool operator==(const Voxel &vox) const { return i == vox.i && j == vox.j && k == vox.k; }

    int i;
    int j;
    int k;
};

// Specialization of std::hash for our custom type Voxel
namespace std {

// Needed for unoredered map
template <>
struct hash<Voxel> {
    size_t operator()(const Voxel &vox) const {
        return ((1 << 20) - 1) & (vox.i * 73856093 ^ vox.j * 19349663 ^ vox.k * 83492791);
    }
};

}  // namespace std

// TODO: Fill your class with methods and attributes
class MyPointCloud {
public:
    MyPointCloud() : _points({}) {}  // Emtpy
    MyPointCloud(const std::vector<Eigen::Vector3d> &points) : _points(points) {}

    MyPointCloud(const MyPointCloud &my_pcd) = delete;
    MyPointCloud(MyPointCloud &&my_pcd) = default;

    MyPointCloud operator=(const MyPointCloud &my_pcd) = delete;
    MyPointCloud& operator=(MyPointCloud &&my_pcd) = default;

    // Eigen::Vector3d operator[](std::size_t idx) const {
    //   if (idx > _points.size() || idx < 0) {
        // throw std::out_of_range("Index out of bounds!"); 
    //   }
    //   return _points[idx];
    // }

    inline Eigen::Vector3d operator[](std::size_t idx) const {
      return _points.at(idx);  // .at already performs checks
    }
    // Public methods here
    inline void Clear() { _points.clear(); }

    inline int Size() const { return _points.size(); }

    inline bool IsEmpty() const { return Size() == 0; }

    inline std::vector<Eigen::Vector3d> GetPoints() const { return _points; }

    MyPointCloud Transfrom(const Eigen::Matrix4d& T) const;

    Eigen::Vector3d GetMinBound() const;

    Eigen::Vector3d GetMaxBound() const;

    // Default values just need to appear in the declaration
    MyPointCloud VoxelDownSample(const double voxel_size, const int n_points = 1) const;

    MyPointCloud RemoveDuplicatePoints() const;

    MyPointCloud Threshold(const double threshold) const;

    std::tuple<Eigen::Vector3d, Eigen::Matrix3d> ComputeMeanAndCovariance() const;

    // TODO
    Eigen::Vector3d ComputeGroundNormal() const;

private:
    // Private attributes here
    std::vector<Eigen::Vector3d> _points;
};
