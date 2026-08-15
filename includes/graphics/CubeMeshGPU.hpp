#ifndef CUBEMESHGPU_HPP
#define CUBEMESHGPU_HPP

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include "CubeMesh.hpp"
#include "Types.hpp"

class Shader;

class CubeMeshGPU
{
	public:
		CubeMeshGPU(CubeMesh&);
		~CubeMeshGPU();

		void draw(Shader&) const;

	private:
		GLuint		_vao = 0;
		GLuint		_vbo = 0;
		CubeMesh&	_mesh;

		void upload();
};

#endif