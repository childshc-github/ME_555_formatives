#include "path_planning.hpp"

// include all functions here
// Point methods
const unsigned int Point::returnID() const {
  return this->ID;
}
const double Point::returnxcord() const {
  return this->x_cord;
}
const double Point::returnycord() const {
  return this->y_cord;
}

// checks if valid decimal
void good_dot(std::string input) {
  // ensure no "." is alone + correct number
  int num_dot = 0;
  size_t loc = 0;
  size_t size = input.size();
  while (loc != size) {
    if (input[loc] == '.') {
      if ((input[(loc + 1)] < '0') || (input[(loc + 1)] > '9')) {
        std::cerr << "Lone decimal present in $nodes\n";
        exit(EXIT_FAILURE);
      }
    }
    loc++;
  }

  // check tracker (note: Node ID can't be a decimal)
  if (num_dot > 2) {
    std::cerr << "Incorrect number of decimals in $edges\n";
    exit(EXIT_FAILURE);
  }
}

// checks if valid negative sign
void good_neg(std::string input) {
  // ensure no "." is alone + correct number
  int num_neg = 0;
  size_t loc = 0;
  size_t size = input.size();
  while (loc != size) {
    if (input[loc] == '-') {
      if ((input[(loc + 1)] < '0') || (input[(loc + 1)] > '9')) {
        std::cerr << "Lone negative sign present in $nodes\n";
        exit(EXIT_FAILURE);
      }
    }
    loc++;
  }

  // check tracker (note: Node ID can't be a decimal)
  if (num_neg > 2) {
    std::cerr << "Incorrect number of negative signs in $edges\n";
    exit(EXIT_FAILURE);
  }
}

// checks if passed std::string is valid $nodes input
void is_valid_node(std::string input) {
  // track number of entries
  int num_spaces = 0;

  // loop through + check spacing + num entries
  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == ' ') {
      num_spaces++;
      continue;
    }
    // if a decimal, pass (already checked in good_dot)
    else if (input[i] == '.') {
      continue;
    }
    // skip negative signs (already check in good_neg)
    else if (input[i] == '-') {
      continue;
    }
    // if entry, make sure a number
    else if ((input[i] < '0') || (input[i] > '9')) {
      std::cerr << "Invalid entries in $nodes\n";
      exit(EXIT_FAILURE);
    }
  }

  // check tracker
  if (num_spaces != 2) {
    std::cerr << "Incorrect formatting in $nodes line\n";
    exit(EXIT_FAILURE);
  }
}

// checks if passed std::string is valid $edges input
void is_valid_edge(std::string input) {
  // track number of entries
  int num_spaces = 0;

  // loop through + check spacing + num entries
  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == ' ') {
      num_spaces++;
    }
    // all entries should be nums
    else if ((input[i] < '0') || (input[i] > '9')) {
      std::cerr << "Invalid entries in $edges\n";
      exit(EXIT_FAILURE);
    }
  }

  // check tracker
  if (num_spaces != 1) {
    std::cerr << "Incorrect formatting in $edges line\n";
    exit(EXIT_FAILURE);
  }
}

// get the location of when the $edges starts
int get_loc_edge(const char * filename) {
  //tracker
  int loc = 0;

  std::ifstream myFile;
  myFile.open(filename);
  if (myFile.is_open()) {
    while (myFile) {
      std::string myLine;

      // get one line at a time
      while (std::getline(myFile, myLine)) {
        if (myLine[0] != '$') {
          loc++;
        }
        else if (myLine[1] == 'n') {
          loc++;
        }
        else if (myLine[1] == 'e') {
          return loc;
        }
      }
    }
  }
  else {
    std::cerr << "Can't open obstacles file\n";
    exit(EXIT_FAILURE);
  }

  return loc;
}

// file format checker
void format_check(const char * filename) {
  // track line number + if reading nodes or edges
  int line_num = 0;
  int found_edge = 0;
  int num_nodes = 0;

  // loop through file
  std::ifstream myFile;
  myFile.open(filename);
  if (myFile.is_open()) {
    while (myFile) {
      std::string myLine;

      // get one line at a time
      while (std::getline(myFile, myLine)) {
        // ensure 1st line is "$nodes"
        if (line_num == 0) {
          std::string comp = "$nodes";
          if (myLine != comp) {
            std::cerr << "First line in file isn't $nodes\n";
            exit(EXIT_FAILURE);
          }
          line_num++;
        }
        // else, check input lines
        else {
          // if encounter another $, check valid + update tracker
          if (myLine[0] == '$') {
            std::string comp = "$edges";
            if (comp != myLine) {
              std::cerr << "Header $edges is incorrectly formatted\n";
              exit(EXIT_FAILURE);
            }
            found_edge++;
            line_num++;
          }
          // if node input, check 1 ID and 2 doubles w/ spacing
          else if (found_edge == 0) {
            // update tracker
            num_nodes++;
            // check no lone decimal
            good_dot(myLine);
            // check no lone negative sign
            good_neg(myLine);
            // check valid entries
            is_valid_node(myLine);
          }
          // if edges input, 2 IDs w/ spacing
          else if (found_edge > 0) {
            // if edge but no nodes
            if (num_nodes == 0) {
              std::cerr << "Edges given, but no nodes present\n";
              exit(EXIT_FAILURE);
            }
            // check valid entries
            is_valid_edge(myLine);
          }
        }
      }
    }
  }
  else {
    std::cerr << "Couldn't open file\n";
    exit(EXIT_FAILURE);
  }

  // check tracker
  if (found_edge > 1) {
    std::cerr << "Incorrect number of $nodes or $edges headers\n";
    exit(EXIT_FAILURE);
  }
}

