
#version 330 core
out vec4 FragColor;

uniform sampler2D tex;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform sampler2D tex6;


struct Fog
{
    int active;
    vec3 color;
    float density;
};
vec4 calcFog(vec3 pos, vec4 color, Fog fog)
{
    float distance = length(pos);
    float fogFactor = 1.0 / exp( (distance * fog.density)* (distance * fog.density));
    fogFactor = clamp( fogFactor, 0.0, 1.0 );
    vec3 resultColor = mix(fog.color, color.xyz, fogFactor);
    return vec4(resultColor.xyz, color.w);
}

in vec4 oColor;
in vec2 oPixel;
in vec3 oNormal;
in vec3 FragPos; 

in vec4 vtilesets; 
in vec2 vuv0; 
in vec2 vuv1; 
in vec2 vuv2; 
in vec2 vuv3; 
in vec3 mvVertexPos;

// varying vec4 oColor;

//@editor Color4f
//@default 1.0 0.0 1.0 1.0
uniform vec4 uColor;

//@editor Color3f
//@default 1.0 0.5 0.3
uniform vec3 objColor;

// //@default 10.0 10 10
// uniform vec3 eyePos;

//@default -5.2 6.0 -6.0
// uniform vec3 lightPos;


vec4 getTileColor(float subtile, vec2 uv){
    int t = int(subtile + 0.1);
    if (t == 0){ return texture(tex0, uv); }
    else if (t == 1){ return texture(tex1, uv); }
    else if (t == 2){ return texture(tex2, uv); }
    else if (t == 3){ return texture(tex3, uv); }
    else if (t == 4){ return texture(tex4, uv); }
    else if (t == 5){ return texture(tex5, uv); }
    else if (t == 6){ return texture(tex6, uv); }

    return vec4(0.0, 0.0, 0.0, 0.0);
}

void main()
{
    Fog fog;
    fog.color = vec3(1.0, 1.0, 1.0);
    fog.density = 0.0010;

    vec4 tilec = getTileColor(vtilesets.x, vuv0);
    vec4 tilec1 = getTileColor(vtilesets.y, vuv1);
    vec4 tilec2 = getTileColor(vtilesets.z, vuv2);
    vec4 tilec3 = getTileColor(vtilesets.w, vuv3);

    tilec = mix(tilec, tilec1, tilec1.a);
    tilec = mix(tilec, tilec2, tilec2.a);
    tilec = mix(tilec, tilec3, tilec3.a);


    vec3 objectColor = tilec.rgb; //vec3(1.0f, 0.5f, 0.31f);//0.4, 0.4, 0.4, 1.0);
    // vec3 lightColor = uColor.rgb;//vec3(0.0f, 1.0f, 0.0f);
    vec3 lightColor = vec3(1.0, 0.8, 0.3);
    vec3 lightPos = vec3(0.0, 0.0, 2000.0);

    vec3 viewPos = vec3(0.0, -1000.0, 2000.0);


    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = vec3(0.0, 0.0, 1.0);//normalize(oNormal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    float specularStrength = 0.8;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // objectColor = vec3(1.0f, 0.5f, 0.31f); //vec3(1.0f, 0.5f, 0.31f);
    // vec3 result = (ambient + diffuse + specular ) * objectColor;
    vec3 result = (ambient + diffuse) * objectColor;
    // vec3 result = (ambient ) * objectColor;

    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // FragColor = vec4(oColor, 1.0f);
    // FragColor = oColor;//vec4(oColor, 1.0f);
    // FragColor = uColor;
    // FragColor = vec4(oPixel, 0.0f, 1.0f);
    // FragColor = vec4(c.rgb, 1.0);
    // vec4 c = texture(tex, oPixel);
    // FragColor = c;
    // FragColor = vec4(oNormal, 1.0);

    // FragColor = vec4(result, 1.0);
    // FragColor = uColor;
    // FragColor = vec4(1.0, 1.0, 0.0, 1.0);


    vec4 c = texture(tex, vuv0);
    FragColor = c;
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = calcFog(mvVertexPos, FragColor, fog);


    // tilec = mix(tilec, getTileColor(vtilesets.w, vuv3), tilec.a);
    // FragColor = vec4(vuv0, 0.0, 1.0);
    // FragColor = tilec;
    // FragColor = vec4(
    //     vtilesets.x / 17.0, 
    //     vtilesets.y / 17.0,
    //     vtilesets.z / 17.0,
    //     1.0);
} 