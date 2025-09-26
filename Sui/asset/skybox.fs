#version 330 core

out vec4 FragColor;

uniform sampler2D tex[6];

in vec3 oIdxUv; 

void main()
{
    int idx = int(oIdxUv.x+0.01);
    vec2 uv = oIdxUv.yz;

    vec4 c = texture(tex[idx], uv);
    FragColor = vec4(c.rgb, 0.5);
    FragColor = c;
} 