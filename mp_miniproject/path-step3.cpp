#include "path_planning.hpp"

int main(int argc, char ** argv) {
  // check number of args
  if (argc != 5) {
    std::cerr << "Incorrect number of arguments given" << '\n';
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

  // format check obstacles file
  format_check_obs(argv[2]);

  // get all obstacles
  std::vector<Obstacle> all_obstacles = extract_obs(argv[2]);

  // check obstacles are in Graph
  obs_in_graph(all_obstacles, answer_Graph);

  // update Graph w/ obstacles
  answer_Graph.AddObstacles(all_obstacles, order_pstorage);

  // format check nodes + get
  unsigned int start_node = format_nodes(argv[3]);
  unsigned int end_node = format_nodes(argv[4]);

  // check nodes are in graph
  node_in_graph(start_node, answer_Graph);
  node_in_graph(end_node, answer_Graph);

  // find shortest path + print
  Dij_path(answer_Graph, start_node, end_node);

  return EXIT_SUCCESS;
}
