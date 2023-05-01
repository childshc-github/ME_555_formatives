#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

typedef std::string task_t;

class TaskDep {
 private:
  // removed const from task
  task_t task;
  std::list<task_t> pres;

 public:
  // I added this:
  TaskDep(task_t new_task, std::list<task_t> new_prev);
  // write these
  // TaskDep(const task_t & t);
  const task_t & getTask() const;
  // void addPredecessor(const task_t & t);
  std::list<task_t> getPredecessors() const;
};
