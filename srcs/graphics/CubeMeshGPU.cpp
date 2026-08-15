#include "CubeMeshGPU.hpp"

#include "Shader.hpp"

CubeMeshGPU::CubeMeshGPU(CubeMesh& mesh) : _mesh(mesh)
{
	upload();
}

CubeMeshGPU::~CubeMeshGPU() = default;

void CubeMeshGPU::upload()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _mesh.vertices().size() * sizeof(Vertex), _mesh.vertices().data(), GL_STATIC_DRAW);

	GLsizei stride = sizeof(Vertex);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, normale));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
}

void CubeMeshGPU::draw(Shader& shader) const
{
	shader.use();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_mesh.vertices().size()));
}