#ifndef CUBEMESH_HPP
#define CUBEMESH_HPP

#include <vector>
#include <string>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Types.hpp"

class CubeMesh
{
	public:
		CubeMesh();
		~CubeMesh();

		const std::vector<Vertex>&	vertices() const {return _vertices;}; 
	private:
		std::vector<Vertex>		_vertices;
	
		void addFace(vec3 v[4], vec3 n, vec3 color);
};

#endif