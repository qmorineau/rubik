#include "Kociemba.hpp"

Kociemba::Kociemba()
{
	_moves.reserve(static_cast<size_t>(Move::COUNT));
	_inverses.reserve(static_cast<size_t>(Move::COUNT));

	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		_moves.push_back(static_cast<Move>(i));
		switch (i % 3)
		{
			case 0:
				_inverses.push_back(static_cast<Move>(i + 1));
				break;
			case 1:
				_inverses.push_back(static_cast<Move>(i - 1));
				break;
			case 2:
				_inverses.push_back(static_cast<Move>(i));
				break;
		}	
	}
}

std::vector<Move> Kociemba::solve(Cube& c)
{
	std::vector<Move> l;
	return l;
};

void Kociemba::phase1Search(Cube& cube, std::vector<Move>& solution)
{
	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		solution.push_back(_moves[i]);
		cube.move(_moves[i]);
		phase1Search(cube, solution);
		cube.move(_inverses[i]);
		solution.pop_back();
	}
};

void Kociemba::phase2Search()
{

};

/* 
bool phase1Search(Cube& cube, int depth, int maxDepth, std::vector<Move>& solution) {
    int h = std::max(edgeOrientTable[cube.edgeOrientCoord()],
                      cornerOrientTable[cube.cornerOrientCoord()]);
    // (+ table de position de tranche, prise en compte pareil)
    if (depth + h > maxDepth) return false; // coupe la branche
    if (h == 0) return true; // phase 1 terminée

    for (Move m : ALL_18_MOVES) {
        cube.move(m);
        solution.push_back(m);
        if (phase1Search(cube, depth + 1, maxDepth, solution)) return true;
        solution.pop_back();
        cube.move(inverse(m)); // annule pour essayer le mouvement suivant
    }
    return false;
}
 */