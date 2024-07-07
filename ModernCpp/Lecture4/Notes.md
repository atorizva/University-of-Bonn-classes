# Classes and structs (more or less the same)

What comes next can be applied to both of them.

## Constructors and destroyers

Are called when creating a new object and after getting out of scope to *destroy* them.

```cpp
struct Point() {
    Point () { std::cout << "New point!" << std::endl; }
    ~Point () { std::cout << "Bye point!" << std::endl; }

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

int main() {
    Point p;
    std::cout << p.x << std::endl;
    return 0;
}
```

> Constructors and destructors will be created automatically for you if you don't define them.

### Constructors with arguments

```cpp
struct Point() {
    Point (const double x_, const double y_, const double z_)
        : x(x), y(y_), z(z_) {}
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};
```

> Most of the time you want to have a constructor with arguments, but if you define it the compiler will not defined the default constructors!

### Default constructors

```cpp
// Empty
Point() {};  
// Copy constructor
Point(const Point &other) : x(other.x), y(other.y), z(other.z) {};  
// Move constructor. Calling it destroys the object you are moving its content to a new memory location
Point(Point &&other) {
    x = std::move(other.x);
    y = std::move(other.y);
    y = std::move(other.z);
}
// 'default' keyword tells the compiler to use your default constructor (const a_,...) : a(a_),... to define the move operation
Point(Point &&other) = default; 
```

> Copy constructor translates to overloading the function `operation=(const class &ref)`.

> Move constructor moves the reference to the right-handside value of the `=` operator to a different memory location. To call it explicitly use `std::move()`.

> If you use the `default` keyword you must be aware that you will need to use it for ASK TIZIANO WHEN AND HOW TO USE IT.

There is the `delete` keyword to vanish from existence certain default constructors to tell the compiler to don't use/create them. For example, you don't want to copy over and over again large objects in memory:

```cpp
LargeObject(const LargeObject &other) = delete;
```

### Additional constructor

You may initialize an object using `{ }`:

```cpp
struct HugeObect {
    double a;
    int b;
    std::string c;
};

int main() {
    HugeObject object{1.1, 2, "hola"};
    return 0;
}
```

## Public and private attributes and functions

*Hides* or makes available variables and functions of the class:

```cpp
struct Point {
public:
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
private:
  double norm = 1;
};
```

> You must always initialize your variables whether you use a constructor or not.

## Methods

Methods are functions associated to a certain class -> inside the scope of our class. They may be *private* or *public*.

```cpp
struct Point {
  Point () {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  double norm() { return std::sqrt(squareNorm()); }

  double x;
  double y;
  double z;

private:
  double squareNorm() { return x*x + y*y + z*z; }
};
```

> If you have a function with multiple arguments of the same type (e.g. `int`). It is much better to create your own types with conditions that will ensure safety in your code!

### Function features

Keywords that may be added to functions to enhance them:

```cpp
inline type function(); // inline for short functions below 10 lines (look it up).
const type function(); // Tells we are not modifiying attributes. It helps the compiler to optimize the code.
[[nodiscard]] type function(); // Reminds you that it will return a value that shouldn't be lost.
static type function(); // Can be called without creating an object as in Class::function();
```

### Attribute feature

Keywords that add a feature to the variable:

```cpp
static type variable;  // Shared variable available to every instantiated object! It exists at compiled time.
```

> `static` allows code safety because it is at compiled time.
