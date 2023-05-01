#include "euler.h"

// constructor
EulerSimulation::EulerSimulation(const MyOde & rhs) {
  // DA MyOde to private field
  ode_array = new MyOde(rhs);
}

// destructor
EulerSimulation::~EulerSimulation() {
  // delete entry of MyOde in ode_array
  delete ode_array;
}

// function operator
odesoln_t EulerSimulation::operator()(const std::vector<double> & tspan,
                                      const std::vector<double> & ics,
                                      size_t n) const {
  // check valid tspan
  assert(tspan.size() == 2);
  // EDIT: time doesn't have to be pos or increasing
  // assert(tspan[0] < tspan[1]);
  // assert(tspan[0] >= 0);

  // check valid ics
  assert(ics.size() == 2);
  assert((ics[0] >= 0) && (ics[1] >= 0));

  // check valid time size (need at least start + end)
  assert(n >= 2);

  // EDIT: fixed time step
  double adjusted = n - 1;
  double spanning = tspan[1] - tspan[0];
  double time_step = spanning / adjusted;

  // calculate time step
  // double time_step = n - 1;
  // time_step = 1 / time_step;

  // trackers
  int loc = 0;

  // create templates for storing calculations
  std::vector<double> store_time = std::vector<double>(0);
  std::vector<double> store_x = std::vector<double>(0);
  std::vector<double> store_xdot = std::vector<double>(0);

  // calculate x and xdot for each time step + update std::pair typdef
  for (double i = 0; i < n; i++) {
    // get values
    // (note: assumes tspan[0] == 0, not sure this is ok from README but makes sense)
    // EDIT: changed current_time calc if tspan !=[0]
    double current_time = tspan[0];
    if (i != 0) {
      current_time = time_step * i + tspan[0];
    }

    // add initial time, x, and xdot into std::pair typedef
    if (loc == 0) {
      store_time.push_back(current_time);
      store_x.push_back(ics[0]);
      store_xdot.push_back(ics[1]);
      loc++;
    }

    // add further steps
    else {
      // add time
      store_time.push_back(current_time);

      // calculate x + add
      double x_old = store_x[(loc - 1)];
      double xdot_old = store_xdot[(loc - 1)];
      double x = x_old + (xdot_old * time_step);
      store_x.push_back(x);

      // calculate xdot + add
      std::vector<double> param = std::vector<double>(2);
      param[0] = x_old;
      param[1] = xdot_old;
      std::vector<double> deriv = this->ode_array[0]((current_time - time_step), param);
      double xdot = xdot_old + (deriv[1] * time_step);
      store_xdot.push_back(xdot);

      loc++;
    }
  }

  // combine x and xdot into vector of vectors
  double num_rows = store_x.size();
  std::vector<std::vector<double> > store_all_x = std::vector<std::vector<double> >();
  store_all_x.resize(num_rows, std::vector<double>(2));

  for (int i = 0; i < num_rows; i++) {
    // add x
    store_all_x[i][0] = store_x[i];

    // add xdot
    store_all_x[i][1] = store_xdot[i];
  }

  // construct answer template + add vectors
  odesoln_t answer;
  answer = std::make_pair(store_time, store_all_x);

  // return typdef
  return answer;
}

// return requested entry in typedef
double EulerSimulation::getEntry(int row, int column) const {
  return 0;
}

// stream insertion overload
std::ostream & operator<<(std::ostream & s, const odesoln_t & output) {
  // make sure same number of rows for all entries
  assert((output.first.size()) == (output.second.size()));

  // get number of rows
  size_t rows = output.first.size();

  // loop through data structure + format print at each time step
  for (size_t i = 0; i < rows; i++) {
    s << output.first[i] << ',' << output.second[i][0] << ',' << output.second[i][1]
      << '\n';
  }

  return s;
}
