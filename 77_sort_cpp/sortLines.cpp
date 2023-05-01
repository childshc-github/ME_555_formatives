#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// store + parse + print function
void handler(std::istream & is) {
  // line
  std::string myLine;

  // vector
  std::vector<std::string> holder;

  // get the line
  while (std::getline(is, myLine)) {
    // store in vector
    holder.push_back(myLine);
  }

  // sort
  std::sort(holder.begin(), holder.end());

  // print vector (includes \n in holder)
  for (int s = 0; s < holder.size(); s++) {
    std::cout << holder[s] << '\n';
  }
}

// main
int main(int argc, char ** argv) {
  // standard input
  if (argc == 1) {
    handler(std::cin);
    return EXIT_SUCCESS;
  }

  // read from file
  else if (argc > 1) {
    for (int i = 1; i <= (argc - 1); i++) {
      // open file
      std::ifstream myFile;
      myFile.open(argv[i]);

      // make sure file opens + sort
      if (myFile.is_open()) {
        while (myFile) {
          handler(myFile);
        }
      }
      else {
        std::cerr << "Couldn't open file\n";
        return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  }

  std::cerr << "Nothing done.";
  return EXIT_FAILURE;
}
