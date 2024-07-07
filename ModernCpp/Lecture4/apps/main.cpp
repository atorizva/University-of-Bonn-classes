#include <iostream>
#include <point_class/Point.hpp>

int main() {
  Point a(10.0, 10.0, 10.0);
  Point b(12.0, 5.0, 0.0);
  Point c(a); // Calls COPY constructor

  std::cout << "Euclidean distance between points: " << Point::Dist(a, b) << " = " << a.Dist(b) << std::endl;

  std::cout << "Number of points: " << Point::count << std::endl;

  std::cout << "Point a is greater than Point b: " <<  ((a < b) ? "True": "False") << std::endl;

  std::cout << "Point a == c: " << ((a == c) ? "True" : "False") << std::endl;

  Point d;
  Point e = std::move(d);

  std::cout << "Point d no longer exists?: " << d << std::endl;  // For some reason, d is not showing garbage. Ask Tiziano
  
  // Lower than expected, maybe some constructors don't increment the counter
  std::cout << "Number of points: " << Point::count << std::endl;  

  return 0;
}