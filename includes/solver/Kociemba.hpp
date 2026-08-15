#ifndef KOCIEMBA_HPP
#define	KOCIEMBA_HPP

#include <vector>
#include <string>

#include "Cube.hpp"

class Kociemba
{
	public:
		Kociemba();
		~Kociemba() = default;

		std::vector<Move> solve(Cube& c);
	private:
		void phase1Search(Cube& cube, std::vector<Move>& solution);
		void phase2Search();
		std::vector<Move>	_inverses;
		std::vector<Move>	_moves;
};

#endif