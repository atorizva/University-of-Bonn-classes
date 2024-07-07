# Objecct Oriented Programming (OOP)

Building relationships between classes.

```cpp
// Interface -> Contains pure virtual functions;
// Structs/Classes will derive from the interface and force the user to implement the functions
// from the interface.
struct Geometry {
    virtual void Print () = 0;
}


struct Point {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double norm() { return 1.0; };
    // 'virtual' function can be overloaded in derived classes
    virtual void Print() { std::cout << x << y << z << std::endl; }
    // virtual void fun() = 0; // Pure virtual function -> forces the user to implement the function
    // in the derived class. Now the base class its called an abstract class! It forces certain API
    // in the programmer.
}

// Inherits the public properties from Point struct
struct PointWithColor : public Point {
    u_int8_t color = 255;
    // 'override' 
    virtual void Print() override { std::cout << x << y << z << << color << std::endl; }
}

// Generic function for Point and Point derived class
Point shiftPoint(const Point &p) {
    Point copy = p;
    copy.z += 3.0;
    return copy;
}

int main() {
    PointWithColor p;
    shiftPoint(p);
    return(0);
}
```

> Overloading happends at compile time. Overriding happens at runtime.

## Prefer composition over inheritance always!

```cpp
struct Point() {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
}

struct PointWithColor() {
    Point coordinates;  // Composition! -> Include an object from a different class into another.
    u_int8_t color = 255;
}
```

## Casting

Change types around:

1. `static_cast` (compile time cast) The compiler usually handles it (e.g. int -> float).
2. `dynamic_cast` (works on pointers at runtime -> exploit inheritance between classes). Be careful! If you cast a base class to a derived class you can end up with a `nullptr`.
3. `const_cast`  creates a copy and removes 'const' keyword. AVOID.
4. `reinterpret_cast` it tries to convert binary code into a useful type.
5. C-style cast -> NEVER EVER EVER USE IT! It will randonmly try different type combinations until it gets somethings.
