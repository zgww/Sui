#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 insPos;


uniform mat4 mvp;
uniform mat4 model;

void main()
{
    gl_Position = mvp*vec4(position, 1.0);
}