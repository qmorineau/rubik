#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include "Types.hpp"

struct Vertex
{
	Vector3 position;
	Vector3	normale;
	Vector3 color;

	Vertex() {};
	Vertex(const Vector3& pos, const Vector3& norm, const Vector3& color) :
		position(pos),
		normale(norm),
		color(color)
	{};

	void print()
	{
		std::cout << "pos" << position  << ", normale" << normale << ", color" << color << std::endl;
	};

	bool operator==(const Vertex& other) const
	{
		return (position == other.position && normale == other.normale && color == other.color);
	}
};

#endif