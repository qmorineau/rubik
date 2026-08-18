#include "Kociemba.hpp"

Kociemba::Kociemba()
{
	_edgesOrientTable.fill(-1);
	_cornersOrientTable.fill(-1);
	_sliceTable.fill(-1);

	initMoves();

	createEdgesOrientTable();
	createCornersOrientTable();
	createSliceTable();
}

std::vector<Move> Kociemba::solve(Cube& c)
{
	std::vector<Move> solution;

	Cube toSolve = c;
	phase1Search(toSolve, solution, 0, Move::COUNT);
	return (solution);
};

void Kociemba::initMoves()
{
	_allMoves.reserve(static_cast<size_t>(Move::COUNT));
	_movesP2.reserve(static_cast<size_t>(Move::COUNT) - 8);
	_inverses.reserve(static_cast<size_t>(Move::COUNT));

	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		_allMoves.push_back(static_cast<Move>(i));
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

	std::queue<int>	toExplore;

	_edgesOrientTable[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _edgesOrientTable[coord];

		Cube current;
		current.setFromEdgesOrient(coord);

		for (size_t m = 0; m < static_cast<size_t>(Move::COUNT); m++)
		{
			Cube tmp = current;
			tmp.move(_allMoves[m]);
			int newCoord = tmp.edgeOrientCoord();
			if (_edgesOrientTable[newCoord] == -1)
			{
				_edgesOrientTable[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
		}
	}
}

void Kociemba::createCornersOrientTable()
{
	_cornersOrientTable.fill(-1);

	std::queue<int>	toExplore;

	_cornersOrientTable[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _cornersOrientTable[coord];

		Cube current;
		current.setFromCornersOrient(coord);

		for (size_t m = 0; m < static_cast<size_t>(Move::COUNT); m++)
		{
			Cube tmp = current;
			tmp.move(_allMoves[m]);
			int newCoord = tmp.cornerOrientCoord();
			if (_cornersOrientTable[newCoord] == -1)
			{
				_cornersOrientTable[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
		}
	}
}

void Kociemba::createSliceTable()
{
	_sliceTable.fill(-1);

	std::queue<int>	toExplore;

	_sliceTable[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _sliceTable[coord];

		Cube current;
		current.setFromSlice(coord);

		for (size_t m = 0; m < static_cast<size_t>(Move::COUNT); m++)
		{
			Cube tmp = current;
			tmp.move(_allMoves[m]);
			int newCoord = tmp.sliceCoord();
			if (_sliceTable[newCoord] == -1)
			{
				_sliceTable[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
		}
	}
}

bool Kociemba::phase1Search(Cube& cube, std::vector<Move>& solution, int depth, Move lastMove)
{
	int heuristic = std::max(_edgesOrientTable[cube.edgeOrientCoord()], _cornersOrientTable[cube.cornerOrientCoord()]);
	heuristic = std::max(heuristic, _sliceTable[cube.sliceCoord()]);

	if (depth + heuristic > 15)
		return (false);
	if (heuristic == 0)
		return (true);

	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		if (toIndex(lastMove) / 6 == i / 6)
			continue;
		cube.move(_allMoves[i]);
		solution.push_back(_allMoves[i]);
		if (phase1Search(cube, solution, depth + 1, _allMoves[i]))
			return (true);
		solution.pop_back();
		cube.move(_inverses[i]);
	}
	return (false);
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
