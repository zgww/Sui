#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

layout (location = 4) in vec4 tilesets;
layout (location = 5) in vec2 uv0;
layout (location = 6) in vec2 uv1;
layout (location = 7) in vec2 uv2;
layout (location = 8) in vec2 uv3;

uniform mat4 mvp;
uniform mat4 model;

//@editor Color
//@default 1 1 2 1
uniform vec4 uColor;


// varying vec4 oColor;
out vec4 oColor;
out vec2 oPixel;
out vec3 oNormal;
out vec3 FragPos; 

out vec4 vtilesets; 
out vec2 vuv0; 
out vec2 vuv1; 
out vec2 vuv2; 
out vec2 vuv3; 


void main()
{
    
    // gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    gl_Position = mvp*vec4(position.x, position.y, position.z, 1.0);
    oColor = color;
    oPixel = texCoord;
    // oNormal = normal;
    //法线坐标转换
    oNormal = mat3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(position, 1.0));


    vtilesets = tilesets;
    vuv0 = uv0;
    vuv1 = uv1;
    vuv2 = uv2;
    vuv3 = uv3;
}