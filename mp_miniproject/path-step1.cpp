#include "path_planning.hpp"

// include only main here
int main(int argc, char ** argv) {
  // check number of args
  if (argc != 2) {
    std::cerr << "Incorrect number of files given" << '\n';
    exit(EXIT_FAILURE);
  }

  // format check + parse file
  std::pair<std::vector<Point>, std::vector<std::vector<unsigned int> > > storage =
      parse_graph(argv[1]);

  // get storage
  std::vector<Point> order_pstorage = storage.first;
  std::vector<std::vector<unsigned int> > edge_storage = storage.second;

  // create Graph
  Graph answer_Graph = Graph(order_pstorage.size());

  // add edges for each vector in edge storage
  for (size_t i = 0; i < edge_storage.size(); i++) {
    answer_Graph.addEdge(edge_storage[i], order_pstorage);
  }

  // print coords
  print_coords(order_pstorage);

  // print graph w/ overload
  std::cout << answer_Graph;

  return EXIT_SUCCESS;
}
