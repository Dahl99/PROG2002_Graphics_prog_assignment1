#version 430 core

in vec2 v_TexCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
	vec4 texColor = texture(uTexture, v_TexCoords);
	FragColor = texColor;
}