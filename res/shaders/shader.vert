#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
//layout(location = 2) in vec2 texCoords;

out vec4 VertexColor;
//out vec2 vTexCoords;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	VertexColor = color;
	//vTexCoords = texCoords;
}