// parse graph file - returns pair of storage node/vector
std::pair<std::vector<Point>, std::vector<std::vector<unsigned int> > > parse_graph(
    const char * filename) {
  // format check
  format_check(filename);
  int current = 0;

  // get index of $edges
  int edge_loc = get_loc_edge(filename);

  // storage of node IDs + coordinates
  std::vector<Point> point_storage = std::vector<Point>();

  // storage of edges
  std::vector<std::vector<unsigned int> > edge_storage =
      std::vector<std::vector<unsigned int> >();

  // open file + pass to parse via getline
  std::ifstream myFile;
  myFile.open(filename);
  if (myFile.is_open()) {
    while (myFile) {
      std::string myLine;
      while (std::getline(myFile, myLine)) {
        // skip headers
        if ((current == 0) || (current == edge_loc)) {
          current++;
        }

        // if a node, store
        else if (current < edge_loc) {
          // get ID
          std::vector<unsigned int> curr_ID = get_ID(myLine, true);
          unsigned int cID = curr_ID[0];

          // get coords
          std::vector<double> coords = get_cords(myLine);

          // make new class
          Point new_point = Point(cID, coords[0], coords[1]);

          // add to storage
          point_storage.push_back(new_point);

          current++;
        }

        // if an edge, store
        else if (current > edge_loc) {
          // get IDs
          std::vector<unsigned int> IDs = get_ID(myLine, false);

          // add to storage
          edge_storage.push_back(IDs);

          current++;
        }
      }
    }
  }
  else {
    std::cerr << "Couldn't open file\n";
    exit(EXIT_FAILURE);
  }

  // get ordered points in point storage by ID
  std::vector<Point> order_pstorage = order_point_storage(point_storage);

  // add both storage to pair + return
  std::pair<std::vector<Point>, std::vector<std::vector<unsigned int> > > answer;
  answer.first = order_pstorage;
  answer.second = edge_storage;
  return answer;
}

// converts std::strings to unsigned ints
unsigned int convert_to_ui(std::string input) {
  // calculate power of ten
  unsigned int answer = 0;
  int power_ten = 1;
  for (size_t i = 1; i < input.size(); i++) {
    power_ten = power_ten * 10;
  }

  // convert
  for (size_t i = 0; i < input.size(); i++) {
    input[i] = input[i] - '0';
    answer += (input[i] * power_ten);
    power_ten = power_ten / 10;
  }

  return answer;
}

// converts std::strings to doubles via stod
double convert_to_double(std::string input) {
  // convert std::string to char *
  const char * temp = input.c_str();

  // setup end point
  char * end;

  // extract num
  double answer;
  answer = strtod(temp, &end);

  return answer;
}

// given a line (node or edge via bool), extracts IDs
std::vector<unsigned int> get_ID(std::string input, bool isNode) {
  // template
  std::vector<unsigned int> answer = std::vector<unsigned int>();

  // if node line, get ID + return
  if (isNode == true) {
    std::string NodeID;
    int loc = 0;
    while (input[loc] != ' ') {
      // add to string
      NodeID.push_back(input[loc]);
      loc++;
    }
    // convert + add
    unsigned int newNode = convert_to_ui(NodeID);
    answer.push_back(newNode);
  }

  // if edge line, get both IDs + return
  else if (isNode == false) {
    std::string ID1;
    std::string ID2;
    int loc = 0;
    // get 1st ID
    while (input[loc] != ' ') {
      ID1.push_back(input[loc]);
      loc++;
    }
    loc++;

    // get 2nd ID
    while (input[loc] != '\0') {
      ID2.push_back(input[loc]);
      loc++;
    }

    // convert + add
    unsigned int a1 = convert_to_ui(ID1);
    unsigned int a2 = convert_to_ui(ID2);
    answer.push_back(a1);
    answer.push_back(a2);
  }

  // return extracted data
  return answer;
}

