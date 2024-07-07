#pragma once

// This pattern only allows for a class to be instanciating JUST once and
// by the compiler. The user is forbidden from instanciating the class.
struct Singleton {
public:
  Singleton(const Singleton& other) = delete;
  Singleton &operator=(const Singleton &other) = delete;

  Singleton &GetInstance() {
    static Singleton instance;  // The compiler builds static objects
    return instance;  // Returns a reference to the compiled time object.
  }
private:
  Singleton() = default;
};

// To access it you can do:
// const auto& s = Singleton::GetInstance();