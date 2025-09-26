
#version 330 core
out vec4 FragColor;


uniform sampler2D tex;
uniform vec2 texSize;

uniform vec4 time;
uniform vec4 color;

in vec4 oColor;
in vec3 oNormal;
in vec3 FragPos; 

in vec2 vuv; 


void main() {
    vec2 invSize = 1.0 / texSize;
    vec4 uvOffset = vec4(1.0, 0.0, 0.0, 1.0)  * vec4(invSize, invSize);
    vec4 c = texture2D(tex, vuv);
    vec4 c1 = texture2D(tex, vuv + uvOffset.xy);
    vec4 c2 = texture2D(tex, vuv - uvOffset.xy);
    vec4 c3 = texture2D(tex, vuv + uvOffset.yw);
    vec4 c4 = texture2D(tex, vuv - uvOffset.yw);

    //跨2像素
    vec4 c21 = texture2D(tex, vuv + uvOffset.xy*2);
    vec4 c22 = texture2D(tex, vuv - uvOffset.xy*2);
    vec4 c23 = texture2D(tex, vuv + uvOffset.yw*2);
    vec4 c24 = texture2D(tex, vuv - uvOffset.yw*2);

    //跨3像素
    vec4 c31 = texture2D(tex, vuv + uvOffset.xy*3);
    vec4 c32 = texture2D(tex, vuv - uvOffset.xy*3);
    vec4 c33 = texture2D(tex, vuv + uvOffset.yw*3);
    vec4 c34 = texture2D(tex, vuv - uvOffset.yw*3);

    float diff1 = ((c1.r - c.r) + (c2.r - c.r) + (c21.r - c.r) + (c22.r - c.r) + (c31.r - c.r) + (c32.r - c.r)) * 0.5;
    float diff2 = ((c3.r - c.r) + (c4.r - c.r) + (c23.r - c.r) + (c24.r - c.r) + (c33.r - c.r) + (c34.r - c.r)) * 0.5;
    float d = length(vec2(diff1, diff2));

    vec4 lineC = vec4(0.902, 0.5843, 0.0, 1.0);
    // vec4 lineC = vec4(1.0, 0.0, 0.0, 1.0);
    // FragColor = vec4(0.0, 0.0, 1.0, 1.0) * vec4(d, d, d, d);


    if (c.r > 0 && d > 0.0){//边缘的两边，两像素
        FragColor = lineC * vec4(d, d, d, 1.0);
    }
    else {
        FragColor = lineC * vec4(d, d, d, 0.0);
    }



    // vec4 c = texture(tex, vuv);
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // FragColor = vec4(vuv, 0.0, 1.0);
    // FragColor = (1.0 - c.a) * vec4(1.0, 1.0, 1.0, 1.0) + c.a * c ;
    // FragColor = vec4(1.0, 0.0, 0.0 , 1.0);
} 