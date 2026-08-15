#version 330 core

out vec4 FragColor;

flat in vec3 FaceColor;

void main()
{
	FragColor = vec4(FaceColor, 1);
}