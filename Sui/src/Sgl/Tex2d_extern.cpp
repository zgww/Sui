
#include "./UnitOpengl.h"
#include "./Tex2d_orc.h"
#include "Orc/Orc.h"
#include "nanovg/nanovg.h"

#define NANOVG_GL3
#include "../nanovg/nanovg_gl.h"


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../nanovg/stb_image_write.h"
#include "../Sui/Core/Global_orc.h"

void  Sgl$Tex2d$gen(Sgl$Tex2d *  self){
    glGenTextures(1, &self->id);
}
void  Sgl$deleteTexture(GLuint id){
    glDeleteTextures(1, &id);
}

void  Sgl$Tex2d$bind(Sgl$Tex2d *  self){
    glBindTexture(GL_TEXTURE_2D, self->id);
}
void  Sgl$Tex2d$unbind(Sgl$Tex2d *  self){
    glBindTexture(GL_TEXTURE_2D, 0);
}
void  Sgl$Tex2d$active(Sgl$Tex2d *  self, int offset){
    glActiveTexture(GL_TEXTURE0 + offset);
}
void  Sgl$Tex2d$updateParameters(Sgl$Tex2d *  self){
    self->bind(self);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, self->wrapS);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, self->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, self->minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, self->magFilter);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
}
void  Sgl$Tex2d$generateMipmap(Sgl$Tex2d *  self){
    glGenerateMipmap(GL_TEXTURE_2D);
}
void  Sgl$Tex2d$image2dRgba(Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h)
{
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_RGBA;
    self->channelCount = 4;

    glTexImage2D(GL_TEXTURE_2D, 
    0, GL_RGBA, 
    w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
}
void  Sgl$Tex2d$image2dRgb(Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h)
{
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_RGB;
    self->channelCount = 3;

    glTexImage2D(GL_TEXTURE_2D, 
    0, GL_RGB, 
    w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
}
void  Sgl$Tex2d$image2dRed8(Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h)
{
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_RED;
    self->channelCount = 1;

    glTexImage2D(GL_TEXTURE_2D, 
    0, GL_RED, 
    w, h, 0, GL_RED, 
    GL_UNSIGNED_BYTE, buf);
}
void  Sgl$Tex2d$initForDepthAttachment(Sgl$Tex2d *  self, int w, int h){
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_DEPTH_COMPONENT;
    self->channelCount = 4;

    // self->updateParameters(self);

    glTexImage2D(
    GL_TEXTURE_2D, 0, 
    GL_DEPTH_COMPONENT, w, h, 0, 
    GL_DEPTH_COMPONENT, GL_FLOAT, NULL
    );
}
void  Sgl$Tex2d$initForStencilAttachment(Sgl$Tex2d *  self, int w, int h){
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_STENCIL_INDEX;
    self->channelCount = 4;

    glTexImage2D(
    GL_TEXTURE_2D, 0, 
    GL_STENCIL_INDEX, w, h, 0, 
    GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL
    );
}
void  Sgl$Tex2d$initForDepth32fStencil8Attachment(Sgl$Tex2d *  self, int w, int h){
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_DEPTH32F_STENCIL8;
    self->channelCount = 4;

    glTexImage2D(
    GL_TEXTURE_2D, 0, 
    GL_DEPTH32F_STENCIL8, w, h, 0, 
    GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL
    );
}
void  Sgl$Tex2d$initForDepth24Stencil8Attachment(Sgl$Tex2d *  self, int w, int h){
    self->bind(self);

    self->width = w;
    self->height = h;
    self->format = GL_DEPTH24_STENCIL8;
    self->channelCount = 4;

    glTexImage2D(
    GL_TEXTURE_2D, 0, 
    GL_DEPTH24_STENCIL8, w, h, 0, 
    GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
    );
}
int  Sgl$__nvglCreateImageFromTexId(int  texId, int  w, int  h, bool  flipY){
    NVGcontext *vg = (NVGcontext*)SuiCore$Global_getCanvas()->data;

    int imgId = nvglCreateImageFromHandleGL3(
        vg, texId, w, h,
        NVG_IMAGE_REPEATX|NVG_IMAGE_REPEATY |NVG_IMAGE_FLIPY
    );
    return imgId;
}