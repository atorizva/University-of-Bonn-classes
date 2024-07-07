#include <math.h>
#include <ostream>

class Point {
public:
  // Constructors and destructors. If you define one of them, you must define
  // ALL of them. Otherwise, the compiler will figure them out on its own.
  Point() { Point::count++; }
  Point(const double& _x, const double& _y, const double& _z) : x_(_x), y_(_y), z_(_z) { Point::count++; }

  // Deep copy  (same as overloading Point& operator=(const Point& other))
  Point(const Point &other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    this->z_ = other.z_;
  }
  // Deep copy alternative
  // Point(const Point &other) : x_(other.x_), y_(other.y_), z(other.z_) {}

  // Move constructor, 'steals' the data from other. Other stops existing after.
  // Same as overloading Point& operator=(Point&& other)
  Point(Point &&other) noexcept {
    this->x_ = std::move(other.x_);
    this->y_ = std::move(other.y_);
    this->z_ = std::move(other.z_);
  }

  ~Point() { Point::count--; }

  // Attribute accesable without instantiating object
  // inline keyword allows for initialization of static variable (c++17)
  inline static int count = 0;

  // Static method
  static double Dist(const Point &pt1, const Point &pt2) {
    return std::sqrt(pt1.x_*pt2.x_ + pt1.y_*pt2.y_ + pt1.z_*pt2.z_);
  }

  // Member function
  // const member functions doesn't modify the object
  double Dist(const Point &other) const {
    return std::sqrt(x_*other.x_ + y_*other.y_ + z_*other.z_);
  }

  // Operator overloading

  // friend keyword allows a function to access private variables. It has to be
  // declared outside of the class.
  friend std::ostream &operator<<(std::ostream &os, const Point &pt);
  
  bool operator<(const Point &other) const {
    return (this->x_ < other.x_) ||
           (this->x_ == other.x_ && this->y_ < other.y_) ||
           (this->x_ == other.x_ && this->y_ == other.y_ &&
            this->z_ < other.z_);
  }

  bool operator==(const Point &other) const {
    return (this->x_ == other.x_) && (this->y_ == other.y_) &&
           (this->z_ == other.z_);
  }


private:
  double x_ = 0.0;
  double y_ = 0.0;
  double z_ = 0.0;
};

std::ostream &operator<<(std::ostream &os, const Point &pt) {
    os << "(" << pt.x_ << "," << pt.y_ << "," << pt.z_ << ")";
    return os;
  }