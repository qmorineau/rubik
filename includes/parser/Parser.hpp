#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

class Parser
{
	public:
		Parser();
		~Parser();

		std::vector<std::string> parse(int argc, char *argv[]);
};

#endif