#include "Kociemba.hpp"

Kociemba::Kociemba()
{
	initMoves();
	initTable();

	createEdgesOrientTable();
	createCornersOrientTable();
	createSliceTable();
	createEdgesPermTable();
	createCornersPermTable();
	createSlicePermTable();
}

std::vector<Move> Kociemba::solve(Cube& c)
{
	std::vector<Move> solution;

	Cube toSolve = c;
	phase1Search(toSolve.edgeOrientCoord(), toSolve.cornerOrientCoord(), toSolve.sliceCoord(), solution, 0, Move::COUNT);
	for (auto m : solution)
		toSolve.move(m);
	phase2Search(toSolve.edgePermCoord(), toSolve.cornerPermCoord(), toSolve.slicePermCoord(), solution, 0, Move::COUNT);
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

void Kociemba::initTable()
{
	_edgesOrientPruning.fill(-1);
	_cornersOrientPruning.fill(-1);
	_slicePruning.fill(-1);
	_edgesPermPruning.fill(-1);
	_cornersPermPruning.fill(-1);
	_slicePermPruning.fill(-1);
}

void Kociemba::createEdgesOrientTable()
{
	std::queue<int>	toExplore;

	_edgesOrientPruning[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _edgesOrientPruning[coord];

		Cube current;
		current.setFromEdgesOrient(coord);

		for (size_t m = 0; m < static_cast<size_t>(Move::COUNT); m++)
		{
			Cube tmp = current;
			tmp.move(_allMoves[m]);
			int newCoord = tmp.edgeOrientCoord();
			if (_edgesOrientPruning[newCoord] == -1)
			{
				_edgesOrientPruning[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
			_edgesOrientTable[coord][m] = newCoord;
		}
	}
}

void Kociemba::createCornersOrientTable()
{
	std::queue<int>	toExplore;

	_cornersOrientPruning[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _cornersOrientPruning[coord];

		Cube current;
		current.setFromCornersOrient(coord);

		for (size_t m = 0; m < static_cast<size_t>(Move::COUNT); m++)
		{
			Cube tmp = current;
			tmp.move(_allMoves[m]);
			int newCoord = tmp.cornerOrientCoord();
			if (_cornersOrientPruning[newCoord] == -1)
			{
				_cornersOrientPruning[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
			_cornersOrientTable[coord][m] = newCoord;
		}
	}
}

void Kociemba::createSliceTable()
{
	std::queue<int>	toExplore;

	_slicePruning[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _slicePruning[coord];

		Cube current;
		current.setFromSlice(coord);

		for (size_t m = 0; m < static_cast<size_t>(Move::COUNT); m++)
		{
			Cube tmp = current;
			tmp.move(_allMoves[m]);
			int newCoord = tmp.sliceCoord();
			if (_slicePruning[newCoord] == -1)
			{
				_slicePruning[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
			_sliceTable[coord][m] = newCoord;
		}
	}
}

void Kociemba::createEdgesPermTable()
{
	std::queue<int>	toExplore;

	_edgesPermPruning[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _edgesPermPruning[coord];

		Cube current;
		current.setFromEdgesPerm(coord);

		for (size_t i = 0; i < _movesP2.size(); i++)
		{
			Move m = _movesP2[i];
			Cube tmp = current;
			tmp.move(m);
			int newCoord = tmp.edgePermCoord();
			if (_edgesPermPruning[newCoord] == -1)
			{
				_edgesPermPruning[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
			_edgesPermTable[coord][i] = newCoord;
		}
	}
}

void Kociemba::createCornersPermTable()
{
	std::queue<int>	toExplore;

	_cornersPermPruning[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _cornersPermPruning[coord];

		Cube current;
		current.setFromCornersPerm(coord);

		for (size_t i = 0; i < _movesP2.size(); i++)
		{
			Move m = _movesP2[i];
			Cube tmp = current;
			tmp.move(m);
			int newCoord = tmp.cornerPermCoord();
			if (_cornersPermPruning[newCoord] == -1)
			{
				_cornersPermPruning[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
			_cornersPermTable[coord][i] = newCoord;
		}
	}
}

void Kociemba::createSlicePermTable()
{
	std::queue<int>	toExplore;

	_slicePermPruning[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _slicePermPruning[coord];

		Cube current;
		current.setFromSlicePerm(coord);

		for (size_t i = 0; i < _movesP2.size(); i++)
		{
			Move m = _movesP2[i];
			Cube tmp = current;
			tmp.move(m);
			int newCoord = tmp.slicePermCoord();
			if (_slicePermPruning[newCoord] == -1)
			{
				_slicePermPruning[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
			_slicePermTable[coord][i] = newCoord;
		}
	}
}

bool Kociemba::phase1Search(int edgeCoord, int cornerCoord, int sliceCoord, std::vector<Move>& solution, int depth, Move lastMove)
{
	int heuristic = std::max(_edgesOrientPruning[edgeCoord], _cornersOrientPruning[cornerCoord]);
	heuristic = std::max(heuristic, _slicePruning[sliceCoord]);

	if (depth + heuristic > 30)
		return (false);
	if (heuristic == 0)
		return (true);

	for (uint8_t i = 0; i < static_cast<uint8_t>(Move::COUNT); i++)
	{
		if (toIndex(lastMove) / 6 == i / 6)
			continue;
		int newEdgeCoord = _edgesOrientTable[edgeCoord][i];
		int newCornerCoord = _cornersOrientTable[cornerCoord][i];
		int newSliceCoord = _sliceTable[sliceCoord][i];
		solution.push_back(_allMoves[i]);
		if (phase1Search(newEdgeCoord, newCornerCoord, newSliceCoord, solution, depth + 1, _allMoves[i]))
			return (true);
		solution.pop_back();
	}
	return (false);
};

bool Kociemba::phase2Search(int edgeCoord, int cornerCoord, int sliceCoord, std::vector<Move>& solution, int depth, Move lastMove)
{
	int heuristic = std::max(_edgesPermPruning[edgeCoord], _cornersPermPruning[cornerCoord]);
	heuristic = std::max(heuristic, _slicePermPruning[sliceCoord]);

	if (depth + heuristic > 18)
		return (false);
	if (heuristic == 0)
		return (true);

	for (uint8_t i = 0; i < _movesP2.size(); i++)
	{
		Move m = _movesP2[i];
		int moveIndex = toIndex(m);
		if (toIndex(lastMove) / 3 == moveIndex / 3)
			continue;
		int newEdgeCoord = _edgesPermTable[edgeCoord][i];
		int newCornerCoord = _cornersPermTable[cornerCoord][i];
		int newSliceCoord = _slicePermTable[sliceCoord][i];
		solution.push_back(m);
		if (phase2Search(newEdgeCoord, newCornerCoord, newSliceCoord, solution, depth + 1, m))
			return (true);
		solution.pop_back();
	}
	return (false);
};
