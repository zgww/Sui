
#version 330 core
out vec4 FragColor;


uniform sampler2D tex;
uniform vec4 time;
uniform vec4 color;

in vec4 oColor;
in vec3 oNormal;
in vec3 FragPos; 

in vec2 vuv; 


void main() {
    // vec4 c = texture(tex, vuv);
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = color;
    // FragColor = (1.0 - c.a) * vec4(1.0, 1.0, 1.0, 1.0) + c.a * c ;
    // FragColor = vec4(1.0, 0.0, 0.0 , 1.0);
} 