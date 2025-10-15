#version 330 core
out vec4 FragColor;

uniform sampler2D tex;

uniform vec3 viewPos; // 相机位置
uniform vec3 lightPos; // 灯光位置

uniform float ambientStrength;      // 环境光强度，例如 0.1
uniform float specularStrength;     // 镜面反射强度，例如 0.5
uniform float shininess;            // 高光指数，例如 32.0
uniform vec4 lightColor; //光照颜色

in vec4 oColor; //顶点色
in vec3 oNormal;
in vec3 FragPos; 

in vec2 vuv; 

vec3 blinnPhong(){
    // 归一化法线
    vec3 norm = normalize(oNormal);

    // 光照方向（从片段指向光源）
    vec3 lightDir = normalize(lightPos - FragPos);

    // 观察方向（从片段指向相机）
    vec3 viewDir = normalize(viewPos - FragPos);

    // 半角向量（Blinn-Phong 关键）
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // 环境光
    vec3 ambient = ambientStrength * lightColor.rgb;

    // 漫反射
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb;

    // 镜面反射（Blinn-Phong）
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor.rgb;

    // 从纹理采样物体基础颜色（漫反射颜色）
    vec3 objectColor = texture(tex, vuv).rgb;

    // 最终光照结果 = (环境 + 漫反射 + 镜面) * 纹理颜色
    vec3 result = (ambient + diffuse + specular) * objectColor;
    // vec3 result2 = (ambient + diffuse + max(vec3(0, 0, 0), specular)) * objectColor;

    // return result2;
    // return objectColor;
    // return specular * objectColor;
    // return ambient * objectColor;
    return result;
    // return specular;
}

void main() {
    // vec4 c = texture(tex, vuv);
    vec3 c = blinnPhong();
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // FragColor = color;
    // FragColor = diffuse;
    // FragColor = (1.0 - c.a) * vec4(1.0, 1.0, 1.0, 1.0) + c.a * c ;
    // FragColor = vec4(1.0, 0.0, 0.0 , 1.0);
    // FragColor = vec4(vuv, 0.0, 1.0);
    // FragColor = c;
    FragColor = vec4(c, 1.0);
    // FragColor = vec4(ambientStrength, 0.0, 0.0, 1.0);
    // FragColor = vec4(shininess , 0.0, 0.0, 1.0);
} 