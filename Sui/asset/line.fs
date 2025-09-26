
#version 330 core
out vec4 FragColor;
in vec4 oColor;

void main()
{
    // gl_FragDepth = gl_FragCoord.z;//这行其实也可以去掉
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = oColor;
}
