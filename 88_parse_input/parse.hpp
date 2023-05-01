#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<std::string, std::vector<std::string> > item_t;

std::ostream & operator<<(std::ostream & s, const std::vector<item_t> & array);

void parseLine(const std::string & line);

void checks(const std::vector<int> input);

#endif
