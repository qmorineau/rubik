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
		std::array<int, 2048>		_edgesOrientTable;		// 2048 = 2^11 => 12th edges depend of the 11 others
		std::array<int, 2187>		_cornersOrientTable;	// 2187 = 3^7  => 8th corners depend of the 7 others
		std::array<int, 495>		_sliceTable;			// 495 = (12! / (4! * 8!)) => (12! / 8!) / 4! => (12 * 11 * 10 * 9) / (4 * 3 * 2 * 1)
		std::array<int, 40320>		_edgesPermTable;		// 8 edges / corners to permut => 40320
		std::array<int, 40320>		_cornersPermTable;		// 40320 = 8! = 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
		std::array<int, 24> 		_slicePermTable;		// 24 = 4! = 4 * 3 * 2 * 1


		bool phase1Search(Cube& cube, std::vector<Move>& solution, int depth, Move lastMove);
		bool phase2Search(Cube& cube, std::vector<Move>& solution, int depth, Move lastMove);
		void initMoves();
		void createEdgesOrientTable();
		void createCornersOrientTable();
		void createSliceTable();
		void createEdgesPermTable();
		void createCornersPermTable();
		void createSlicePermTable();
};

#endif