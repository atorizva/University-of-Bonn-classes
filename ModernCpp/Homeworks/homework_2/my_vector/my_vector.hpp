/*
 * File: my_vector.hpp
 * Project: my_vector
 * File Created: Tuesday, 30th April 2024 10:12:39 am
 * Author: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx)
 * -----
 * Last Modified: Tuesday, 7th May 2024 10:28:16 am
 * Modified By: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx>)
 * -----
 * License: MIT License
 * -----
 * Description: Small vector struct with simple operations
 */


#pragma once  // Avoid multiple inclusions. Similar to #IF_DEF_...
#include <tuple>
#include <vector>


// Declares a new type with attributes.
struct Vector3d {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

// Function declarations 
// Remember to use const refs as input parameters when possible
Vector3d operator+(const Vector3d &lhs, const Vector3d &rhs);

Vector3d sum(const Vector3d& lhs, const Vector3d& rhs);

Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs);

Vector3d substract(const Vector3d& lhs, const Vector3d& rhs);

Vector3d scale(const Vector3d& vec, const double& scalar);

Vector3d multiply(const Vector3d& lhs, const Vector3d& rhs);

double norm(const Vector3d& vec);

Vector3d normalize(const Vector3d& vec);

void setConstant(Vector3d &vec, double &constant);

double dotProduct(const Vector3d& lhs, const Vector3d& rhs);

std::tuple<double, double> minmax(const Vector3d &vec);

bool isZeros(const Vector3d &vec);

std::vector<Vector3d> raySampling(const Vector3d &start_vec, const Vector3d &end_vec, const int num_samples);

std::ostream& operator<<(std::ostream& os, const Vector3d& vec);