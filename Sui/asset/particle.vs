#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 insPos;


uniform mat4 mvp;
uniform mat4 model;


// varying vec4 oColor;
out vec4 oColor;
out vec3 oNormal;
out vec3 FragPos; 

out vec2 vuv; 


void main()
{
    
    // gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    vec3 pos = position + insPos;
    gl_Position = mvp * vec4(pos, 1.0);

    oColor = color;
    // oNormal = normal;
    //法线坐标转换
    oNormal = mat3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(pos, 1.0));


    vuv = uv;
}