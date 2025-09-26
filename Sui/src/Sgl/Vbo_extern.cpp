
#include "./UnitOpengl.h"
#include "./Vbo_orc.h"
#include "Orc/Orc.h"



void  Sgl$Vbo$genBuffer(Sgl$Vbo *  self){
    glGenBuffers(1, &self->id);
}
void  Sgl$Vbo$bind(Sgl$Vbo *  self){
    if (self->isIndices){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->id);
    }
    else {
        glBindBuffer(GL_ARRAY_BUFFER, self->id);
    }
}
void  Sgl$Vbo$setVertexAttrib(Sgl$Vbo *  self){
    self->bind(self);

    if (self->isFloat){
        glVertexAttribPointer(self->vaIndex, 
            self->elementCount,
            GL_FLOAT, GL_FALSE, self->elementCount * sizeof(float), (void*)0);
    }
    else if (self->isInt){
        glVertexAttribPointer(self->vaIndex, 
            self->elementCount,
            GL_INT, GL_FALSE, self->elementCount * sizeof(int), (void*)0);
    }
    else {
        printf("!!unknown VertexAttrib type\n");
    }
    if (self->divide > 0){
        glVertexAttribDivisor(self->vaIndex, self->divide);
    }
    glEnableVertexAttribArray(self->vaIndex);
}

void  Sgl$Vbo$arrayBufferData(Sgl$Vbo *  self
    , int byteSize
    , float *vertices
){
    self->isIndices = false;
    self->byteSize = byteSize;

    glBindBuffer(GL_ARRAY_BUFFER, self->id);

    glBufferData(
        GL_ARRAY_BUFFER,
        byteSize,
        vertices,
        self->usage
    );
}
void  Sgl$Vbo$elementBufferData(Sgl$Vbo *  self
    , int byteSize
    , int *vertices

){
    self->isIndices = true;
    self->byteSize = byteSize;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->id);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        byteSize,
        vertices,
        self->usage
    );
}
void  Sgl$deleteBuffer(GLuint id){
    glDeleteBuffers(1, &id);
}
