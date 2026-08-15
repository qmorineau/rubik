#ifndef KOCIEMBA_HPP
#define	KOCIEMBA_HPP

#include <vector>
#include <string>

#include "Cube.hpp"

class Kociemba
{
	public:
		Kociemba() = default;
		~Kociemba() = default;

		std::vector<std::string> solve(Cube c);
	private:

		void _phase1();
		void _phase2();
};

#endif