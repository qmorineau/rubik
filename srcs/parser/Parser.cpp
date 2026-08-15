#include "Parser.hpp"

#include "cube_types.hpp"

Parser::Parser() = default;
Parser::~Parser() = default;


const std::unordered_map<std::string, Move> moves = {
	{"U", Move::U},
	{"U'", Move::UPrime},
	{"U2", Move::U2},
	{"D", Move::D},
	{"D'", Move::DPrime},
	{"D2", Move::D2},
	{"L", Move::L},
	{"L'", Move::LPrime},
	{"L2", Move::L2},
	{"R", Move::R},
	{"R'", Move::RPrime},
	{"R2", Move::R2},
	{"F", Move::F},
	{"F'", Move::FPrime},
	{"F2", Move::F2},
	{"B", Move::B},
	{"B'", Move::BPrime},
	{"B2", Move::B2},
};

std::vector<Move> Parser::parse(int argc, char *argv[])
{
	std::vector<Move> list;
	if (argc > 2)
		throw std::runtime_error("Rubik: too many arguments");
	if (argc == 1)
		return list;

	std::istringstream	iss(argv[1]);
	std::string token;
	while (iss >> token)
	{
		auto it = moves.find(token);
		if (it == moves.end())
			throw std::runtime_error("Rubik: Unknown move : " + token);
		list.push_back(it->second);
	}
	return (list);
}