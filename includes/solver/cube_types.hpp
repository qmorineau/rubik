#ifndef CUBE_TYPES_HPP
#define CUBE_TYPES_HPP

#include <cstdint>

enum class EdgeId : uint8_t
{
	UF = 0,
	UR = 1,
	UB = 2,
	UL = 3,
	DF = 4,
	DR = 5,
	DB = 6,
	DL = 7,
	FL = 8,
	FR = 9,
	BL = 10,
	BR = 11
};

enum class EdgePos : uint8_t
{
	UF = 0,
	UR = 1,
	UB = 2,
	UL = 3,
	DF = 4,
	DR = 5,
	DB = 6,
	DL = 7,
	FL = 8,
	FR = 9,
	BL = 10,
	BR = 11
};

enum class CornerId : uint8_t
{
	UFL = 0,
	UFR = 1,
	UBR = 2,
	UBL = 3,
	DFL = 4,
	DFR = 5,
	DBR = 6,
	DBL = 7
};

enum class CornerPos : uint8_t
{
	UFL = 0,
	UFR = 1,
	UBR = 2,
	UBL = 3,
	DFL = 4,
	DFR = 5,
	DBR = 6,
	DBL = 7
};

enum class Move : uint8_t
{
	U, UPrime, U2,
	D, DPrime, D2,
	L, LPrime, L2,
	R, RPrime, R2,
	F, FPrime, F2,
	B, BPrime, B2
};

template <typename EnumT>
constexpr auto toIndex(EnumT e) noexcept
{
	return static_cast<std::underlying_type_t<EnumT>>(e);
};

#endif