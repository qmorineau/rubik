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
	createEdgesPermTable();
	createCornersPermTable();
	createSlicePermTable();

// 	for (int coord = 0; coord < 40320; ++coord)
// {
//     Cube cube;
//     cube.setFromCornersPerm(coord);

//     if (cube.cornerPermCoord() != coord)
//     {
//         std::cout << "corner ERREUR : " << coord
//                   << " -> " << cube.cornerPermCoord()
//                   << '\n';
//         break;
//     }
// }
// 	for (int coord = 0; coord < 40320; ++coord)
// {
//     Cube cube;
//     cube.setFromEdgesPerm(coord);

//     if (cube.edgePermCoord() != coord)
//     {
//         std::cout << "edges ERREUR : " << coord
//                   << " -> " << cube.edgePermCoord()
//                   << '\n';
//         break;
//     }
// }
}

// #include <map>
// void Kociemba::test()
// {
// 	std::map<int, int> map;

// 	_cornersOrientTable.fill(-1);

// 	std::queue<int>	toExplore;

// 	map.try_emplace(0, 0);
// 	toExplore.push(0);

// 	while (!toExplore.empty())
// 	{
// 		int coord = toExplore.front();
// 		toExplore.pop();
// 		int currentDist = map.at(coord);

// 		Cube current;
// 		current.setFromEdgesPerm(coord);

// 		for (auto m : _movesP2)
// 		{
// 			Cube tmp = current;
// 			tmp.move(m);
// 			int newCoord = tmp.edgePermCoord();
// 			try
// 			{
// 				map.at(newCoord);
// 			}
// 			catch(const std::exception& e)
// 			{
// 				map.try_emplace(newCoord, currentDist + 1);
// 				toExplore.push(newCoord);
// 			}
// 		}
// 	}
// 	std::cout << "Map = " << map.size() << std::endl;
// }

std::vector<Move> Kociemba::solve(Cube& c)
{
	std::vector<Move> solution;

	Cube toSolve = c;
	phase1Search(toSolve, solution, 0, Move::COUNT);
	phase2Search(toSolve, solution, 0, Move::COUNT);
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

void Kociemba::createEdgesPermTable()
{
	_edgesPermTable.fill(-1);

	std::queue<int>	toExplore;

	_edgesPermTable[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _edgesPermTable[coord];

		Cube current;
		current.setFromEdgesPerm(coord);

		for (auto m : _movesP2)
		{
			Cube tmp = current;
			tmp.move(m);
			int newCoord = tmp.edgePermCoord();
			if (_edgesPermTable[newCoord] == -1)
			{
				_edgesPermTable[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
		}
	}
}

void Kociemba::createCornersPermTable()
{
	_cornersPermTable.fill(-1);

	std::queue<int>	toExplore;

	_cornersPermTable[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _cornersPermTable[coord];

		Cube current;
		current.setFromCornersPerm(coord);

		for (auto m : _movesP2)
		{
			Cube tmp = current;
			tmp.move(m);
			int newCoord = tmp.cornerPermCoord();
			if (_cornersPermTable[newCoord] == -1)
			{
				_cornersPermTable[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
		}
	}
}

void Kociemba::createSlicePermTable()
{
	_slicePermTable.fill(-1);

	std::queue<int>	toExplore;

	_slicePermTable[0] = 0;
	toExplore.push(0);

	while (!toExplore.empty())
	{
		int coord = toExplore.front();
		toExplore.pop();
		int currentDist = _slicePermTable[coord];

		Cube current;
		current.setFromSlicePerm(coord);

		for (auto m : _movesP2)
		{
			Cube tmp = current;
			tmp.move(m);
			int newCoord = tmp.slicePermCoord();
			if (_slicePermTable[newCoord] == -1)
			{
				_slicePermTable[newCoord] = currentDist + 1;
				toExplore.push(newCoord);
			}
		}
	}
}

bool Kociemba::phase1Search(Cube& cube, std::vector<Move>& solution, int depth, Move lastMove)
{
	int heuristic = std::max(_edgesOrientTable[cube.edgeOrientCoord()], _cornersOrientTable[cube.cornerOrientCoord()]);
	heuristic = std::max(heuristic, _sliceTable[cube.sliceCoord()]);

	if (depth + heuristic > 30)
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

bool Kociemba::phase2Search(Cube& cube, std::vector<Move>& solution, int depth, Move lastMove)
{
	int heuristic = std::max(_edgesPermTable[cube.edgePermCoord()], _cornersPermTable[cube.cornerPermCoord()]);
	heuristic = std::max(heuristic, _slicePermTable[cube.slicePermCoord()]);

	if (depth + heuristic > 18)
		return (false);
	if (heuristic == 0)
		return (true);

	for (uint8_t i = 0; i < _movesP2.size(); i++)
	{
		Move m = _movesP2[i];
		if (toIndex(lastMove) / 3 == toIndex(m) / 3)
			continue;
		cube.move(m);
		solution.push_back(m);
		if (phase2Search(cube, solution, depth + 1, m))
			return (true);
		solution.pop_back();
		cube.move(_inverses[toIndex(m)]);
	}
	return (false);
};
