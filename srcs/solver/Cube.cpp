#include "Cube.hpp"

#include "commands.hpp"

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

// Edge Coord

int Cube::edgeOrientCoord() const
{
	int coord = 0;
	
	for (int i = 0; i < 11; i++)
		coord = (coord << 1) | _edge_orient[i];
	return (coord);
}

void Cube::setFromEdgesOrient(int coord)
{
	int sum = 0;
	for (int i = 0; i < 11; i++)
	{
		int bit = (coord >> (10 - i)) & 1;
		_edge_orient[i] = bit;
		sum += bit;
	}
	_edge_orient[11] = sum % 2; // 12th edges depend of the 11 others
}

int Cube::edgePermCoord() const
{
	int coord = 0;

	for (int i = 0; i < 7; i++)
	{
		int count = 0;

		for (int j = i + 1; j < 8; ++j)
		{
			if (static_cast<int>(_edge_perm[j]) < static_cast<int>(_edge_perm[i]))
				++count;
		}
		coord = coord * (8 - i) + count;
	}
	return (coord);
}

void Cube::setFromEdgesPerm(int coord)
{
		EdgeId available[8] = {
        EdgeId::UF, EdgeId::UR, EdgeId::UB, EdgeId::UL,
        EdgeId::DF, EdgeId::DR, EdgeId::DB, EdgeId::DL
    };

    for (int i = 0; i < 8; ++i)
    {
        int factorial = 1;

        for (int j = 2; j <= 7 - i; ++j)
            factorial *= j;

        int index = coord / factorial;
		coord %= factorial;

		_edge_perm[i] = available[index];

        for (int j = index; j < 7 - i; ++j)
            available[j] = available[j + 1];
    }
}

// Corner Coord

int Cube::cornerOrientCoord() const
{
	int coord = 0;

	for (int i = 0; i < 7; i++)
		coord = coord * 3 + _corner_orient[i];
	return (coord);
}

void Cube::setFromCornersOrient(int coord)
{
	int sum = 0;
	for (int i = 6; i >= 0; i--)
	{
		_corner_orient[i] = coord % 3;
		sum += _corner_orient[i];
		coord /= 3;
	}
	_corner_orient[7] = (3 - (sum % 3)) % 3; // 8th corners depend of the 7 others
}

int Cube::cornerPermCoord() const
{
	int coord = 0;

	for (int i = 0; i < 7; i++)
	{
		int count = 0;

		for (int j = i + 1; j < 8; ++j)
		{
			if (static_cast<int>(_corner_perm[j]) < static_cast<int>(_corner_perm[i]))
				++count;
		}
		coord = coord * (8 - i) + count;
	}
	return (coord);
}

void Cube::setFromCornersPerm(int coord)
{
	CornerId available[8] = {
        CornerId::UFL, CornerId::UFR, CornerId::UBR, CornerId::UBL,
        CornerId::DFL, CornerId::DFR, CornerId::DBR, CornerId::DBL
    };

    for (int i = 0; i < 8; ++i)
    {
        int factorial = 1;

        for (int j = 2; j <= 7 - i; ++j)
            factorial *= j;

        int index = coord / factorial;
		coord %= factorial;

		_corner_perm[i] = available[index];

        for (int j = index; j < 7 - i; ++j)
            available[j] = available[j + 1];
    }
}

// Slice Coord

static int binomial(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	int result = 1;
	for (int i = 0; i < k; i++)
		result = result * (n - i) / (i + 1);
    return result;
}

bool Cube::isSliceEdge(EdgeId e) const
{
	return (e == EdgeId::FL
			|| e == EdgeId::FR
			|| e == EdgeId::BL
			|| e == EdgeId::BR);
}

int Cube::sliceCoord() const
{
    int coord = 0;
    int k = 3; // 4 edge slice pos remaining

    for (int i = 11; i >= 0 && k >= 0; i--)
    {
        if (isSliceEdge(_edge_perm[i]))
            k--;
        else
            coord += binomial(i, k);
    }
    return (coord);
}

void Cube::setFromSlice(int coord)
{
    int k = 3; // 4 edge slice pos remaining
    bool isSlice[12] = {};

    for (int i = 11; i >= 0; i--)
    {
		if (k < 0)
			break;

        int c = binomial(i, k);

		if (coord >= c)
		{
			coord -= c;
			isSlice[i] = false;
		}
		else
		{
			isSlice[i] = true;
			k--;
		}
	}

	EdgeId sliceIds[4] = {EdgeId::FL, EdgeId::FR, EdgeId::BL, EdgeId::BR};
	EdgeId nonSliceIds[8] = {EdgeId::UF, EdgeId::UR, EdgeId::UB, EdgeId::UL,
                          EdgeId::DF, EdgeId::DR, EdgeId::DB, EdgeId::DL};

	int si = 0;
	int nsi = 0;

	for (int i = 0; i < 12; i++)
	{
		if (isSlice[i])
			_edge_perm[i] = sliceIds[si++];
		else
			_edge_perm[i] = nonSliceIds[nsi++];
	}
}

int Cube::slicePermCoord() const
{
    EdgeId slice[4];
    int count = 0;

    for (int i = 0; i < 12; ++i)
    {
        if (isSliceEdge(_edge_perm[i]))
            slice[count++] = _edge_perm[i];
    }

    int coord = 0;

    for (int i = 0; i < 3; ++i)
    {
        int smaller = 0;

        for (int j = i + 1; j < 4; ++j)
        {
            if (static_cast<int>(slice[j]) <
                static_cast<int>(slice[i]))
                ++smaller;
        }

        coord = coord * (4 - i) + smaller;
    }

    return coord;
}

void Cube::setFromSlicePerm(int coord)
{
    EdgeId available[4] = {
        EdgeId::FL,
        EdgeId::FR,
        EdgeId::BL,
        EdgeId::BR
    };

    EdgeId slice[4];

    for (int i = 0; i < 4; ++i)
    {
        int factorial = 1;

        for (int j = 2; j <= 3 - i; ++j)
            factorial *= j;

        int index = coord / factorial;
        coord %= factorial;

        slice[i] = available[index];

        for (int j = index; j < 3 - i; ++j)
            available[j] = available[j + 1];
    }

    // Pour l'instant on remet les slice edges
    // dans les 4 positions slice.
    int s = 0;

    for (int i = 0; i < 12; ++i)
    {
        if (isSliceEdge(_edge_perm[i]))
            _edge_perm[i] = slice[s++];
    }
}

// Helpers

void Cube::print() const
{
	// Edges
	const char edges[][3] = {
		"UF", "UR", "UB", "UL",
		"DF", "DR", "DB", "DL",
		"FL", "FR", "BL", "BR"
	};
	std::cout << std::endl << "===== Edges =====" << std::endl;
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
	std::cout << "===== Coord =====" << std::endl;
	std::cout << "EdgeOrient = " << edgeOrientCoord() << std::endl;
	std::cout << "EdgePerm = " << edgePermCoord() << std::endl;
	std::cout << "CornerOrient = " << cornerOrientCoord() << std::endl;
	std::cout << "CornerPerm = " << cornerPermCoord() << std::endl;
	std::cout << "Slice = " << sliceCoord() << std::endl;
	std::cout << "SlicePerm = " << slicePermCoord() << std::endl;
	std::cout << "=================" << std::endl << std::endl;
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

// Moves

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