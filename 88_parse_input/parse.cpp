#include "parse.hpp"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class invalid_input : public std::exception {
 private:
  const char * whats_wrong;

 public:
  invalid_input(const char * m) : whats_wrong(m){};
  // can also just have one return message for all errors
  virtual const char * what() const throw() { return whats_wrong; }
};

// stream insertion overload
std::ostream & operator<<(std::ostream & s, const item_t & array) {
  // get num values
  int num_values = array.second.size();

  // print out 1 key
  s << "key = " << array.first << '\n';
  s << "  values =";

  // print all values
  for (int i = 0; i < num_values; i++) {
    if (i == (num_values - 1)) {
      s << array.second[i];
    }
    else {
      s << array.second[i] << ';';
    }
  }

  return s;
}

void parseLine(const std::string & line) {
  // trackers
  int length = 0;
  int num_colons = 0;

  // get size of line + do checks
  while (line[length] != '\0') {
    if (line[length] == ':') {
      num_colons++;
      char next = line[(length + 1)];
      if ((next == ':') || (next == ',')) {
        throw invalid_input("Incorrect spacing after key colon\n");
      }
    }
    else if (line[length] == ',') {
      char next = line[(length + 1)];
      if ((next == ':') || (next == ',')) {
        throw invalid_input("Incorrect spacing after value's comma\n");
      }
    }
    length++;
  }

  std::vector<int> answer = std::vector<int>();
  answer.push_back(length);
  answer.push_back(num_colons);

  // make sure correct line format
  if (length == 0) {
    throw invalid_input("Empty line passed\n");
  }
  if (num_colons != 1) {
    throw invalid_input("Wrong number of colons present\n");
  }

  // create templates
  std::string key;
  std::vector<std::string> values = std::vector<std::string>();

  // get key (handles empty key)
  int loc = 0;
  while (line[loc] != ':') {
    key.push_back(line[loc]);
    loc++;
  }
  // key.push_back('\0');
  loc++;

  // handle if empty string for value
  std::string new_val;
  if (line[loc] == '\0') {
    new_val.push_back(' ');
    new_val.push_back('\n');
    values.push_back(new_val);
  }

  else {
    // handle non-empty values
    while (line[loc] != '\0') {
      if (line[loc] == ',') {
        values.push_back(new_val);
        new_val.clear();
        loc++;
      }
      else {
        new_val.push_back(line[loc]);
        loc++;
      }
    }
    new_val.push_back('\n');
    values.push_back(new_val);
  }

  // print typedef
  item_t itemPtr = item_t(key, values);
  std::cout << itemPtr;
}

// void checks(const std::vector<int> input) {
//   // check length of line
//   try {
//     if (input[0] == 0) {
//       throw invalid_input("Empty line passed\n");
//     }
//   }
//   catch (invalid_input & n) {
//     std::cerr << n.what();
//     exit(EXIT_FAILURE);
//   }

// // check colons
// try {
//   if (input[1] != 1) {
//     throw invalid_input("Wrong number of colons present\n");
//   }
// }
// catch (invalid_input & f) {
//   std::cerr << f.what();
//   exit(EXIT_FAILURE);
// }
// }

// main
int main(int argc, char ** argv) {
  // if not given/too many filenames
  try {
    if (argc != 2) {
      throw invalid_input("Wrong number of file args\n");
    }
  }

  catch (invalid_input & n) {
    std::cerr << n.what();
    exit(EXIT_FAILURE);
  }

  // check file opens
  try {
    FILE * file;
    if ((file = fopen(argv[1], "r"))) {
      fclose(file);
    }
    else {
      throw invalid_input("File didn't open\n");
    }
  }
  catch (invalid_input & f) {
    std::cerr << f.what();
    exit(EXIT_FAILURE);
  }

  // if given filename
  std::ifstream myFile;
  myFile.open(argv[1]);

  // make sure file opens + sort
  if (myFile.is_open()) {
    while (myFile) {
      // get line
      std::string myLine;

      while (std::getline(myFile, myLine)) {
        try {
          // pass line to parse
          parseLine(myLine);
        }
        catch (invalid_input & e) {
          std::cerr << e.what();
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
