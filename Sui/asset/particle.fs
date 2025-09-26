
#version 330 core
out vec4 FragColor;

uniform sampler2D tex;



in vec4 oColor;
in vec3 oNormal;
in vec3 FragPos; 

in vec2 vuv; 



void main()
{
    vec4 c = texture(tex, vuv);
    FragColor = vec4(c.rgb, 0.5);
 
} 