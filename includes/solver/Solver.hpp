#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>

#include "Cube.hpp"
#include "Kociemba.hpp"

class Solver
{
	public:
		Solver();
		~Solver();

		void move(Move m);
		// getter
		const Cube& cube() const {return _cube;};
		Cube& cube() {return _cube;};
	private:
		Cube		_cube;
		Kociemba	_kociamba;
};

#endif