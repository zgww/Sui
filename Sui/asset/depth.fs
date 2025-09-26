
#version 330 core
out vec4 FragColor;

void main()
{
    gl_FragDepth = gl_FragCoord.z;//这行其实也可以去掉
    FragColor = vec4(0.5, 0.0, 0.0, 1.0);
}
