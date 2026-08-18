#include "Solver.hpp"

Solver::Solver() = default;

Solver::~Solver() = default;

std::vector<Move> Solver::solve()
{
	clock_t begin = clock();
	auto solution = _kociemba.solve(_cube);
	clock_t duration = clock() - begin;
	std::cout << "time to solve = " << static_cast<float>(duration) / CLOCKS_PER_SEC << std::endl;
	return solution;
}

void Solver::move(Move m)
{
	_cube.move(m);
};