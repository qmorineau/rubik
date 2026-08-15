#include "Solver.hpp"

Solver::Solver() = default;

Solver::~Solver() = default;

void Solver::move(Move m)
{
	_cube.move(m);
	_cube.print();
};