#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class Scene;

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void beginFrame(vec3);
		void draw(Scene* scene);
	private:
		Shader			_shader;
};

#endif