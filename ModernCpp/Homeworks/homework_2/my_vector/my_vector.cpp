/*
 * File: my_vector.cpp
 * Project: my_vector
 * File Created: Tuesday, 30th April 2024 10:19:21 am
 * Author: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx)
 * -----
 * Last Modified: Tuesday, 7th May 2024 10:27:57 am
 * Modified By: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx>)
 * -----
 * License: MIT License
 * -----
 * Description: Small vector struct with simple operations.
 */


#include "my_vector.hpp"
#include <math.h>
#include <tuple>
#include <iostream>

Vector3d operator+(const Vector3d &lhs, const Vector3d &rhs) {
  Vector3d result;
  result.x = lhs.x + rhs.x;
  result.y = lhs.y + rhs.y;

  return result;
}

Vector3d sum(const Vector3d &lhs, const Vector3d &rhs) {
  Vector3d result;
  result.x = lhs.x + rhs.x;
  result.y = lhs.y + rhs.y;
  result.z = lhs.z + rhs.z;

  return result;
};

Vector3d operator-(const Vector3d &lhs, const Vector3d &rhs) {
  Vector3d result;
  result.x = lhs.x - rhs.x;
  result.y = lhs.y - rhs.y;
  result.z = lhs.z - rhs.z;

  return result;
}

Vector3d substract(const Vector3d &lhs, const Vector3d &rhs) {
  Vector3d result;
  result.x = lhs.x - rhs.x;
  result.y = lhs.y - rhs.y;
  result.z = lhs.z - rhs.z;

  return result;
}

Vector3d scale(const Vector3d &vec, const double &scalar) {
  Vector3d result;
  result.x = vec.x * scalar;
  result.y = vec.y * scalar;
  result.z = vec.z * scalar;

  return result;
}

Vector3d multiply(const Vector3d &lhs, const Vector3d &rhs) {
  Vector3d result;
  result.x = lhs.x * rhs.x;
  result.y = lhs.y * rhs.y;
  result.z = lhs.z * rhs.z;

  return result;
}

double norm(const Vector3d &vec) {
  double result = std::pow(vec.x, 2) + std::pow(vec.y, 2) + std::pow(vec.z, 2);

  return std::sqrt(result);
}

Vector3d normalize(const Vector3d &vec) {
  Vector3d result;
  double divisor = norm(vec);

  result.x = vec.x / divisor;
  result.y = vec.y / divisor;
  result.z = vec.z / divisor;

  return result;
}

void setConstant(Vector3d &vec, double &constant) {
  vec.x = constant;
  vec.y = constant;
  vec.z = constant;
}

double dotProduct(const Vector3d &lhs, const Vector3d &rhs) {
  return (lhs.x * rhs.x + lhs.y * rhs.y + rhs.z * lhs.z);
}

std::tuple<double, double> minmax(const Vector3d &vec) {
  double min = vec.x, max = vec.x;

  // Min
  if (vec.y < min) {
    min = vec.y;
  }
  if (vec.z < min) {
    min = vec.z;
  }
  // Max
  if (vec.y > max) {
    max = vec.y;
  }
  if (vec.z > max) {
    max = vec.z;
  }

  return std::make_tuple(min, max);
}

bool isZeros(const Vector3d &vec) {
  if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
    return true;
  }
  return false;
}

std::vector<Vector3d> raySampling(const Vector3d &start_vec,
                                  const Vector3d &end_vec,
                                  const int num_samples) {

  std::vector<Vector3d> ray_sampled_vector;

  double x = 0, y = 0, z = 0;

  const Vector3d diff = substract(end_vec, start_vec);

  const double delta_x = diff.x / num_samples;
  const double delta_y = diff.y / num_samples;
  const double delta_z = diff.z / num_samples;

  for (int i = 0; i < num_samples; i++) {
    x = x + delta_x;
    y = y + delta_y;
    z = z + delta_z;
    ray_sampled_vector.emplace_back(Vector3d{x, y, z});
  }

  return ray_sampled_vector;
}

std::ostream& operator<<(std::ostream &os, const Vector3d &vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
