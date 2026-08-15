#include "Renderer.hpp"
#include "CubeMeshGPU.hpp"
#include "Matrix4.hpp"
#include "Math.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

Renderer::Renderer() :
	_shader("assets/shaders/shader.vs", "assets/shaders/shader.fs")
{};

Renderer::~Renderer() {};

void Renderer::beginFrame(vec3 v)
{
	glClearColor(v.x, v.y, v.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(Scene* scene)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Use shader
    _shader.use();

	// Camera
	Camera& camera = scene->camera();
    mat4 projection = mat4::perspective(math::radians(camera.getZoom()), camera.getAspectRatio(), 0.001f, 100.0f);
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", camera.getViewMatrix());
	_shader.setVec3("viewPos", vec3(camera.getPosition()));

	// // Model
	const auto& mesh = scene->cube().mesh();
	const auto& cubelets = scene->cube().cubelets();
	for (auto i = 0; i < 27; i++)
	{
    	// _shader.setMat4("model", cubelets[i].translate.mul_mat(cubelets[i].orient));
		_shader.setMat4("model", scene->cube().getModelMatrix(i));
		_shader.setMat4("orient", cubelets[i].orient);
		_shader.setVec3("translate", cubelets[i].translate_pos);
		mesh.draw(_shader);
	}
}
