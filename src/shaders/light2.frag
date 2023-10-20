#version 330 core

out vec4 FragColor;

uniform vec4 lightColor2;

void main()
{
	FragColor = lightColor2;
}