// given a node line, returns coords in vector
std::vector<double> get_cords(std::string input) {
  // templates
  std::vector<double> answer = std::vector<double>();
  std::string xloc;
  std::string yloc;
  int posn = 0;

  // iterate to start of 1st coord
  while (input[posn] != ' ') {
    posn++;
  }
  posn++;

  // get x
  while (input[posn] != ' ') {
    xloc.push_back(input[posn]);
    posn++;
  }
  posn++;

  // get y
  while (input[posn] != '\0') {
    yloc.push_back(input[posn]);
    posn++;
  }

  // convert
  double xc = convert_to_double(xloc);
  double yc = convert_to_double(yloc);

  // add to vector + return
  answer.push_back(xc);
  answer.push_back(yc);
  return answer;
}

// given a vector of Points, order via ID
std::vector<Point> order_point_storage(std::vector<Point> input) {
  // corner case: if empty or 1 entry
  if ((input.size() == 0) || (input.size() == 1)) {
    return input;
  }

  // sort
  int swapped = 0;
  do {
    swapped = 0;
    for (size_t i = 0; i < (input.size() - 1); i++) {
      Point first = input[i];
      Point second = input[(i + 1)];

      if (first.returnID() > second.returnID()) {
        swapped++;
        input[i] = second;
        input[(i + 1)] = first;
      }
    }
  } while (swapped > 0);
  return input;
}

// Point methods:
// Point constructor
Point::Point(unsigned int num, double x, double y) {
  ID = num;
  x_cord = x;
  y_cord = y;
}

// define Euclid distance calculator
double distanceFrom(std::vector<double> first, std::vector<double> second) {
  double x_diff = (first[0] - second[0]) * (first[0] - second[0]);
  double y_diff = (first[1] - second[1]) * (first[1] - second[1]);
  double answer = x_diff + y_diff;
  answer = sqrt(answer);
  return answer;
}

// Graph methods:
// Graph constructor (to total size)
Graph::Graph(size_t num_nodes) {
  // create num_nodes x num_nodes graph
  std::vector<double> row = std::vector<double>(num_nodes);
  std::vector<std::vector<double> > table = std::vector<std::vector<double> >();
  for (size_t i = 0; i < num_nodes; i++) {
    table.push_back(row);
  }

  // set all entries = infinity
  for (size_t i = 0; i < num_nodes; i++) {
    for (size_t s = 0; s < num_nodes; s++) {
      table[i][s] = INFINITY;
    }
  }

  // construct Graph
  map = table;
}

// add edge to map
void Graph::addEdge(std::vector<unsigned int> curr_edge, std::vector<Point> p_storage) {
  // get both IDs
  unsigned int ID1 = curr_edge[0];
  unsigned int ID2 = curr_edge[1];
  std::vector<double> coord1 = std::vector<double>();
  std::vector<double> coord2 = std::vector<double>();

  // get coords via ID
  for (size_t i = 0; i < p_storage.size(); i++) {
    // get 1st coord
    if (ID1 == p_storage[i].returnID()) {
      coord1.push_back(p_storage[i].returnxcord());
      coord1.push_back(p_storage[i].returnycord());
    }

    // get 2nd coord
    else if (ID2 == p_storage[i].returnID()) {
      coord2.push_back(p_storage[i].returnxcord());
      coord2.push_back(p_storage[i].returnycord());
    }
  }

  // calculate distance
  double answer = distanceFrom(coord1, coord2);

  // insert edge at both index
  map[ID1][ID2] = answer;
  map[ID2][ID1] = answer;
}

// return Row from Graph
const std::vector<double> Graph::returnRow(size_t index) const {
  // ensure index valid
  assert(index < this->map.size());

  // return requested vector
  return this->map[index];
}

// return size of graph (square)
size_t Graph::returnSize() const {
  return this->map.size();
}

// prints coordinates given a vector of Points
void print_coords(std::vector<Point> points) {
  for (size_t i = 0; i < points.size(); i++) {
    std::cout << '(' << points[i].returnxcord() << ',' << points[i].returnycord() << ") ";
  }
  std::cout << '\n';
}

// determines if a row has a distance entry
bool row_has_distance(std::vector<double> input) {
  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] != INFINITY) {
      return true;
    }
  }
  return false;
}

// << overload
std::ostream & operator<<(std::ostream & s, const Graph & rhs) {
  // formatted print
  for (size_t i = 0; i < rhs.returnSize(); i++) {
    // get current row
    std::vector<double> curr_row = rhs.returnRow(i);

    // determine if has entry
    bool entry = row_has_distance(curr_row);

    // if has entry, print
    if (entry) {
      // print ID (= iterator)
      s << i << ": ";

      // print all intersects
      for (size_t t = 0; t < curr_row.size(); t++) {
        if (curr_row[t] != INFINITY) {
          s << t << ',' << curr_row[t] << ' ';
        }
      }
    }

    // if no entry, indicate no edges
    else if (!entry) {
      // print ID + no intersects
      s << i << ": no edges";
    }

    s << '\n';
  }

  return s;
}

