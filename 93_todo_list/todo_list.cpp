#include <cstdlib>

#include "task.hpp"

// other functions

// constructor
TaskDep::TaskDep(task_t new_task, std::list<task_t> new_prev) {
  task = new_task;
  pres = new_prev;
}

// check if acceptable character
void good_char(char input) {
  // create acceptable vector
  std::vector<int> good = std::vector<int>();
  // add nums
  for (int i = 48; i <= 57; i++) {
    good.push_back(i);
  }
  // add cap letters
  for (int i = 65; i <= 90; i++) {
    good.push_back(i);
  }
  // add low letters
  for (int i = 97; i <= 122; i++) {
    good.push_back(i);
  }
  int there = 0;

  // loop through + throw error
  for (size_t i = 0; i < good.size(); i++) {
    if (input == good[i]) {
      there = 1;
    }
  }

  // check tracker
  if (there == 0) {
    std::cerr << "Incorrect char type present\n";
    exit(EXIT_FAILURE);
  }
}

// check format of 1 line - return num commas
int format_check(std::string input) {
  // trackers
  int num_colons = 0;
  int num_spaces = 0;
  int num_commas = 0;

  // check if given blank line
  if ((input[0] == ' ') || (input[0] == '\0') || (input[0] == '\n')) {
    std::cerr << "Blank line passed\n";
    exit(EXIT_FAILURE);
  }

  // loop through + check entries
  for (size_t i = 0; i < input.size(); i++) {
    // update trackers
    if (input[i] == ':') {
      int track = 0;
      if (input[(i + 1)] == ' ') {
        track = 1;
      }
      else if (input[(i + 1)] == '\0') {
        track = 1;
      }
      if (track != 1) {
        std::cerr << "Incorrect spacing after colon\n";
        exit(EXIT_FAILURE);
      }
      num_colons++;
    }
    else if (input[i] == ',') {
      num_commas++;
    }
    else if (input[i] == ' ') {
      num_spaces++;
    }
    // check good char
    else {
      good_char(input[i]);
    }
  }

  // check trackers
  // if (num_colons != 1) {
  //   std::cerr << "Incorrect number of colons in input\n";
  //   exit(EXIT_FAILURE);
  // }

  // if (num_spaces == 0) {
  //   if (num_commas != 0) {
  //     std::cerr << "Incorrect formatting in input\n";
  //     exit(EXIT_FAILURE);
  //   }
  // }

  // else if (num_commas != (num_spaces - 1)) {
  //   std::cerr << "Incorrect formatting in input\n";
  //   exit(EXIT_FAILURE);
  // }
  return num_commas;
}

// get info
TaskDep extract_info(std::string input, int num_commas) {
  // trackers
  size_t loc = 0;
  task_t new_task;
  std::string prev_temp;
  std::list<task_t> new_prev = std::list<task_t>();

  // get task
  while (input[loc] != ':') {
    new_task.push_back(input[loc]);
    loc++;
  }
  loc = loc + 2;

  // no add if 0 entry

  // get dependent - 1 entry
  if ((num_commas == 0) && (loc < input.size())) {
    while (input[loc] != '\0') {
      prev_temp.push_back(input[loc]);
      loc++;
    }
    // add to storage
    new_prev.push_back(prev_temp);
  }

  // get dependent - > 1 entry
  else if (num_commas > 0) {
    while (input[loc] != '\0') {
      if (input[loc] == ',') {
        // save + iterate twice
        new_prev.push_back(prev_temp);
        prev_temp.clear();
        loc = loc + 2;
      }
      else {
        prev_temp.push_back(input[loc]);
        loc++;
      }
    }
    new_prev.push_back(prev_temp);
  }

  // construct class + add info
  TaskDep answer = TaskDep(new_task, new_prev);
  return answer;
}

// get a task
const task_t & TaskDep::getTask() const {
  return this->task;
}

// return all previous
std::list<task_t> TaskDep::getPredecessors() const {
  return this->pres;
}

int main(int argc, char ** argv) {
  // open file for reading
  if (argc != 2) {
    std::cerr << "Incorrect number of inputs given\n";
    exit(EXIT_FAILURE);
  }

  // check file opens
  FILE * file;
  if ((file = fopen(argv[1], "r"))) {
    fclose(file);
  }
  else {
    std::cerr << "Couldn't open file\n";
    exit(EXIT_FAILURE);
  }

  // create vector for TaskDep
  std::vector<TaskDep> storage = std::vector<TaskDep>();

  // open file + sort  std::ifstream myFile;
  std::ifstream myFile;
  myFile.open(argv[1]);

  // make sure file opens + sort
  if (myFile.is_open()) {
    while (myFile) {
      // get line
      std::string myLine;

      while (std::getline(myFile, myLine)) {
        // check format
        int commas = format_check(myLine);

        // make dependency list of tasks from input file
        TaskDep newTD = extract_info(myLine, commas);

        // add class to list
        storage.push_back(newTD);
      }
    }
  }

  // make sure no repeat task in storage
  for (size_t i = 0; i < storage.size(); i++) {
    task_t ctask = storage[i].getTask();
    for (size_t s = (i + 1); s < storage.size(); s++) {
      task_t ntask = storage[s].getTask();
      if (ctask == ntask) {
        std::cerr << "Repeat tasks given\n";
        exit(EXIT_FAILURE);
      }
    }
  }

  // create answer list template
  std::list<task_t> print_answer = std::list<task_t>();

  // order list according to dependencies (iterate until list empty)
  while (storage.size() != 0) {
    for (size_t i = 0; i < storage.size(); ++i) {
      // get current task and preds
      task_t curr_task = storage[i].getTask();
      std::list<task_t> curr_pred = storage[i].getPredecessors();

      // if no preds, add to beginning + remove from storage
      if (curr_pred.empty()) {
        print_answer.push_front(curr_task);
        storage.erase(storage.begin() + i);
        i--;
        continue;
      }

      // if have preds, check if present via trackers
      int num_preds = curr_pred.size();
      int num_present = 0;
      int already_add = 0;

      // check current preds w/ current answers
      for (std::list<task_t>::iterator it = print_answer.begin();
           it != print_answer.end();
           ++it) {
        for (std::list<task_t>::iterator pit = curr_pred.begin(); pit != curr_pred.end();
             ++pit) {
          // if already in answer, update tracker
          if (*pit == *it) {
            num_present++;
          }
          // if all present, insert now + delete from storage
          if ((num_present == num_preds) && (already_add == 0)) {
            ++it;
            already_add = 1;
            print_answer.insert(it, curr_task);
            storage.erase(storage.begin() + i);
            break;
          }
        }
      }
    }
  }

  // print answer list
  int loc = 0;
  int size = print_answer.size();

  for (std::list<task_t>::iterator fit = print_answer.begin(); fit != print_answer.end();
       ++fit) {
    if (loc == (size - 1)) {
      std::cout << *fit;
      break;
    }
    else {
      std::cout << *fit << ", ";
      loc++;
    }
  }
  std::cout << '\n';
}
