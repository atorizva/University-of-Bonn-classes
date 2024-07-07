#include <iostream>
// #include <tuple>  // Allows you to return multiple things

// [[nodiscard("you are studpid")]] Shows warning if you are not using the result
// inline -> Allows the compiler to optimize the function

// type (auto) -> Automatic type detection. Used in function type. Use it for readability reasons
// DO NOT use it in function arguments

// Extraction values -> Allows to extract tuple values with correct type
// const auto& [a1, a2, ..., an] = tuple(1.0, 2, ..., 'a');

// Remember you can pass arguments by reference (&) or by copy
// If you pass by reference is better to add 'const &' to prevent modifying

// Never return references! It's gonna be garbage

// Return value optimization doesn't make a copy, it's fast af

// static keyword means -> variable is available at compile time.
// Meaning it will be preserved. It breaks the local scope asumption

// Functions SHOULD do one only thing (Not a law, but keep it in mind)

// Function overloading -> Allows having multiple function declaration for different input arguments.

inline double sum(double param, double param2) {
  return param + param2;
}

int main() {
  std::cout << "Cia people" << std::endl;
  return 0;
}