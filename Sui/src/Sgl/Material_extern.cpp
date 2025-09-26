
#include "./UnitOpengl.h"
#include "./Material_orc.h"
#include <stdio.h>


void  Sgl$Material$endDraw(Sgl$Material *  self){
    if (self->wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
void  Sgl$Material$prepareDraw(Sgl$Material *  self){
    // glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_STENCIL_TEST);
    // glDisable(GL_CULL_FACE);


    if (self->depthTest) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);

    // glDepthMask(false);
    // glDepthMask(self->depthWrite);

    if (self->blend) glEnable(GL_BLEND);
    else glDisable(GL_BLEND);


    if (self->stencilTest) glEnable(GL_STENCIL_TEST);
    else glDisable(GL_STENCIL_TEST);

    if (self->alphaTest) glEnable(GL_ALPHA_TEST);
    else glDisable(GL_ALPHA_TEST);

    if (self->scissorTest) glEnable(GL_SCISSOR_TEST);
    else glDisable(GL_SCISSOR_TEST);

    if (self->cullFace) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);

    if (self->wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}