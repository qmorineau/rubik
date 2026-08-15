#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <array>
#include <unordered_map>
#include <string>

#include "cube_types.hpp"

class Cube
{
	public:
		Cube();
		~Cube();

		void move(std::string);
		void reset();
		// getters
		const std::array<EdgeId, 12>	edgePerm() const {return _edge_perm;};
		const std::array<CornerId, 8>	cornerPerm() const {return _corner_perm;};
		const std::array<uint8_t, 12>	edgeOrient() const {return _edge_orient;};
		const std::array<uint8_t, 8>	cornerOrient() const {return _corner_orient;};
	private:
		std::array<EdgeId, 12>		_edge_perm;
		std::array<CornerId, 8>		_corner_perm;
		std::array<uint8_t, 12>		_edge_orient;
		std::array<uint8_t, 8>		_corner_orient;

		std::unordered_map<std::string, void (Cube::*)()>	_moves;

		void applyEdgeCycle(const EdgePos cycle[4], const uint8_t orientDelta[4]);
		void applyCornerCycle(const CornerPos cycle[4], const uint8_t orientDelta[4]);
		void U();
		void UPrime();
		void U2();
		void L();
		void LPrime();
		void L2();
		void R();
		void RPrime();
		void R2();
		void B();
		void BPrime();
		void B2();
		void D();
		void DPrime();
		void D2();
		void F();
		void FPrime();
		void F2();
};

#endif