// format check start/end node args
unsigned int format_nodes(char * input) {
  // check entries via ASCII + convert to std::string
  std::string holder;
  int loc = 0;
  while (input[loc] != '\0') {
    if ((input[loc] < '0') || (input[loc] > '9')) {
      std::cerr << "Node argument has invalid chars\n";
      exit(EXIT_FAILURE);
    }
    else {
      holder.push_back(input[loc]);
      loc++;
    }
  }

  // std::string -> unsigned int
  unsigned int answer = convert_to_ui(holder);
  return answer;
}

// check if node in map
void node_in_graph(unsigned int ident, Graph table) {
  // if ident < graph size, node exists
  if (ident >= table.returnSize()) {
    std::cerr << "Given node doesn't exist in map\n";
    exit(EXIT_FAILURE);
  }
}

// checks if table is empty
void have_empty_map(Graph input) {
  // check if all entries are INFINITY
  for (size_t i = 0; i < input.returnSize(); i++) {
    // get row
    std::vector<double> row = input.returnRow(i);

    // check each entry
    for (size_t t = 0; t < row.size(); t++) {
      if (row[t] != INFINITY) {
        return;
      }
    }
  }

  // if no entries
  std::cerr << "No path possible - map has no edges\n";
  exit(EXIT_FAILURE);
}

// determines if current node is in visited
bool in_visited(unsigned int current, std::set<unsigned int> v) {
  // iterate + compare
  for (std::set<unsigned int>::iterator it = v.begin(); it != v.end(); ++it) {
    if (*it == current) {
      return true;
    }
  }

  // if not in visited
  return false;
}

// Graph return adjacents
std::vector<unsigned int> returnAdj(Graph g, unsigned int index) {
  // template
  std::vector<unsigned int> answer = std::vector<unsigned int>();

  // get row and size + check if has adjac
  std::vector<double> row = g.returnRow(index);
  size_t gsize = g.returnSize();
  for (size_t i = 0; i < gsize; i++) {
    if (row[i] != INFINITY) {
      answer.push_back(i);
    }
  }

  // return
  return answer;
}

// Path constructor
Path::Path(std::vector<unsigned int> p,
           Graph g,
           unsigned int EndN,
           bool wantED,
           const char * filename) {
  // update path
  path = p;

  // calculate distance
  size_t num_nodes = this->path.size();
  double answer = 0;

  // find distance between each node
  for (size_t i = 0; i < (num_nodes - 1); i++) {
    // get both IDs
    unsigned int n1 = this->path[i];
    unsigned int n2 = this->path[(i + 1)];

    // get ID row from g (either ID is fine)
    std::vector<double> row = g.returnRow(n1);

    // find distance between both in graph
    double dist = row[n2];
    answer += dist;
  }

  // update distance
  distance = answer;

  // check if need to find distance to end
  if (wantED == false) {
    distance_from_end = INFINITY;
    return;
  }

  // find distance from end node (may not connect so need Euclid dist)
  // get Points
  std::pair<std::vector<Point>, std::vector<std::vector<unsigned int> > > storage =
      parse_graph(filename);
  std::vector<Point> allPs = storage.first;
  size_t number_P = allPs.size();
  size_t numIP = p.size();

  // get starting ID + cords
  unsigned int startID = p[(numIP - 1)];

  // handle end -> end
  if (startID == EndN) {
    distance_from_end = INFINITY;
    return;
  }

  std::vector<double> scords = std::vector<double>();
  std::vector<double> ecords = std::vector<double>();
  for (size_t i = 0; i < number_P; i++) {
    if (allPs[i].returnID() == startID) {
      double sx = allPs[i].returnxcord();
      double sy = allPs[i].returnycord();
      scords.push_back(sx);
      scords.push_back(sy);
    }
    else if (allPs[i].returnID() == EndN) {
      double ex = allPs[i].returnxcord();
      double ey = allPs[i].returnycord();
      ecords.push_back(ex);
      ecords.push_back(ey);
    }
  }

  // calculate + update
  distance_from_end = distanceFrom(scords, ecords);
}

// return path
std::vector<unsigned int> Path::returnPath() const {
  return this->path;
}

// return distance of path
double Path::returnDistance() const {
  return this->distance;
}

// print Path with/without distance calculation
void Path::printPath(bool outputODist) const {
  // get path nodes
  std::vector<unsigned int> cpath = this->path;

  // print each node in path
  size_t length = cpath.size();
  for (size_t i = 0; i < length; i++) {
    if (i == (length - 1)) {
      std::cout << cpath[i] << ' ';
    }
    else {
      std::cout << cpath[i] << ", ";
    }
  }

  // print distance
  std::cout << ": " << this->distance;

  // if only want path distance
  if (outputODist == true) {
    std::cout << '\n';
  }

  // if request end distane
  if (outputODist == false) {
    std::cout << " (current path distance), " << this->returnDistanceEnd();
    std::cout << " (distance from end node)" << '\n';
  }
}

