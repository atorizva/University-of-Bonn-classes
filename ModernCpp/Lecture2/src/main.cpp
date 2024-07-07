#include <iostream>
#include <vector>
#include "tools.hpp"

int main() {
  std::vector<int> my_vector{0};
  std::cout << "Accumulate output: " << Accumulate(my_vector) << std::endl;
  return 0;
}