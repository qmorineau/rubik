#include "Solver.hpp"

Solver::Solver() = default;

Solver::~Solver() = default;

std::vector<Move> Solver::solve()
{
	_kociemba.solve(_cube);
	return
}

void Solver::move(Move m)
{
	_cube.move(m);
};