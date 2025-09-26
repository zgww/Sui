#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 insPos;

layout (location = 5) in vec4 skinIndex;
layout (location = 6) in vec4 skinWeight;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 shadowVp;//阴影mvp矩阵


//最多支持20个关节
uniform mat4 boneMatrix[50];


// varying vec4 oColor;
out vec4 oColor;
out vec3 oNormal;
out vec3 FragPos; 

out vec2 vuv; 

//投影后的坐标在[-1,1]之间
out vec4 lightViewVertexPos;//在灯的投影坐标

out vec4 oSkinIndex;
out vec4 oSkinWeight;

void main()
{
    
    vec3 pos = position + insPos;
    //vec3 pos = position;
    // gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);


    int boneIndex = int(skinIndex.x + 0.001);
    mat4 bone0 = boneMatrix[boneIndex];


    gl_Position = mvp* bone0 * vec4(pos, 1.0);
    // gl_Position = mvp* vec4(pos, 1.0);
    oColor = color;
    //oNormal = normal;
    //法线坐标转换到世界空间; 法线矩阵 transpose(inverse(model))。因为法线只有方向性
    //因为法线是方向向量，只表示方向，不受平移影响，而且如果模型矩阵包含非均匀缩放（比如 x 缩放 2 倍，y 不变），
    //直接用 model 变换会导致法线不再垂直于表面
    oNormal = mat3(transpose(inverse(model))) * normal;
    //oNormal = mat3(model) * normal;  
    FragPos = vec3(model * vec4(position, 1.0));


    lightViewVertexPos = shadowVp * model * vec4(pos, 1.0);
    lightViewVertexPos /= lightViewVertexPos.w;//齐次
    vuv = uv;

    oSkinIndex = skinIndex;
    oSkinWeight = skinWeight;
}