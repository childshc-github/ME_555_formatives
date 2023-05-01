/* write your class interface in this file
   write function definitions only if they are very short
 */

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double init_x, double init_y) {
    x = init_x;
    y = init_y;
  }
  double getMagnitude() const {
    double double_x = x * x;
    double double_y = y * y;
    double total = double_x + double_y;
    total = sqrt(total);
    return total;
  }
  Vector2D operator+(const Vector2D & rhs) const {
    // returns copy of vector v3 based on v1 and v2
    Vector2D answer;
    answer.x = x + rhs.x;
    answer.y = y + rhs.y;
    return answer;
  }
  Vector2D & operator+=(const Vector2D & rhs) {
    // modifies v1, v2 and returns reference *this
    x = x + rhs.x;
    y = y + rhs.y;
    return *this;
  }
  double dot(const Vector2D & rhs) const {
    double first = x * rhs.x;
    double second = y * rhs.y;
    double total = first + second;
    return total;
  }
  void print() const { printf("<%.2f, %.2f>", x, y); }
};
