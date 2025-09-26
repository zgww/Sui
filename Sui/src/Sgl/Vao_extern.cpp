
#include "./UnitOpengl.h"
#include "./Vao_orc.h"
#include "Orc/Orc.h"



void  Sgl$Vao$gen(Sgl$Vao *  self){
    glGenVertexArrays(1, &self->id);
}
void  Sgl$Vao$bind(Sgl$Vao *  self){
    glBindVertexArray(self->id);
}
void  Sgl$Vao$unbind(Sgl$Vao *  self){
    glBindVertexArray(0);
}
void  Sgl$deleteVertexArray(GLuint id)
{
    glDeleteVertexArrays(1, &id);
}
void  Sgl$Vao$drawInstanced(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  matl)
{
    int instanceCount = geometry->instanceVbo->calcInstanceCount(
            geometry->instanceVbo
    );
    if (instanceCount > 0){
        int indexCount = geometry->ibo->calcIndexCount(geometry->ibo);
        glDrawElementsInstanced(
            GL_TRIANGLES, 
            indexCount, 
            GL_UNSIGNED_INT, 
            0,
            instanceCount);
    }
}