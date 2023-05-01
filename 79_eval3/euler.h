#ifndef __EULER_H__
#define __EULER_H__

#include <assert.h>

#include <iostream>
#include <utility>
#include <vector>

#include "myode.h"

// typedef
typedef std::pair<std::vector<double>, std::vector<std::vector<double> > > odesoln_t;

// header for simulation (step 2)
class EulerSimulation {
 private:
  MyOde * ode_array;

 public:
  EulerSimulation(const MyOde & rhs);
  ~EulerSimulation();
  odesoln_t operator()(const std::vector<double> & tspan,
                       const std::vector<double> & ics,
                       size_t n) const;
  double getEntry(int index1, int index2) const;
  friend void testEuler(EulerSimulation & es);
};

std::ostream & operator<<(std::ostream & s, const odesoln_t & output);
void testEuler(EulerSimulation & es);

#endif
