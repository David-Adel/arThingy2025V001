#version 330 core

layout(location=0) in vec3 in_position;
layout(location=1) in vec4 in_color;


out vec4 world_posv; // Position in world space.
out  vec4 v2f_colorv;
// Model, View, Projection matrix.

uniform mat4 MVP;

uniform mat4 model_matrix;

void main()
{
    gl_Position = MVP * vec4(in_position, 1);
	v2f_colorv = in_color;

	world_posv = model_matrix * vec4(in_position, 1); 
}