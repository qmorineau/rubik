#include "Cube.hpp"

Cube::Cube()
{
	_moves.emplace(Move::U, &Cube::U);
	_moves.emplace(Move::UPrime, &Cube::UPrime);
	_moves.emplace(Move::U2, &Cube::U2);
	_moves.emplace(Move::D, &Cube::D);
	_moves.emplace(Move::DPrime, &Cube::DPrime);
	_moves.emplace(Move::D2, &Cube::D2);
	_moves.emplace(Move::F, &Cube::F);
	_moves.emplace(Move::FPrime, &Cube::FPrime);
	_moves.emplace(Move::F2, &Cube::F2);
	_moves.emplace(Move::B, &Cube::B);
	_moves.emplace(Move::BPrime, &Cube::BPrime);
	_moves.emplace(Move::B2, &Cube::B2);
	_moves.emplace(Move::L, &Cube::L);
	_moves.emplace(Move::LPrime, &Cube::LPrime);
	_moves.emplace(Move::L2, &Cube::L2);
	_moves.emplace(Move::R, &Cube::R);
	_moves.emplace(Move::RPrime, &Cube::RPrime);
	_moves.emplace(Move::R2, &Cube::R2);

	reset();
}

Cube::~Cube() = default;

void Cube::move(Move move)
{
	auto it = _moves.find(move);
    if (it == _moves.end())
        throw std::runtime_error("Rubik: Cube::move(): Unmanage move");
    (this->*(it->second))();
}

int Cube::edgeOrientCoord() const
{
	int coord = 0;

    for (int i = 0; i < 11; ++i)
        coord = coord * 2 + _edge_orient[i];

    return (coord);
}

int Cube::cornerOrientCoord() const
{
	int coord = 0;

    for (int i = 0; i < 7; ++i)
        coord = coord * 2 + _corner_orient[i];

    return (coord);
}

int Cube::sliceCoord() const
{
	return (0);
}

void Cube::print() const
{
	// Edges
	const char edges[][3] = {
		"UF", "UR", "UB", "UL",
		"DF", "DR", "DB", "DL",
		"FL", "FR", "BL", "BR"
	};
	std::cout << "===== Edges =====" << std::endl;
	for (auto i = 0; i < 12; i++)
		std::cout << edges[i] << " == " << edges[toIndex(_edge_perm[i])]
			<< ", o = " << static_cast<int>(_edge_orient[toIndex(static_cast<EdgePos>(i))]) << std::endl;

	// Corners
	const char corners[][4] = {
		"UFL", "UFR", "UBR", "UBL",
		"DFL", "DFR", "DBR", "DBL"
	};
	std::cout << "===== Corners =====" << std::endl;
	for (auto i = 0; i < 8; i++)
		std::cout << corners[i] << " == " << corners[toIndex(_corner_perm[i])]
			<< ", o = " << static_cast<int>(_corner_orient[toIndex(static_cast<CornerPos>(i))]) << std::endl;
	std::cout << std::endl;
}

void Cube::reset()
{
	for (uint8_t i = 0; i < 12; i++)
	{
		_edge_perm[i] = static_cast<EdgeId>(i);
		_edge_orient[i] = 0;
	}
	for (uint8_t i = 0; i < 8; i++)
	{
		_corner_perm[i] = static_cast<CornerId>(i);
		_corner_orient[i] = 0;
	}
}

void Cube::applyEdgeCycle(const EdgePos cycle[4], const uint8_t orientDelta[4])
{
	EdgeId	tmp = _edge_perm[toIndex(cycle[3])];
	uint8_t	tmpOrient = _edge_orient[toIndex(cycle[3])];

	for (int i = 3; i > 0; i--)
	{
		_edge_perm[toIndex(cycle[i])] = _edge_perm[toIndex(cycle[i - 1])];
		_edge_orient[toIndex(cycle[i])] = (_edge_orient[toIndex(cycle[i - 1])] + orientDelta[i]) % 2;
	}

	_edge_perm[toIndex(cycle[0])] = tmp;
	_edge_orient[toIndex(cycle[0])] = (tmpOrient + orientDelta[0]) % 2;
}

void Cube::applyCornerCycle(const CornerPos cycle[4], const uint8_t orientDelta[4])
{
	CornerId	tmp = _corner_perm[toIndex(cycle[3])];
	uint8_t		tmpOrient = _corner_orient[toIndex(cycle[3])];

	for (int i = 3; i > 0; i--)
	{
		_corner_perm[toIndex(cycle[i])] = _corner_perm[toIndex(cycle[i - 1])];
		_corner_orient[toIndex(cycle[i])] = (_corner_orient[toIndex(cycle[i - 1])] + orientDelta[i]) % 3;
	}

	_corner_perm[toIndex(cycle[0])] = tmp;
	_corner_orient[toIndex(cycle[0])] = (tmpOrient + orientDelta[0]) % 3;
}

