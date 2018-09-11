#ifndef _DIJKSTRA_IVM198005_H
#define _DIJKSTRA_IVM198005_H
#include "vertex.h"
#include <vector>
#include <unordered_map>

namespace dijkstra {
	bool get_way(std::unordered_map<unsigned int, vertex*> verteces, unsigned int& start, unsigned int& target, std::vector<unsigned int>& way, unsigned int& length);
}

#endif
