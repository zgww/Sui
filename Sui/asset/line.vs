#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 mvp;
uniform mat4 model;

out vec4 oColor;

void main()
{
    //gl_Position = mvp*vec4(position, 1.0);
    gl_Position = mvp * vec4(position, 1.0);
    oColor = color;
}