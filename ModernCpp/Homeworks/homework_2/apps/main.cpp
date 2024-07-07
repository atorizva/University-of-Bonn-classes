/*
 * File: main.cpp
 * Project: apps
 * File Created: Tuesday, 30th April 2024 9:52:35 am
 * Author: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx)
 * -----
 * Last Modified: Tuesday, 7th May 2024 10:25:53 am
 * Modified By: Alfonso Toriz Vazquez (atoriz98@comunidad.unam.mx>)
 * -----
 * License: MIT License
 * -----
 * Description: Prints 10 equally spaced vectors between the
 * provided vectors start_vec and end_vec.
 */


#include "my_vector/my_vector.hpp"
#include <iostream>
#include <vector>

int main() {
    const Vector3d start_vec{0.0, 0.0, 0.0};
    const Vector3d end_vec{10.0, 10.0, 10.0};
    const int number_equal_spaces = 10;

    const std::vector<Vector3d> ray_sampled_vector = raySampling(start_vec, end_vec, number_equal_spaces);

    for (auto &vec : ray_sampled_vector) {
      std::cout << vec << std::endl;
    }
    /**
     * RAY TRACING
     *
     * Write a piece of code that computes and prints to the terminal
     * 10 equally spaced vectors that lie between the provided start_vec and end_vec
     *
     * Use as many functions as you defined in the my_vector library
     * Feel free to add more functions to the library if necessary to accomplish this task
     */
    return 0;
}