// determine priorty queue of Path vectors w/ operator overload
struct ComparePath {
  bool operator()(const Path & p1, const Path & p2) const {
    if (p1.returnDistance() == p2.returnDistance()) {
      std::vector<unsigned int> firstp = p1.returnPath();
      std::vector<unsigned int> secondp = p2.returnPath();
      for (size_t i = 0; i < firstp.size(); i++) {
        if (firstp[i] < secondp[i]) {
          return false;
        }
      }
      return true;
    }

    else {
      return p1.returnDistance() > p2.returnDistance();
    }
  }
};

// determine best path - prints step paths + distance
void Dij_path(Graph table, unsigned int start, unsigned int end) {
  // if start=end node
  if (start == end) {
    std::cout << "The start and end node are the same, so distance = 0\n";
    return;
  }

  // check if table empty
  have_empty_map(table);

  // check start node has at least 1 edge
  std::vector<double> start_row = table.returnRow(start);
  if (!row_has_distance(start_row)) {
    std::cerr << "Start node has no edges- no path exists\n";
    exit(EXIT_FAILURE);
  }

  // check final node has at least 1 edge
  std::vector<double> end_row = table.returnRow(end);
  if (!row_has_distance(end_row)) {
    std::cerr << "End node has no edges- no path exists\n";
    exit(EXIT_FAILURE);
  }

  // print starting conditions
  std::cout << "Starting at node " << start << " and reaching for node " << end << '\n';

  // create 1st node Path
  std::vector<unsigned int> firstv = std::vector<unsigned int>();
  firstv.push_back(start);
  Path firstp = Path(firstv, table, 0, false, "none");

  // store Paths template
  std::priority_queue<Path, std::vector<Path>, ComparePath> all_paths;

  // Dij search
  // ------------------------------------------------
  // create worklist ordered by distance (same = prioritize lowest ID)
  std::priority_queue<Path, std::vector<Path>, ComparePath> todo;

  // track visited nodes
  std::set<unsigned int> visited;

  // add first Path to worklist
  todo.push(firstp);

  while (!todo.empty()) {
    // get current values + remove from worklist
    Path currentPClass = todo.top();
    todo.pop();
    std::vector<unsigned int> currentPath = currentPClass.returnPath();
    size_t length_path = currentPath.size() - 1;
    unsigned int currentNode = currentPath[length_path];

    // if has end node, add to pqueue storage
    if (currentNode == end) {
      all_paths.push(currentPClass);
    }

    // if node not visited, add all adjacents + add to todo list
    else if (!in_visited(currentNode, visited)) {
      visited.insert(currentNode);
      std::vector<unsigned int> adjacents = returnAdj(table, currentNode);
      // if adjacent not visited, create new path class + add to worklist
      for (size_t i = 0; i < adjacents.size(); i++) {
        if (!in_visited(adjacents[i], visited)) {
          std::vector<unsigned int> update_Path = currentPath;
          update_Path.push_back(adjacents[i]);
          Path update_Path_class = Path(update_Path, table, 0, false, "none");
          todo.push(update_Path_class);
          update_Path_class.printPath(true);
        }
      }
    }
  }

  // return top of priority queue storage
  if (all_paths.size() > 0) {
    std::cout << "Shortest path found: \n";
    Path answer = all_paths.top();
    answer.printPath(true);
    return;
  }

  // if no paths exist
  std::cerr << "No path exists\n";
  exit(EXIT_FAILURE);
}

// checks line in obstacles file for formatting
void good_obs_lines(std::string input) {
  // trackers
  int num_spaces = 0;

  // loop + check
  size_t length = input.size();
  for (size_t i = 0; i < length; i++) {
    // track spaces
    if (input[i] == ' ') {
      num_spaces++;
    }

    // skip dots and negs
    else if ((input[i] == '.') || (input[i] == '-')) {
      continue;
    }

    // type check entries
    else if ((input[i] < '0') || (input[i] > '9')) {
      std::cerr << "Invalid entries in obstacles file\n";
      exit(EXIT_FAILURE);
    }
  }

  // check has > 1 ID
  if (num_spaces == 0) {
    std::cerr << "Only one node given in obstacles line\n";
    exit(EXIT_FAILURE);
  }
}

// makes sure a string doesn't have 2 consecutive spaces
void good_space(std::string input) {
  size_t loc = 0;
  size_t size = input.size();
  while (loc != size) {
    if (input[loc] == ' ') {
      if ((input[(loc + 1)] < '0') || (input[(loc + 1)] > '9')) {
        std::cerr << "Double space or invalid node type present in obstacles file\n";
        exit(EXIT_FAILURE);
      }
    }
    loc++;
  }
}

