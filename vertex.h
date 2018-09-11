#ifndef _VERTEX_IVM198005_H
#define _VERTEX_IVM198005_H

#include <vector>
#include <limits>

struct vertex
{
	vertex(unsigned int vx_id) : id(vx_id)
	{
		this->weight = std::numeric_limits<unsigned int>::max();

		this->considered = false;

		this->prev = NULL;
	}
	unsigned int id;
	unsigned int weight;
	bool considered;
	vertex* prev;
	std::vector<std::pair<vertex*, unsigned int>> edges;
};

#endif
