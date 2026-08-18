#ifndef KOCIEMBA_HPP
#define	KOCIEMBA_HPP

#include <vector>
#include <string>
#include <array>
#include <queue>
#include <algorithm>

#include "Cube.hpp"

class Kociemba
{
	public:
		Kociemba();
		~Kociemba() = default;

		std::vector<Move> solve(Cube& c);
	private:
		std::vector<Move>	_inverses;
		std::vector<Move>	_allMoves;
		std::vector<Move>	_movesP2;
		// Transition Table
		std::array<int, 2048>	_edgesOrientPruning;	// 2048 = 2^11 => 12th edges depend of the 11 others
		std::array<int, 2187>	_cornersOrientPruning;	// 2187 = 3^7  => 8th corners depend of the 7 others
		std::array<int, 495>	_slicePruning;			// 495 = (12! / (4! * 8!)) => (12! / 8!) / 4! => (12 * 11 * 10 * 9) / (4 * 3 * 2 * 1)
		std::array<int, 40320>	_edgesPermPruning;		// 8 edges / corners to permut => 40320
		std::array<int, 40320>	_cornersPermPruning;	// 40320 = 8! = 8 * 7 * 18 * 5 * 4 * 3 * 2 * 1
		std::array<int, 24> 	_slicePermPruning;		// 24 = 4! = 4 * 3 * 2 * 1
		// Pruning Table
		std::array<std::array<int, 18>, 2048>	_edgesOrientTable;
		std::array<std::array<int, 18>, 2187>	_cornersOrientTable;
		std::array<std::array<int, 18>, 495>	_sliceTable;
		std::array<std::array<int, 10>, 40320>	_edgesPermTable;
		std::array<std::array<int, 10>, 40320>	_cornersPermTable;
		std::array<std::array<int, 10>, 24> 	_slicePermTable;

		bool phase1Search(int edgeCoord, int cornerCoord, int sliceCoord, std::vector<Move>& solution, int depth, Move lastMove);
		bool phase2Search(int edgeCoord, int cornerCoord, int sliceCoord, std::vector<Move>& solution, int depth, Move lastMove);
		void initTable();
		void initMoves();
		void createEdgesOrientTable();
		void createCornersOrientTable();
		void createSliceTable();
		void createEdgesPermTable();
		void createCornersPermTable();
		void createSlicePermTable();
};

#endif