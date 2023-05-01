#include "path_planning.hpp"

int main(int argc, char ** argv) {
  // check number of args
  if (argc != 4) {
    std::cerr << "Incorrect number of args given" << '\n';
    exit(EXIT_FAILURE);
  }

  // check + get nodes/edges
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

  // format check start + goal node (unsigned ints)
  unsigned int start_node = format_nodes(argv[2]);
  unsigned int end_node = format_nodes(argv[3]);

  // ensure nodes are in graph
  node_in_graph(start_node, answer_Graph);
  node_in_graph(end_node, answer_Graph);

  // find best path + print
  Dij_path(answer_Graph, start_node, end_node);

  return EXIT_SUCCESS;
}
