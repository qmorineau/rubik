#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

#include "cube_types.hpp"

class Parser
{
	public:
		Parser();
		~Parser();

		std::vector<Move> parse(int argc, char *argv[]);
};

#endif