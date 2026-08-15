#include "Parser.hpp"

Parser::Parser() = default;
Parser::~Parser() = default;


const std::unordered_set<std::string> moves = {
	"U", "U'", "U2",
	"D", "D'", "D2",
	"L", "L'", "L2",
	"R", "R'", "R2",
	"F", "F'", "F2",
	"B", "B'", "B2"
};

std::vector<std::string> Parser::parse(int argc, char *argv[])
{
	std::vector<std::string> list;
	if (argc > 2)
		throw std::runtime_error("Rubik: too many arguments");
	if (argc == 1)
		return list;

	std::istringstream	iss(argv[1]);
	std::string token;
	while (iss >> token)
	{
		if (moves.find(token) == moves.end())
			throw std::runtime_error("Rubik: Unknown move : " + token);
		list.push_back(token);
	}
	return (list);
}