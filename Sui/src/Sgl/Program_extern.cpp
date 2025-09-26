
#include "./UnitOpengl.h"
#include "./Program_orc.h"
#include <stdio.h>


bool  Sgl$Program$compile(Sgl$Program *  self, 
    const char *  vs, const char *  fs){


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);


    {
        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("compile vertex shader error:%s\n", infoLog);
            return false;
        }
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);


    {
        int  success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("compile fragment shader error:%s\n", infoLog);
            return false;
        }
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    {
        int  success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            printf("link program error:%s\n", infoLog);
            return false;
        }
    }
    self->id = shaderProgram;
    // self->vsId = vertexShader;
    // self->fsId = fragmentShader;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}
void  Sgl$Program$use(Sgl$Program *  self){
    glUseProgram(self->id);
}
void  Sgl$deleteProgram(GLuint id){
    //会有bug, 释放可能是在别的线程释放的。。。。。。
    glDeleteProgram(id);
}
void  Sgl$Program$uniform1i(Sgl$Program *  self, const char *  key, int x)
{
    int loc = glGetUniformLocation(self->id, key);
    glUniform1i(loc, x);
}
void  Sgl$Program$uniform2f(Sgl$Program *  self, const char *  key, float  x, float  y)
{
    int loc = glGetUniformLocation(self->id, key);
    glUniform2f(loc, x, y);
}
void  Sgl$Program$uniform3f(Sgl$Program *  self, const char *  key, float  x, float  y, float  z)
{
    int loc = glGetUniformLocation(self->id, key);
    glUniform3f(loc, x, y, z);
}
void  Sgl$Program$uniform4f(Sgl$Program *  self, const char *  key, float  x, float  y, float  z, float  w)
{
    int loc = glGetUniformLocation(self->id, key);
    glUniform4f(loc, x, y, z, w);
}
void  Sgl$Program$uniformMatrix4fv(Sgl$Program *  self, const char *key, float *data, int matrixCnt)
{
    int loc = glGetUniformLocation(self->id, key);
    if (loc >= 0){
        glUniformMatrix4fv(loc, matrixCnt, GL_FALSE, data);
    }
}