void Cube::U()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::UL, EdgePos::UB, EdgePos::UR, EdgePos::UF};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UBL, CornerPos::UBR, CornerPos::UFR, CornerPos::UFL};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {0, 0, 0, 0};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::UPrime()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::UF, EdgePos::UR, EdgePos::UB, EdgePos::UL};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UFL, CornerPos::UFR, CornerPos::UBR, CornerPos::UBL};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {0, 0, 0, 0};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::U2()
{
	for (int i = 0; i < 2; i++)
		U();
}

void Cube::D()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::DF, EdgePos::DR, EdgePos::DB, EdgePos::DL};
	constexpr CornerPos corner_cycle[4] = {CornerPos::DFL, CornerPos::DFR, CornerPos::DBR, CornerPos::DBL};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {0, 0, 0, 0};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::DPrime()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::DL, EdgePos::DB, EdgePos::DR, EdgePos::DF};
	constexpr CornerPos corner_cycle[4] = {CornerPos::DBL, CornerPos::DBR, CornerPos::DFR, CornerPos::DFL};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {0, 0, 0, 0};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::D2()
{
	for (int i = 0; i < 2; i++)
		D();
}

void Cube::L()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::UL, EdgePos::FL, EdgePos::DL, EdgePos::BL};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UFL, CornerPos::DFL, CornerPos::DBL, CornerPos::UBL};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {1, 2, 1, 2};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::LPrime()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::BL, EdgePos::DL, EdgePos::FL, EdgePos::UL};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UBL, CornerPos::DBL, CornerPos::DFL, CornerPos::UFL};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {2, 1, 2, 1};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::L2()
{
	for (int i = 0; i < 2; i++)
		L();
}

void Cube::R()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::BR, EdgePos::DR, EdgePos::FR, EdgePos::UR};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UBR, CornerPos::DBR, CornerPos::DFR, CornerPos::UFR};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {1, 2, 1, 2};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::RPrime()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::UR, EdgePos::FR, EdgePos::DR, EdgePos::BR};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UFR, CornerPos::DFR, CornerPos::DBR, CornerPos::UBR};
	constexpr uint8_t	edge_orient_cycle[4] = {0, 0, 0, 0};
	constexpr uint8_t	corner_orient_cycle[4] = {2, 1, 2, 1};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::R2()
{
	for (int i = 0; i < 2; i++)
		R();
}

void Cube::F()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::FR, EdgePos::DF, EdgePos::FL, EdgePos::UF};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UFR, CornerPos::DFR, CornerPos::DFL, CornerPos::UFL};
	constexpr uint8_t	edge_orient_cycle[4] = {1, 1, 1, 1};
	constexpr uint8_t	corner_orient_cycle[4] = {1, 2, 1, 2};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::FPrime()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::UF, EdgePos::FL, EdgePos::DF, EdgePos::FR};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UFL, CornerPos::DFL, CornerPos::DFR, CornerPos::UFR};
	constexpr uint8_t	edge_orient_cycle[4] = {1, 1, 1, 1};
	constexpr uint8_t	corner_orient_cycle[4] = {2, 1, 2, 1};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::F2()
{
	for (int i = 0; i < 2; i++)
		F();
}

void Cube::B()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::UB, EdgePos::BL, EdgePos::DB, EdgePos::BR};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UBL, CornerPos::DBL, CornerPos::DBR, CornerPos::UBR};
	constexpr uint8_t	edge_orient_cycle[4] = {1, 1, 1, 1};
	constexpr uint8_t	corner_orient_cycle[4] = {1, 2, 1, 2};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::BPrime()
{
	constexpr EdgePos	edge_cycle[4] = {EdgePos::BR, EdgePos::DB, EdgePos::BL, EdgePos::UB};
	constexpr CornerPos corner_cycle[4] = {CornerPos::UBR, CornerPos::DBR, CornerPos::DBL, CornerPos::UBL};
	constexpr uint8_t	edge_orient_cycle[4] = {1, 1, 1, 1};
	constexpr uint8_t	corner_orient_cycle[4] = {2, 1, 2, 1};

	applyEdgeCycle(edge_cycle, edge_orient_cycle);
	applyCornerCycle(corner_cycle, corner_orient_cycle);
}

void Cube::B2()
{
	for (int i = 0; i < 2; i++)
		B();
}