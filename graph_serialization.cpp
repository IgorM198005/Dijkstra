#include <string>
#include <stdexcept>
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cctype>
#include "graph_serialization.h"
#include "nexception.h"

const std::string VERTEX1 = "vertext1";
const std::string VERTEX2 = "vertext2";
const std::string DISTANCE = "distance";

std::string get_error_message_row(unsigned int& rownum);

std::string get_error_message_edge(unsigned int& rownum, const std::string& what, bool ext);

std::string get_error_message_vertex(const std::string& what);

unsigned int edges_to_uint(std::string& value, unsigned int& rownum, const std::string& what, bool ext);

unsigned int convert_to_uint(std::string& value);

void graph_serialization::deserialize(std::string& filename, std::unordered_map<unsigned int, vertex*>& map)
{
	std::ifstream file;
	file.open(filename);

	if (!file)
	{
		throw nexception("Can't open file for read, - no such file or  access denied or locked by another user");
	}

	unsigned int maxrowno = std::numeric_limits<unsigned int>::max();
	std::string str;
	unsigned int rowno = 0;
	bool ext = false;

	typename std::unordered_map<unsigned int, vertex*>::size_type maxvertex = map.max_size();

	while (std::getline(file, str))
	{
		if (!ext)
		{
			if (rowno < maxrowno)
			{
				rowno++;
			}
			else
			{
				ext = true;
			}
		}		

		std::stringstream ss(str);

		std::string item;

		if (!std::getline(ss, item, ';')) throw nexception(get_error_message_row(rowno));

		unsigned int vix = edges_to_uint(item, rowno, VERTEX1, ext);

		if (!std::getline(ss, item, ';')) throw nexception(get_error_message_row(rowno));

		unsigned int wt = edges_to_uint(item, rowno, DISTANCE, ext);

		if (!std::getline(ss, item, ';')) throw nexception(get_error_message_row(rowno));

		unsigned int viy = edges_to_uint(item, rowno, VERTEX2, ext);

		if (!ss.eof()) throw nexception(get_error_message_row(rowno));

		vertex* vy;

		auto it = map.find(viy);

		if (it == map.end())
		{
			if (map.size() == map.max_size()) throw nexception("the graph can contain no more than " + std::to_string(map.max_size()) + " vertices");

			map.insert(std::pair<unsigned int, vertex*>(viy, vy = new vertex(viy)));
		}
		else
		{
			vy = it->second;
		}

		vertex* vx;

		it = map.find(vix);

		if (it == map.end())
		{
			if (map.size() == map.max_size()) throw nexception("the graph can contain no more than " + std::to_string(map.max_size()) + " vertices");

			map.insert(std::pair<unsigned int, vertex*>(vix, vx = new vertex(vix)));
		}
		else
		{
			vx = it->second;
		}

		if (vx->edges.size() == vx->edges.max_size()) throw nexception("from the vertex there can be no more than " + std::to_string(vx->edges.max_size()) + " edges");

		vx->edges.push_back(std::pair<vertex*, unsigned int>(vy, wt));
	}	
}

unsigned int edges_to_uint(std::string& value, unsigned int& rownum, const std::string& what, bool ext)
{
	try
	{
		return convert_to_uint(value);
	}
	catch (const std::invalid_argument&)
	{
		throw nexception(get_error_message_edge(rownum, what, ext));
	}
	catch (std::out_of_range&)
	{
		throw nexception(get_error_message_edge(rownum, what, ext));
	}
}

unsigned int convert_to_uint(std::string& value)
{
	std::size_t pos;
	if ((value.length() < 1) || std::isspace(value[0])) throw std::invalid_argument("ivalid value format");
	unsigned long lresult = std::stoul(value, &pos, 10);
	if (pos != value.length()) throw std::invalid_argument("ivalid value format");
	unsigned int result = lresult;
	if (result != lresult) throw std::invalid_argument("ivalid value format");
	return  result;
}

void graph_serialization::get_way_str(std::vector<unsigned int>& way, unsigned int& length, std::string& result)
{
	std::stringstream ss;

	ss << "the path from the vertex " << *(way.begin()) << " to " << *(way.rbegin()) << ": " << *(way.begin());

	for (std::vector<unsigned int>::size_type i = 1; i != way.size(); i++) ss << "->" << way[i];

	ss << ", distance: " << length;

	result = ss.str();
}

void graph_serialization::get_no_way_str(unsigned int& start, unsigned int& target, std::string& result)
{
	result = "the path from the vertex " + std::to_string(start) + " to the vertex " + std::to_string(target) + " does not exist in the given graph";
}

std::string get_error_message_row(unsigned int& rownum)
{
	return  "Line number " + std::to_string(rownum) + " does not match the format - vertex1;distance;vertex2";
}

std::string get_error_message_edge(unsigned int& rownum, const std::string& what, bool ext)
{
	std::string lineno;

	if (ext)
	{
		lineno = "in line with number more then" + std::to_string(rownum);
	}
	else
	{
		lineno = "in line " + std::to_string(rownum);
	}

	return "Argument '" + what + "' " + lineno + " must be positive integer less or equal then " + std::to_string(std::numeric_limits<unsigned int>::max());
}

std::string get_error_message_vertex(const std::string& what)
{
	return "Argument '" + what + "' must be positive integer less or equal then " + std::to_string(std::numeric_limits<unsigned int>::max());
}

unsigned int graph_serialization::vertex_to_uint(std::string& value, const std::string& what)
{
	try
	{
		return convert_to_uint(value);
	}
	catch (const std::invalid_argument&)
	{
		throw nexception(get_error_message_vertex(what));
	}
	catch (std::out_of_range&)
	{
		throw nexception(get_error_message_vertex(what));
	}
}