// format check obstacle file
void format_check_obs(const char * filename) {
  // tracker
  int line_num = 0;

  // loop through file
  std::ifstream myFile;
  myFile.open(filename);
  if (myFile.is_open()) {
    while (myFile) {
      std::string myLine;

      // get one line at a time
      while (std::getline(myFile, myLine)) {
        // make sure 1st line is correct header
        if (line_num == 0) {
          std::string comp = "$obstacles";
          if (myLine != comp) {
            std::cerr
                << "First line (header) in obstacles input is not formatted correctly.\n";
            exit(EXIT_FAILURE);
          }
          line_num++;
        }

        // if another header, throw error
        else if (myLine[0] == '$') {
          std::cerr << "More than one header in obstacles file\n";
          exit(EXIT_FAILURE);
        }

        // if empty line, throw error
        else if (myLine[0] == ' ') {
          std::cerr << "Blank line in obstacles file\n";
          exit(EXIT_FAILURE);
        }

        // if ID line, check
        else {
          // check good decimal format
          good_dot(myLine);

          // check good neg sign format
          good_neg(myLine);

          // check spacing is good
          good_space(myLine);

          // check inputs are good
          good_obs_lines(myLine);

          line_num++;
        }
      }
    }
  }
  else {
    std::cerr << "Can't open obstacles file\n";
    exit(EXIT_FAILURE);
  }
}

// Obstacle class constructor
Obstacle::Obstacle(std::vector<unsigned int> input) {
  // given valid obstacle list, create class
  o_IDs = input;
}

// return Obstacle vector
std::vector<unsigned int> Obstacle::returnObs() const {
  return this->o_IDs;
}

// Obstacle method - return number of obstacles
size_t Obstacle::returnNumObs() const {
  std::vector<unsigned int> row = this->o_IDs;
  return row.size();
}

// given an Obstacle, makes sure no repeats IDs
void check_ob_repeat(Obstacle input) {
  // get IDs + track
  std::vector<unsigned int> obstacles = input.returnObs();
  size_t length = obstacles.size();

  // loop + make sure no repeats
  for (size_t i = 0; i < length; i++) {
    unsigned int curr = obstacles[i];
    for (size_t t = 0; t < length; t++) {
      // skip current compare ID
      if (t == i) {
        t++;
      }

      // compare
      if (curr == obstacles[t]) {
        std::cerr << "Repeat obstacle in input file\n";
        exit(EXIT_FAILURE);
      }
    }
  }
}

// returns obstacles from std::string
Obstacle get_ob(std::string input) {
  // trackers
  int posn = 0;
  int length = input.size();
  std::vector<unsigned int> storage = std::vector<unsigned int>();

  // loop + get IDs (convert char -> unsigned int)
  while (posn < length) {
    // move past spaces
    if (input[posn] == ' ') {
      posn++;
    }

    // template
    std::string obsID;

    // get ID
    while (input[posn] != ' ') {
      if (input[posn] == '\0') {
        break;
      }
      obsID.push_back(input[posn]);
      posn++;
    }

    // convert
    unsigned int to_add = convert_to_ui(obsID);

    // store
    storage.push_back(to_add);
  }

  // create Obstacle class
  Obstacle new_obstacle = Obstacle(storage);

  // make sure no repeats
  check_ob_repeat(new_obstacle);

  // return
  return new_obstacle;
}

// extract obstacle data from file
std::vector<Obstacle> extract_obs(char * filename) {
  // trackers
  int line_num = 0;
  std::vector<Obstacle> answer = std::vector<Obstacle>();

  // loop through file
  std::ifstream myFile;
  myFile.open(filename);
  if (myFile.is_open()) {
    while (myFile) {
      std::string myLine;

      // get one line at a time
      while (std::getline(myFile, myLine)) {
        // skip header line
        if (line_num == 0) {
          line_num++;
        }

        // if line w/ obstructs, extract + store
        else {
          // get obstacles
          Obstacle new_ob = get_ob(myLine);

          // add to answer
          answer.push_back(new_ob);
        }
      }
    }
  }
  else {
    std::cerr << "Can't open obstacles file\n";
    exit(EXIT_FAILURE);
  }

  return answer;
}

// checks obstacle cords exist in graph
void obs_in_graph(std::vector<Obstacle> obs, Graph g) {
  // get number of Obstacle classes
  size_t num_Cobs = obs.size();

  // get number of IDs
  size_t max_ID = g.returnSize();

  // if Obstacle IDs < max ID num, then valid
  for (size_t i = 0; i < num_Cobs; i++) {
    size_t currObs = obs[i].returnNumObs();
    if (currObs > max_ID) {
      std::cerr << "Obstacles list contains non-existent nodes\n";
      exit(EXIT_FAILURE);
    }
  }
}

