#include "Solver.hpp"

Solver::Solver() = default;

Solver::~Solver() = default;

void Solver::move(Move m)
{
	const std::vector<std::string> move = {
		"U", "U'", "U2",
		"D", "D'", "D2",
		"L", "L'", "L2",
		"R", "R'", "R2",
		"F", "F'", "F2",
		"B", "B'", "B2",
	};
	_cube.move(m);
	std::cout << " " << move[static_cast<int>(m)];
	// _cube.print();
};