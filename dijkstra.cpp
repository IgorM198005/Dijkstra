#include "nexception.h"
#include "dijkstra.h"
#include <string>
#include <set>
#include <algorithm> 

class VertexWeightComparision
{
public:
	bool operator() (const vertex* lhs, const vertex* rhs) const
	{
		if (lhs->weight == rhs->weight) return (lhs->id < rhs->id);

		return (lhs->weight < rhs->weight);
	}
};

typedef std::set<vertex*, VertexWeightComparision> dijkstra_queue;

void buildway(dijkstra_queue& queue, vertex* start, vertex* target);

bool dijkstra::get_way(std::unordered_map<unsigned int, vertex*> verteces, unsigned int& start, unsigned int& target, std::vector<unsigned int>& way, unsigned int& length)
{
	auto it = verteces.find(start);

	if (it == verteces.end()) throw nexception("the vertex with the identifier " + std::to_string(start) + " is missing in the given graph");

	vertex* vxs = it->second;

	it = verteces.find(target);

	if (it == verteces.end()) throw nexception("the vertex with the identifier " + std::to_string(target) + " is missing in the given graph");

	vertex* vxt = it->second;

	dijkstra_queue queue;

	for (const auto& vx_m : verteces) queue.insert(vx_m.second);

	queue.erase(queue.find(vxs));

	if (start != target)
	{
		vxs->weight = 0;

		vxs->considered = true;
	}

	buildway(queue, vxs, vxt);

	if (vxt->prev == NULL) return false;

	vertex* current = vxt;

	do
	{
		way.push_back(current->id);

		current = current->prev;
	}
	while (current != vxs);

	way.push_back(vxs->id);

	std::reverse(way.begin(), way.end());

	length = vxt->weight;

	return true;
}

void buildway(dijkstra_queue& queue, vertex* start, vertex* target)
{
	vertex* current = start;

	unsigned int weight = 0;
	
	for (;;)
	{
		unsigned int rm = std::numeric_limits<unsigned int>::max() - weight;

		for (auto const& value : current->edges)
		{
			if (value.first->considered) continue;

			if (value.second >= rm) throw nexception("The length of any path in the graph must be less than " + std::to_string(std::numeric_limits<unsigned int>::max()));

			unsigned int nw = weight + value.second;

			if (value.first->weight > nw)
			{
				queue.erase(queue.find(value.first));

				value.first->weight = nw;

				value.first->prev = current;

				queue.insert(value.first);
			}
		}

		if (queue.empty()) break;

		current = *(queue.begin());

		weight = current->weight;

		if (weight >= target->weight) break;

		queue.erase(queue.find(current));

		current->considered = true;
	}
}