#include <stdio.h>
#include <stdlib.h>

#include <cmath>

class Point {
 private:
  double x;
  double y;

 public:
  // default constructor
  Point() {
    x = 0;
    y = 0;
  }

  // move method
  void move(double dx, double dy) {
    x += dx;
    y += dy;
  }

  // distance method
  double distanceFrom(const Point & p) {
    double answer = (p.x - this->x) * (p.x - this->x);
    answer += ((p.y - this->y) * (p.y - this->y));
    answer = sqrt(answer);
    return answer;
  }
};
