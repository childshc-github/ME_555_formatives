#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "euler.h"

// checks formatting of vectors created from handler
void format_check(std::vector<double> ode_inputs,
                  std::vector<double> tspan,
                  std::vector<double> ics) {
  // check format by trackers + vector sizes
  if (ode_inputs.size() != 5) {
    std::cerr << "Incorrect number of ODE params passed" << '\n';
  }
  if (tspan.size() != 2) {
    std::cerr << "Incorrect number of time span params passed" << '\n';
  }
  if (ics.size() != 2) {
    std::cerr << "Incorrect number of initial conditions passed" << '\n';
  }
}

// calculates EulerSim
odesoln_t find_Esim(std::vector<double> ode_inputs,
                    std::vector<double> tspan,
                    std::vector<double> ics,
                    size_t num_points) {
  // create ode
  MyOde params(ode_inputs);

  // put in EulerSim
  EulerSimulation ES(params);

  // calculate
  odesoln_t answer = ES(tspan, ics, num_points);

  return answer;
}

// checks correct num commas
void comma_check(int num_commas, int itype) {
  // make sure correct number of commas per input
  // ode_params
  if (itype == 0) {
    if (num_commas != 4) {
      std::cerr << "Incorrect num commas for ode parameters" << '\n';
      exit(EXIT_FAILURE);
    }
  }

  // tspan and ics
  if (itype == 1) {
    if (num_commas != 1) {
      std::cerr << "Incorrect num commas for " << itype << '\n';
      exit(EXIT_FAILURE);
    }
  }

  // time step
  if (itype == 2) {
    if (num_commas != 0) {
      std::cerr << "Incorrect num commas for time step" << '\n';
      exit(EXIT_FAILURE);
    }
  }
}

// converts strings to double
std::vector<double> convert_string(char * line, int itype) {
  // tracker + holder
  char * endptr;
  std::vector<double> answer = std::vector<double>();

  // convert string based on whitespace + type
  if (itype == 0) {
    // update vector w/ all 5 params
    char * endptr1;
    char * endptr2;
    char * endptr3;
    double m, c, k, a, om;
    m = strtod(line, &endptr);
    endptr++;
    c = strtod(endptr, &endptr1);
    endptr1++;
    k = strtod(endptr1, &endptr2);
    endptr2++;
    a = strtod(endptr2, &endptr3);
    endptr3++;
    om = strtod(endptr3, NULL);
    answer.push_back(m);
    answer.push_back(c);
    answer.push_back(k);
    answer.push_back(a);
    answer.push_back(om);
    return answer;
  }

  else if (itype == 1) {
    // get params + update vector
    double init, fin;
    init = strtod(line, &endptr);
    fin = strtod(endptr, NULL);
    answer.push_back(init);
    answer.push_back(fin);
    return answer;
  }

  else if (itype == 2) {
    double n;
    n = strtod(line, &endptr);
    answer.push_back(n);
    return answer;
  }

  std::cerr << "No conversion occured" << '\n';
  exit(EXIT_FAILURE);
}

// check if an integer, comma, or .
void is_convertible(char input) {
  // create template vector
  std::vector<double> check = std::vector<double>();
  int present = 0;

  // add acceptable inputs to vector
  for (int i = 48; i <= 57; i++) {
    check.push_back(i);
  }
  // commas and .
  check.push_back(46);
  check.push_back(44);

  // loop through + check
  for (size_t i = 0; i < check.size(); i++) {
    if (input == check[i]) {
      present = 1;
    }
  }

  // if not present, exit fail
  if (present != 1) {
    std::cerr << "Incorrect conversion type in input" << '\n';
    exit(EXIT_FAILURE);
  }
}

// checks if any decimals are missing nums
void good_dot(char * line) {
  // iterate + check entries
  int loc = 0;
  while (line[loc] != '\0') {
    if (line[loc] == '.') {
      if ((line[(loc + 1)] < '0') || (line[(loc + 1)] > '9')) {
        std::cerr << "Lone decimal point present in input" << '\n';
        exit(EXIT_FAILURE);
      }
    }
    loc++;
  }
}

std::vector<double> splicer(char * line, int itype) {
  // get number of commas + check no spaces + correct type (no letters in input)
  int loc = 0;
  int num_commas = 0;

  // check missing decimal number
  good_dot(line);

  while (line[loc] != '\0') {
    // if empty space in input
    if (line[loc] == ' ') {
      std::cerr << "Blank space inside paramters for " << itype << '\n';
      exit(EXIT_FAILURE);
    }

    // checks if entries can be converted to double
    is_convertible(line[loc]);

    // track commas
    if (line[loc] == ',') {
      num_commas++;
      // change commas to whitespace for conversion
      line[loc] = ' ';
    }
    loc++;
  }

  // ensure correct # inputs given
  comma_check(num_commas, itype);

  // convert string to double based on itype
  std::vector<double> answer = convert_string(line, itype);

  // return vector
  return answer;
}

// get sort + print w/ sim
int main(int argc, char ** argv) {
  // ensure standard input valid
  if (argc != 5) {
    std::cerr << "Invalid number of args given" << '\n';
    exit(EXIT_FAILURE);
  }

  // note: ode_params=0, tspan/ics=1, n=2

  // splice ode params
  std::vector<double> ode_params = splicer(argv[1], 0);

  // // splice tspan
  std::vector<double> tspan = splicer(argv[2], 1);

  // splice ics
  std::vector<double> ics = splicer(argv[3], 1);

  // get num_points
  std::vector<double> n_steps = splicer(argv[4], 2);
  double n = n_steps[0];

  // check formatting
  format_check(ode_params, tspan, ics);

  // calculate ESim
  odesoln_t answer = find_Esim(ode_params, tspan, ics, n);

  // print
  std::cout << answer;

  return EXIT_SUCCESS;
}
