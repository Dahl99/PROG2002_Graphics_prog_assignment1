#version 430 core

/** Inputs */
layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoords;

/** Outputs */
out vec2 v_TexCoords;

/** Uniforms */
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoords = texCoords;
}