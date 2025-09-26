
#include "./UnitOpengl.h"
#include "./Geometry_orc.h"
#include "Orc/Orc.h"



bool  Sgl$GeoAttr$bindVertexAttrib(
    Sgl$GeoAttr* self,
    Sgl$Material* matl
)
{
    if (matl && matl->program && self->key && self->vbo){
        self->vbo->vaIndex = glGetAttribLocation(matl->program->id, self->key->str);
        //顶点属性可能名字错了。 或者未被使用，被自动优化了
        if (self->vbo->vaIndex < 0){
            printf("shader:%s;%s glGetAttribLocation fail. key:%s\n",
                matl->program->getVsPathCstr(matl->program),
                matl->program->getFsPathCstr(matl->program),
                 self->key->str);
            // return false;
        }
        else {
            self->vbo->setVertexAttrib(
                self->vbo
            );
        }
        return true;
    }
    return false;


}