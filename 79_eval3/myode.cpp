#include "myode.h"

#include <math.h>

// constructor
MyOde::MyOde(const std::vector<double> & ivector) {
  // make sure input vector has length of 5
  assert(ivector.size() == 5);

  // initialize private members
  m = ivector[0];
  c = ivector[1];
  k = ivector[2];
  a = ivector[3];
  o = ivector[4];
}

// function operator
std::vector<double> MyOde::operator()(double time,
                                      const std::vector<double> & ivec) const {
  // check vector ok
  assert(ivec.size() == 2);

  // check time ok
  assert(time >= 0);

  // create answer template for return
  std::vector<double> answer = std::vector<double>(2);

  // ydot_0 is equal to y1 (2nd entry in input vector)
  answer[0] = ivec[1];

  // calculate ydot_1
  answer[1] = ((a * sin(o * time)) - (c * ivec[1]) - (k * ivec[0])) / m;

  // return vector
  return answer;
}

// get order
unsigned MyOde::getOrder() const {
  // return order of ODE
  return 2;
}

// get parameter value via its name
double MyOde::getParam(char name) const {
  // return requested paramter
  if (name == 'm') {
    return this->m;
  }
  else if (name == 'c') {
    return this->c;
  }
  else if (name == 'k') {
    return this->k;
  }
  else if (name == 'a') {
    return this->a;
  }
  else if (name == 'o') {
    return this->o;
  }
  // if invalid name given
  else {
    std::cerr << "Invalid paraemeter name given\n";
    exit(EXIT_FAILURE);
  }
}

// stream insertion operator
std::ostream & operator<<(std::ostream & s, const MyOde & rhs) {
  // mass * xddot + c * xdot + k * x = a*sin(o * t)
  // split lines for cleaner code, but output all on one line
  s << rhs.getParam('m') << '*' << "xddot";
  s << " + ";
  s << rhs.getParam('c') << '*' << "xdot";
  s << " + ";
  s << rhs.getParam('k') << '*' << 'x';
  s << " = ";
  s << rhs.getParam('a') << '*' << "sin(" << rhs.getParam('o') << "*t)";

  // return
  return s;
}
