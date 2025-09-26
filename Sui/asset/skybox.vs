#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 idxUv;


uniform mat4 mvp;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oIdxUv; 

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    oIdxUv = idxUv;
}