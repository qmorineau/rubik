#include "CubeMesh.hpp"

CubeMesh::CubeMesh()
{
	const vec3	v[8] = {
		vec3(-0.5f, 0.5f, 0.5f),
		vec3(0.5f, 0.5f, 0.5f),
		vec3(0.5f, 0.5f, -0.5f),
		vec3(-0.5f, 0.5f, -0.5f),
		vec3(-0.5f, -0.5f, 0.5f),
		vec3(0.5f, -0.5f, 0.5f),
		vec3(0.5f, -0.5f, -0.5f),
		vec3(-0.5f, -0.5f, -0.5f),
	};

	const int	index[6][4] = {
		{0, 1, 2, 3},
		{0, 3, 7, 4},
		{3, 2, 6, 7},
		{2, 1, 5, 6},
		{0, 1, 5, 4},
		{4, 5, 6, 7}
	};

	const vec3	normale[6] = {
		vec3(0, 1, 0),
		vec3(-1, 0, 0),
		vec3(0, 0, -1),
		vec3(1, 0, 0),
		vec3(0, 0, 1),
		vec3(0, -1, 0)
	};

	const vec3 color[6] = {
		vec3(0.8, 0.8, 0.8),
		vec3(0, 0.8, 0),
		vec3(0.95, 0.33, 0.08),
		vec3(0, 0, 0.8),
		vec3(0.8, 0, 0),
		vec3(0.8, 0.8, 0),
	};

	const vec3 offset[6] = {
		vec3(0, 0.06, 0),
		vec3(-0.06, 0, 0),
		vec3(0, 0, -0.06),
		vec3(0.06, 0, 0),
		vec3(0, 0, 0.06),
		vec3(0, -0.06, 0)
	};

	float size = 1.f;
	for (int i = 0; i < 6; i++)
	{
		vec3 face[4] = {v[index[i][0]] * size,
			v[index[i][1]] * size,
			v[index[i][2]] * size,
			v[index[i][3]] * size
		};
		addFace(face, normale[i], vec3(0, 0, 0));
	}
	size = 0.9;
	for (int i = 0; i < 6; i++)
	{
		vec3 face[4] = {v[index[i][0]] * size + offset[i],
			v[index[i][1]] * size + offset[i],
			v[index[i][2]] * size + offset[i],
			v[index[i][3]] * size + offset[i]
		};
		addFace(face, normale[i], color[i]);
	}
}

CubeMesh::~CubeMesh() = default;

void CubeMesh::addFace(vec3 v[4], vec3 n, vec3 color)
{
	int	index[6] = {0, 1, 2, 0, 2, 3};

	for (int i = 0; i < 6; i++)
	{
		Vertex vertex;

		vertex.position = v[index[i]];
		vertex.normale = n;
		vertex.color = color;
		_vertices.push_back(vertex);
	}
}
