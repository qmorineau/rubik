#include "Kociemba.hpp"

Kociemba::Kociemba()
{
	_edgesOrientTable.fill(-1);
	_cornersOrientTable.fill(-1);
	_sliceTable.fill(-1);

	initMoves();

	createEdgesOrientTable();
	createCornersOrientTable();
}

std::vector<Move> Kociemba::solve(Cube& c)
{
	(void) c;
	std::vector<Move> l;
	return l;
};

void Kociemba::initMoves()
{
	_movesP1.reserve(static_cast<size_t>(Move::COUNT));
	_movesP2.reserve(static_cast<size_t>(Move::COUNT) - 8);
	_inverses.reserve(static_cast<size_t>(Move::COUNT));

	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		_movesP1.push_back(static_cast<Move>(i));
		if (i < 6 || i % 3 == 2)
			_movesP2.push_back(static_cast<Move>(i));
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

void Kociemba::createEdgesOrientTable()
{
	_edgesOrientTable.fill(-1);

	std::queue<int> queue;

	_edgesOrientTable[0] = 0;
	queue.push(0);

	while (!queue.empty())
	{
	    int coord = queue.front();
	    queue.pop();

	    for (size_t m = 0; m < toIndex(Move::COUNT); m++)
	    {
	        int next = edgeOrientMove[coord][m];

	        if (_edgesOrientTable[next] == -1)
	        {
	            _edgesOrientTable[next] = _edgesOrientTable[coord] + 1;
	            queue.push(next);
	        }
	    }
	}
}

void Kociemba::createCornersOrientTable()
{

}

void Kociemba::phase1Search(Cube& cube, std::vector<Move>& solution)
{
	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		solution.push_back(_movesP1[i]);
		cube.move(_movesP1[i]);
		phase1Search(cube, solution);
		cube.move(_inverses[i]);
		solution.pop_back();
	}
};

void Kociemba::phase2Search(Cube& cube, std::vector<Move>& solution)
{
	for (auto m : _movesP2)
	{
		solution.push_back(m);
		cube.move(m);
		phase2Search(cube, solution);
		cube.move(_inverses[toIndex(m)]);
		solution.pop_back();
	}	
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