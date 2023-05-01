#ifndef __PATH_PLANNING_H__
#define __PATH_PLANNING_H__

#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// independent functions
int get_loc_edge(const char * filename);
void format_check(const char * filename);
std::vector<unsigned int> get_ID(std::string input, bool isNode);
std::vector<double> get_cords(std::string input);
double distanceFrom(std::vector<double> first, std::vector<double> second);
unsigned int format_nodes(char * input);
void format_check_obs(const char * filename);
void valid_AReq(char * request);

// node info class
class Point {
 private:
  // node ID
  unsigned int ID;
  // positions
  double x_cord;
  double y_cord;

 public:
  // constructor
  Point(unsigned int num, double x, double y);
  // return values
  const unsigned int returnID() const;
  const double returnxcord() const;
  const double returnycord() const;
};

// obstacle positioning class
class Obstacle {
 private:
  std::vector<unsigned int> o_IDs;

 public:
  // constructor
  Obstacle(std::vector<unsigned int> input);
  // return obstacles
  std::vector<unsigned int> returnObs() const;
  // return number of obstacles
  size_t returnNumObs() const;
};

// node distances as 3D vector class
class Graph {
 private:
  // vector table of intersect distances
  std::vector<std::vector<double> > map;

 public:
  // constructor
  Graph(size_t num_nodes);
  // add edge to map
  void addEdge(std::vector<unsigned int> curr_edge, std::vector<Point> p_storage);
  // return values
  const std::vector<double> returnRow(size_t index) const;
  // return size of map
  size_t returnSize() const;
  // accomodate obstacles
  void AddObstacles(std::vector<Obstacle> obs, std::vector<Point> all_Points);
};

// path to end node class
class Path {
 private:
  std::vector<unsigned int> path;
  double distance;
  double distance_from_end;

 public:
  // constructor
  Path(std::vector<unsigned int> p,
       Graph g,
       unsigned int endN,
       bool wantED,
       const char * filename);
  // return path
  std::vector<unsigned int> returnPath() const;
  // return distance of path
  double returnDistance() const;
  // print class
  void printPath(bool outputDist) const;
  // return end distance
  double returnDistanceEnd() const;
};

// distances + orientation class
class Edge {
 private:
  unsigned int point1;
  unsigned int point2;
  std::vector<Point> allPoints;

 public:
  // constructor
  Edge(unsigned int ID1, unsigned int ID2, std::vector<Point> pcs);
  // orientation method
  bool EdgeOrient(unsigned int point3, unsigned int point4) const;
  // return slope condition
  int returnSlope(unsigned int first, unsigned int second, unsigned int third) const;
  // return collinear condition
  bool returnColl(unsigned int first, unsigned int second, unsigned int third) const;
  // return Point via ID
  Point returnFromAllPoints(unsigned int ID) const;
};

// class-dependent functions
std::pair<std::vector<Point>, std::vector<std::vector<unsigned int> > > parse_graph(
    const char * filename);
std::vector<Point> order_point_storage(std::vector<Point> input);
void print_coords(std::vector<Point> points);
void node_in_graph(unsigned int ident, Graph table);
std::vector<unsigned int> returnAdj(Graph g, unsigned int index);
void Dij_path(Graph table, unsigned int start, unsigned int end);
std::vector<Obstacle> extract_obs(char * filename);
void obs_in_graph(std::vector<Obstacle> obs, Graph g);
void Astar_path(Graph table, unsigned int start, unsigned int end, char * file);

// overloaded << to print map
std::ostream & operator<<(std::ostream & s, const Graph & rhs);

#endif