// Edge constructor
Edge::Edge(unsigned int ID1, unsigned int ID2, std::vector<Point> pcs) {
  point1 = ID1;
  point2 = ID2;
  allPoints = pcs;
}

// return request Point ID info from vector
Point Edge::returnFromAllPoints(unsigned int ID) const {
  // loop + find requested point
  size_t length = this->allPoints.size();
  for (size_t i = 0; i < length; i++) {
    if (ID == this->allPoints[i].returnID()) {
      return this->allPoints[i];
    }
  }
  std::cerr << "Requested obstacle ID is not in graph\n";
  exit(EXIT_FAILURE);
}

// Edge method: calculates slope truths for orientation
// returns 0 if collinear
// returns 1 if CCW
// returns 2 if Cw
int Edge::returnSlope(unsigned int first, unsigned int second, unsigned int third) const {
  // get Point class
  Point p = this->returnFromAllPoints(first);
  Point q = this->returnFromAllPoints(second);
  Point r = this->returnFromAllPoints(third);

  // calculate slope
  double answer =
      (q.returnycord() - p.returnycord()) * (r.returnxcord() - q.returnxcord());
  answer -= ((q.returnxcord() - p.returnxcord()) * (r.returnycord() - q.returnycord()));

  // return collinear
  if (answer == 0) {
    return 0;
  }

  // return CCW
  if (answer < 0) {
    return 1;
  }

  // return Cw
  return 2;
}

// check if collinear projection conditions are met
bool Edge::returnColl(unsigned int first, unsigned int second, unsigned int third) const {
  // get Point classes
  Point p = this->returnFromAllPoints(first);
  Point q = this->returnFromAllPoints(second);
  Point r = this->returnFromAllPoints(third);

  // get coordinates
  double px = p.returnxcord();
  double py = p.returnycord();
  double qx = q.returnxcord();
  double qy = q.returnycord();
  double rx = r.returnxcord();
  double ry = r.returnycord();

  // check if point q lies on pr via projection
  if (qx <= std::max(px, rx) && qx >= std::min(px, rx) && qy <= std::max(py, ry) &&
      qy >= std::min(py, ry)) {
    return true;
  }

  // if q not on segment
  return false;
}

// determines if orientation condition true for all criteria
bool Edge::EdgeOrient(unsigned int point3, unsigned int point4) const {
  // determine if (ID1, ID2, ID3) & (ID1, ID2, ID4) diff orient:
  // find orient (ID1, ID2, ID3)
  int slope1 = this->returnSlope(this->point1, this->point2, point3);

  // find orient (ID1, ID2, ID4)
  int slope2 = this->returnSlope(this->point1, this->point2, point4);

  // determine if (ID3, ID4, ID1) & (ID3, ID4, ID2) diff orient:
  // find orient (ID3, ID4, ID1)
  int slope3 = this->returnSlope(point3, point4, this->point1);

  // find orient (ID3, ID4, ID2)
  int slope4 = this->returnSlope(point3, point4, this->point2);

  // general case
  if ((slope1 != slope2) && (slope3 != slope4)) {
    return true;
  }

  // special case
  if ((slope1 == 0) && (returnColl(this->point1, point3, this->point2))) {
    return true;
  }
  if ((slope2 == 0) && (returnColl(this->point1, point4, this->point2))) {
    return true;
  }
  if ((slope3 == 0) && (returnColl(point3, this->point1, point4))) {
    return true;
  }
  if ((slope4 == 0) && (returnColl(point3, this->point2, point4))) {
    return true;
  }

  // if not diff
  return false;
}

// Graph method: iterate + update based on obstacles
void Graph::AddObstacles(std::vector<Obstacle> obs, std::vector<Point> PCs) {
  // get number of obstacles
  size_t total_obs = obs.size();

  // loop through all obstacles
  for (size_t i = 0; i < total_obs; i++) {
    // get current obstacle
    std::vector<unsigned int> currOb = obs[i].returnObs();

    // for each segment (pair) in obstacle (-1 so don't index outside)
    size_t size_curr_ob = obs[i].returnNumObs() - 1;
    for (size_t t = 0; t < size_curr_ob; t++) {
      // get IDs of pair
      unsigned int ID1 = currOb[t];
      unsigned int ID2 = currOb[(t + 1)];

      // create an Edge w/ IDs and node locations
      Edge currObsE = Edge(ID1, ID2, PCs);

      // for each segment in current graph
      size_t length_Graph = this->returnSize() - 1;
      for (size_t n = 0; n < length_Graph; n++) {
        for (size_t f = 0; f < length_Graph; f++) {
          // get IDs of pair
          unsigned int ID3 = n;
          unsigned int ID4 = f;

          // don't check don't have edge or same node
          if ((this->map[ID3][ID4] == INFINITY) || (ID3 == ID4)) {
            continue;
          }

          // remove this Graph class edge in Graph
          if (currObsE.EdgeOrient(ID3, ID4)) {
            this->map[ID3][ID4] = INFINITY;
            this->map[ID4][ID3] = INFINITY;
            std::cout << "Obstacle is blocking edge " << ID3 << " -> " << ID4 << '\n';
          }
        }
      }
    }
  }
}

