#ifndef _GRAPH_SERIALIZATION_IVM198005_H
#define _GRAPH_SERIALIZATION_IVM198005_H

#include<string>
#include <unordered_map>
#include "vertex.h"

namespace graph_serialization {
	void deserialize(std::string& filename, std::unordered_map<unsigned int, vertex*>& map);
	void get_way_str(std::vector<unsigned int>& way, unsigned int& length, std::string& result);
	void get_no_way_str(unsigned int& start, unsigned int& target, std::string& result);
	unsigned int vertex_to_uint(std::string& value, const std::string& what);
}

#endif
