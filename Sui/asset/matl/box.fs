
#version 330 core
out vec4 FragColor;

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float distance;
    float decay;
};
struct DirLight {
    vec3 direction; //从光源指向物体
    vec3 ambient; //环境光系数
    vec3 diffuse; //漫反射颜色
    vec3 specular; // 镜面反射颜色
};

// 计算方向光
vec3 calDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 objectColor) {
    //环境光
    vec3 ambient = light.ambient * objectColor;
    // 漫反射
    vec3 diffuse = max(dot(normal, -light.direction), 0.0) * light.diffuse * objectColor;

    vec3 reflectDir = reflect(light.direction, normal);
    float shininess = 32.0; // Adjust shininess as needed
    //镜面反射
    vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), shininess) * light.specular * objectColor;
    return ambient + diffuse + specular;
    // return ambient ;
    // return diffuse + specular;
    // return specular;
    // return objectColor;
}



uniform sampler2D tex;
uniform sampler2D shadowMap;
uniform PointLight pointLight;
uniform DirLight dirLight;
uniform vec4 time;
uniform bool hasShadow;

in vec4 oColor;
in vec3 oNormal;
in vec3 FragPos; 

in vec2 vuv; 
in vec4 lightViewVertexPos;//在灯的投影坐标

// varying vec4 oColor;


// //@default 10.0 10 10
// uniform vec3 eyePos;

//@default -5.2 6.0 -6.0
// uniform vec3 lightPos;

float LinearizeDepth(float depth) {
    float near = 100.1;
    float far = 3000.0;
    float z = depth * 2.0 - 1.0; // back to NDC 
    float linear = (2.0 * near * far) / (far + near - z * (far - near));
    return linear / far; // 归一化到 [0,1]
}

float calcShadow(vec4 position){
    float bias = 0.015;//片元共享深度，导致距离 不同
    float shadowFactor = 1.0;
    vec3 projCoords = position.xyz;
    projCoords = projCoords * 0.5 + 0.5; // [-1, 1]=>[0, 1]
    if (projCoords.z - bias < texture(shadowMap, projCoords.xy).r){
        //不在阴影中
        shadowFactor = 0.0;
    }
    return 1.0 - shadowFactor;
}

void main() {
    FragColor = vec4(vuv, 0.0f, 1.0f);
    vec4 c = texture(tex, vuv);
    FragColor = c;

    vec3 objectColor = c.rgb; //vec3(1.0f, 0.5f, 0.31f);//0.4, 0.4, 0.4, 1.0);
    vec3 lightColor = pointLight.color;
    vec3 lightPos = pointLight.position;
    lightPos.x += time[0] * 500.0;
    vec3 viewPos = vec3(0.0, 1000.0, 1000.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // vec3 norm = vec3(0.0, 1.0, 0.0);//normalize(oNormal);
    vec3 norm = normalize(oNormal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.8;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // vec3 result = (ambient + diffuse) * objectColor;


    // DirLight tmp;
    // tmp.direction = vec3(0.0, -1.0, 0.0);
    // tmp.ambient = vec3(0.5, 0.5, 0.5);
    // tmp.diffuse = vec3(0.5, 0.5, 0.5);
    // tmp.specular = vec3(1.0, 1.0, 1.0);
    // vec3 result = calDirLight(tmp, norm, viewDir, objectColor);
    vec3 result = calDirLight(dirLight, norm, viewDir, objectColor);

    // FragColor = vec4(dirLight.diffuse, 1.0);

    // FragColor = vec4(pointLight.color, 1.0);
    FragColor = vec4(result, 1.0);
    // FragColor = vec4(LinearizeDepth(objectColor.r), 0.0, 0.0, 1.0);
    FragColor = vec4(objectColor , 1.0);
    if (hasShadow){
        float shadow = calcShadow(lightViewVertexPos);
        FragColor = vec4(objectColor * shadow, 1.0);
        // if (shadow <= 0.5){
        //     FragColor = vec4(0.0, 0.0, 1.0, 1.0);
        // }
        // FragColor = vec4(lightViewVertexPos.xy / 1.0, 0.0, 1.0);
    }
    // FragColor = vec4(vuv, 0.0, 1.0);
    // FragColor = vec4(1.0, 0.0, 0.0, 0.5);
    // FragColor = vec4(vuv, 0.0, 1.0);
    // FragColor = vec4(lightPos/ 1000.0, 1.0);
    // FragColor = vec4(diffuse, 1.0);
    // FragColor = vec4(oNormal, 1.0);
    // FragColor = oColor;
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
} 