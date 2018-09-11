#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include "vertex.h"
#include "nexception.h"
#include "graph_serialization.h"
#include "dijkstra.h"


int main(int argc, char* argv[])
{	
	if (argc != 4) {	
		std::cerr << "Invalid number of arguments - " << argc << ", command line must contain: [file with the graph described] [start node] [final vertex]" << std::endl;
		return -1;
	}

	std::string filename(argv[1]);

	try
	{
		unsigned int start = graph_serialization::vertex_to_uint(std::string(argv[2]), std::string("start vertex"));

		unsigned int target = graph_serialization::vertex_to_uint(std::string(argv[3]), std::string("target vertex"));

		std::unordered_map<unsigned int, vertex*> verteces;

		graph_serialization::deserialize(filename, verteces);

		std::vector<unsigned int> way;

		unsigned int length;

		std::string answ;

		if (dijkstra::get_way(verteces, start, target, way, length)) {
			graph_serialization::get_way_str(way, length, answ);			

			std::cout << answ << std::endl;

			return 0;
		}
		else {
			graph_serialization::get_no_way_str(start, target, answ);

			std::cerr << answ << std::endl;

			return -1;
		}		
	}
	catch (const nexception &ne)
	{
		std::cerr << ne.what() << std::endl;
	}
	
}


