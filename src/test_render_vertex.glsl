#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color; // the color variable has attribute position 1
out vec4 vertexColor;

uniform float green;

#define PI 3.14159265359

void main()
{
	float angle = 8 * PI * green;
	gl_Position = vec4(pos.x + 0.5 * sin(angle), pos.y + 0.5 * cos(angle), pos.z, 1.0);
	vertexColor = vec4(color, 1.0);
}