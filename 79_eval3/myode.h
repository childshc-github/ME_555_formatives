#ifndef __MYODE_H__
#define __MYODE_H__

#include <assert.h>

#include <iostream>
#include <vector>

// header for mass-springer dampner class
class MyOde {
 private:
  double m;
  double c;
  double k;
  double a;
  double o;

 public:
  MyOde(const std::vector<double> & ivector);
  std::vector<double> operator()(double time, const std::vector<double> & ivec) const;
  unsigned getOrder() const;
  double getParam(char name) const;
};

std::ostream & operator<<(std::ostream & s, const MyOde & rhs);

#endif
