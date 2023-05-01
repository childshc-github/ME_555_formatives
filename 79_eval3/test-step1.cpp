#include <cstdlib>

#include "myode.h"

// test from README:
// ---------------------------------
int main(void) {
  // Create MyOde
  std::vector<double> readme_inputs = std::vector<double>(5);
  readme_inputs[0] = 1;
  readme_inputs[1] = 0.1;
  readme_inputs[2] = 5;
  readme_inputs[3] = 2;
  readme_inputs[4] = 6;
  MyOde ode(readme_inputs);

  // call function operator
  std::vector<double> test1 = std::vector<double>(2);
  double time = 0;
  test1[0] = 0.5;
  test1[1] = 0;
  std::vector<double> test_readme = ode(time, test1);
  std::cout << '{' << test_readme[0] << ',' << test_readme[1] << '}' << '\n';
  // use stream insertion
  std::cout << ode << '\n';

  // check order return

  // my test cases:
  // ---------------------------------
  // for time > 0
  time = 0.0;
  test1[0] = 0;
  test1[1] = 0.1;
  std::vector<double> test2 = ode(time, test1);
  std::cout << '{' << test2[0] << ',' << test2[1] << '}' << '\n';

  // for time < 0
  // this failed because of assert (good)
  // time = -5;
  // std::vector<double> test3 = ode(time, test1);
  // std::cout << "The derivative is: {" << test3[0] << ',' << test3[1] << '}' << '\n';

  // if incorrect vector size given
  // this failed size assert (good)
  // std::vector<double> inputs = std::vector<double>(6);
  // inputs[0] = 1;
  // inputs[1] = 0.1;
  // inputs[2] = 5;
  // inputs[3] = 2;
  // inputs[4] = 6;
  // inputs[5] = 10;
  // MyOde ode1(inputs);

  return EXIT_SUCCESS;
}
