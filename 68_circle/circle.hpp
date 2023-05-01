#include <stdio.h>
#include <stdlib.h>

#include <cmath>

#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  // initializer list
  Circle(Point p, double c) : center(p), radius(c) {}

  // move circle method
  void move(double d1, double d2) { center.move(d1, d2); }

  // compute area method
  double intersectionArea(const Circle & otherCircle) {
    // initialize answer
    double answer = 0;
    // find distance between circle centers
    double d = this->center.distanceFrom(otherCircle.center);
    // if don't intersect
    if (d > (this->radius + otherCircle.radius)) {
      return answer;
    }
    // if otherCircle inside this
    if (d <= (this->radius - otherCircle.radius) && this->radius >= otherCircle.radius) {
      answer = 3.1415 * otherCircle.radius * otherCircle.radius;
      return answer;
    }
    // if this inside otherCircle
    if (d <= (otherCircle.radius - this->radius) && otherCircle.radius >= this->radius) {
      answer = 3.1415 * this->radius * this->radius;
      return answer;
    }
    // another type of intersection
    else {
      double alpha = acos((this->radius * this->radius + d * d -
                           otherCircle.radius * otherCircle.radius) /
                          (2 * this->radius * d)) *
                     2;
      double beta = acos((otherCircle.radius * otherCircle.radius + d * d -
                          this->radius * this->radius) /
                         (2 * otherCircle.radius * d)) *
                    2;
      double a1 = 0.5 * beta * otherCircle.radius * otherCircle.radius -
                  0.5 * otherCircle.radius * otherCircle.radius * sin(beta);
      double a2 = 0.5 * alpha * this->radius * this->radius -
                  0.5 * this->radius * this->radius * sin(alpha);
      answer = a1 + a2;
      return answer;
    }
    // no conditions mets
    return EXIT_FAILURE;
  }
};