// format check A* requests
void valid_AReq(char * request) {
  // check length
  int size = 0;
  while (request[size] != '\0') {
    size++;
  }
  if (size > 2) {
    std::cerr << "Incorrect format of A* request (too long).\n";
    exit(EXIT_FAILURE);
  }

  // check -
  if (request[0] != '-') {
    std::cerr << "Incorrect format of A* request (bad dash).\n";
    exit(EXIT_FAILURE);
  }

  // check a
  if (request[1] != 'a') {
    std::cerr << "Incorrect format of A* request (bad a).\n";
    exit(EXIT_FAILURE);
  }

  std::cout << "A* algorithm requested successfully\n";
}

// returns Path end distance
double Path::returnDistanceEnd() const {
  return this->distance_from_end;
}

// priority queue ordering for A* (order via distance from end node)
struct ComparePathA {
  bool operator()(const Path & p1, const Path & p2) const {
    // get distances currPath + distance to end
    double curr1 = p1.returnDistance() + p1.returnDistanceEnd();
    double curr2 = p2.returnDistance() + p2.returnDistanceEnd();

    // if same, prioritize low ID
    if (curr1 == curr2) {
      std::vector<unsigned int> firstp = p1.returnPath();
      std::vector<unsigned int> secondp = p2.returnPath();
      for (size_t i = 0; i < firstp.size(); i++) {
        if (firstp[i] < secondp[i]) {
          return false;
        }
      }
      return true;
    }

    // if distances not same
    else {
      return curr1 > curr2;
    }
  }
};

// A* path
void Astar_path(Graph table, unsigned int start, unsigned int end, char * fileN) {
  // if start=end node
  if (start == end) {
    std::cout << "The start and end node are the same, so distance = 0\n";
    return;
  }

  // check if table empty
  have_empty_map(table);

  // check start node has at least 1 edge
  std::vector<double> start_row = table.returnRow(start);
  if (!row_has_distance(start_row)) {
    std::cerr << "Start node has no edges- no path exists\n";
    exit(EXIT_FAILURE);
  }

  // check final node has at least 1 edge
  std::vector<double> end_row = table.returnRow(end);
  if (!row_has_distance(end_row)) {
    std::cerr << "End node has no edges- no path exists\n";
    exit(EXIT_FAILURE);
  }

  // print starting conditions
  std::cout << "Starting at node " << start << " and reaching for node " << end << '\n';

  // create 1st node Path
  std::vector<unsigned int> firstv = std::vector<unsigned int>();
  firstv.push_back(start);
  Path firstp = Path(firstv, table, end, true, fileN);

  // store Paths template - queue
  std::priority_queue<Path, std::vector<Path>, ComparePathA> all_paths;

  // A* search
  // ------------------------------------------------
  // create worklist ordered by distance (same = prioritize lowest ID)
  std::priority_queue<Path, std::vector<Path>, ComparePath> todo;

  // track visited nodes
  std::set<unsigned int> visited;

  // add first Path to worklist
  todo.push(firstp);

  while (!todo.empty()) {
    // get current values + remove from worklist
    Path currentPClass = todo.top();
    todo.pop();
    std::vector<unsigned int> currentPath = currentPClass.returnPath();
    size_t length_path = currentPath.size() - 1;
    unsigned int currentNode = currentPath[length_path];

    // if has end node, add to pqueue storage
    if (currentNode == end) {
      all_paths.push(currentPClass);
    }

    // if node not visited, add all adjacents + add to todo list
    else if (!in_visited(currentNode, visited)) {
      visited.insert(currentNode);
      std::vector<unsigned int> adjacents = returnAdj(table, currentNode);
      // if adjacent not visited, create new path class + add to worklist
      for (size_t i = 0; i < adjacents.size(); i++) {
        if (!in_visited(adjacents[i], visited)) {
          std::vector<unsigned int> update_Path = currentPath;
          update_Path.push_back(adjacents[i]);
          Path update_Path_class = Path(update_Path, table, end, true, fileN);
          todo.push(update_Path_class);
          update_Path_class.printPath(false);
        }
      }
    }
  }

  // return top of priority queue storage
  if (all_paths.size() > 0) {
    std::cout << "Shortest path found: \n";
    Path answer = all_paths.top();
    answer.printPath(true);
    return;
  }

  // if no paths exist
  std::cerr << "No path exists\n";
  exit(EXIT_FAILURE);
}
