#pragma once

#include <open3d/Open3D.h>

#include <string>

#include "MyPointCloud.hpp"

MyPointCloud loadCloud(const std::string& filename);

void viewCloud(const MyPointCloud& pcd);
