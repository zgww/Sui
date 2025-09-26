
#include "./UnitOpengl.h"
#include "./Fbo_orc.h"
#include "Orc/Orc.h"



void  Sgl$Fbo$gen(Sgl$Fbo *  self){
    glGenFramebuffers(1, &self->id);
}

void  Sgl$deleteFrameBuffer(GLuint id){
    glDeleteFramebuffers(1, &id);
}

void  Sgl$Fbo$bind(Sgl$Fbo *  self){
    glBindFramebuffer(GL_FRAMEBUFFER, self->id);
}
void  Sgl$Fbo$unbind(Sgl$Fbo *  self){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int Sgl$Fbo$checkStatus(Sgl$Fbo *  self){
    auto v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    return (int)v;
}
const char*  Sgl$Fbo$statusDesc(Sgl$Fbo *  self){
    auto v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (v == GL_FRAMEBUFFER_COMPLETE){
        return "complete";
    }
    if (v == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT){
        return "incomplete_attachment";
    }
    if (v == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT){
        return "incomplete_missing_attachment";
    }
    if (v == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER){
        return "incomplete_draw_buffer";
    }
    if (v == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER){
        return "incomplete_read_buffer";
    }
    if (v == GL_FRAMEBUFFER_UNSUPPORTED){
        return "unsupported";
    }
    return "unknown";
}
bool  Sgl$Fbo$isStatusComplete(Sgl$Fbo *  self){
    auto v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    bool ok = v == GL_FRAMEBUFFER_COMPLETE;
    return ok;
}
void  Sgl$Fbo$_attachColorTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d, int  colorAttachmentIndex)
{
// target：帧缓冲的目标（绘制、读取或者两者皆有）
// attachment：我们想要附加的附件类型。当前我们正在附加一个颜色附件。注意最后的0意味着我们可以附加多个颜色附件。我们将在之后的教程中提到。
// textarget：你希望附加的纹理类型
// texture：要附加的纹理本身
// level：多级渐远纹理的级别。我们将它保留为0。
    self->bind(self);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachmentIndex, GL_TEXTURE_2D, 
        tex2d->id,
        0);
    bool ok = self->isStatusComplete(self);
}
void  Sgl$Fbo$_attachDepthStencilTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d){

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 
        tex2d->id,
        0);
}
void  Sgl$Fbo$_attachDepthTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d){

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
        tex2d->id,
        0);
}
void  Sgl$Fbo$_attachStencilTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d){
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 
        tex2d->id,
        0);
}
void  Sgl$deleteRenderBuffer(GLuint id){
    glDeleteRenderbuffers(1, &id);
}

void  Sgl$Rbo$gen(Sgl$Rbo *  self){
    glGenRenderbuffers(1, &self->id);
}
void  Sgl$Rbo$bind(Sgl$Rbo *  self){
    glBindRenderbuffer(GL_RENDERBUFFER, self->id);
}
void  Sgl$Rbo$unbind(Sgl$Rbo *  self){
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
void  Sgl$Rbo$storageAs_DEPTH24_STENCIL8(Sgl$Rbo *  self, int w , int h){
    self->bind(self);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
}

void  Sgl$Fbo$_attachRenderBuffer_asDepthStencil(Sgl$Fbo *  self, Sgl$Rbo *  rbo){
    self->bind(self);
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, 
        GL_DEPTH_STENCIL_ATTACHMENT, 
        GL_RENDERBUFFER, rbo->id);
}

void  Sgl$Fbo$startDraw(Sgl$Fbo *  self,
    float r, float g, float b, float a, bool clearColor, bool clearDepth, bool clearStencil
){
    self->bind(self);
    SuiCore$Vec2 s = self->getSize(self);
    int w = s.x;
    int h = s.y;
    glViewport(0, 0, w, h);

    glClearColor(r, g, b, a);

    unsigned int bit = 0;
    if (clearColor) {
        bit |= GL_COLOR_BUFFER_BIT;
    }
    if (clearDepth) {
        bit |= GL_DEPTH_BUFFER_BIT;
    }
    if (clearStencil) {
        bit |= GL_STENCIL_BUFFER_BIT;
    }
    glDisable(GL_SCISSOR_TEST);

    // glClearDepth(0.5);

    glClear(bit);
}
void  Sgl$Fbo$endDraw(Sgl$Fbo *  self){
    self->unbind(self);


    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    // glDisableVertexAttribArray(2);
}
void  Sgl$Fbo$setGlDrawBufferNone(Sgl$Fbo *  self){
    glDrawBuffer(GL_NONE);
}
void  Sgl$Fbo$setGlReadBufferNone(Sgl$Fbo *  self){
    glReadBuffer(GL_NONE);
}
void  Sgl$Fbo$setGlDrawBufferDefault(Sgl$Fbo *  self){
    glDrawBuffer(GL_BACK);
}
void  Sgl$Fbo$setGlReadBufferDefault(Sgl$Fbo *  self){
    glReadBuffer(GL_BACK);
}