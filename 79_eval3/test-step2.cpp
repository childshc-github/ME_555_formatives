#include <cstdlib>

#include "euler.h"

// test from README:
// ---------------------------------
int main(void) {
  // create MyOde array (params)
  std::vector<double> inputs = std::vector<double>(5);
  inputs[0] = 1;
  inputs[1] = 0.1;
  inputs[2] = 5;
  inputs[3] = 2;
  inputs[4] = 6;
  MyOde params(inputs);

  // put in Euler sim
  EulerSimulation ES(params);

  //setup timespan
  std::vector<double> tspan = std::vector<double>(2);
  tspan[0] = 0;
  tspan[1] = 5;

  // setup ics
  std::vector<double> ics = std::vector<double>(2);
  ics[0] = 0;
  ics[1] = 0.1;

  // setup time points
  size_t t_points = 3;

  // calculate
  odesoln_t test1 = ES(tspan, ics, t_points);

  // print
  std::cout << "The derivative is: " << '\n' << test1;

  // I did valgrind via CL

  // my other test cases:
  // -------------------------------

  // check w/ negative timespan
  std::vector<double> inputs1 = std::vector<double>(5);
  inputs[0] = 1;
  inputs[1] = 0.1;
  inputs[2] = 5;
  inputs[3] = 2;
  inputs[4] = 6;
  MyOde params1(inputs1);

  // put in Euler sim
  EulerSimulation ES1(params1);

  //setup timespan
  std::vector<double> tspan1 = std::vector<double>(2);
  tspan1[0] = 0;
  tspan1[1] = 5;

  // setup ics
  std::vector<double> ics1 = std::vector<double>(2);
  ics1[0] = 3;
  ics1[1] = 1;

  // setup time points
  size_t t_points1 = 3;

  // calculate
  odesoln_t test11 = ES1(tspan1, ics1, t_points1);

  // print
  std::cout << "The derivative is: " << '\n' << test11;

  // if passed empty array

  //

  return EXIT_SUCCESS;
}
