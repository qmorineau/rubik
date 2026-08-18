#include "Solver.hpp"

Solver::Solver() = default;

Solver::~Solver() = default;

std::vector<Move> Solver::solve()
{
	return _kociamba.solve(_cube);
}

void Solver::move(Move m)
{
	_cube.move(m);
};