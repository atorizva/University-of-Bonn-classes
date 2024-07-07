#include "tools.hpp"
int Accumulate(std::vector<int> vec) {
  int sum = 0;
  // Old ways
  // for (size_t i = 0; i < vec.size(); i++) {
    // sum = sum + vec[i];
  // }
  // New way (Pythonic kinda way)
  for (auto element : vec) {
    sum += element;
  }
  return sum;
}