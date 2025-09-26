package Sgl


#include "./UnitOpengl.h"
#include <stdio.h>

import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "./Tex2d.orc"

// Frame Buffer Object
// 用来做离屏渲染。渲染到纹理的

// fbo可以管理离屏渲染所需要的 目标纹理、、深度缓冲区、、模板缓冲区等
// 用法:

// self.fbo = new Fbo()
// self.fbo.bind()
// {//创建附件
//     颜色附件
//     Tex2d@ colorTex = new Tex2d()
//     colorTex.initZerosRgba(800, 600)
//     self.fbo.attachColorTex2d(colorTex, 0)

//     fboTex = colorTex.id;

//     深度和模板附件
//     Rbo@ rbo = new Rbo()
//     rbo.storageAs_DEPTH24_STENCIL8(800, 600)
//     self.fbo.attachRenderBuffer_asDepthStencil(rbo)
//     printf("FBO status:%d\n", self.fbo.isStatusComplete())
// }
// self.fbo.unbind()

class Fbo{
    GLuint id;
    Tex2d@ tex2d;
    Tex2d@ depthTex2d;
    Tex2d@ stencilTex2d;
    Rbo@ depthStencilRbo;

    void ctor(){
        self.gen()
    }
    void dtor(){
        if self.id {
            GLuint id = self.id
            //确保在主线程释放
            mkTimerTimeout(^void(){
                deleteFrameBuffer(id);
            }, 0)
        }
    }
    Vec2 getSize(){
        if self.tex2d{
            return mkVec2(self.tex2d.width, self.tex2d.height)
        }
        if self.depthTex2d{
            return mkVec2(self.depthTex2d.width, self.depthTex2d.height)
        }
        return mkVec2(0, 0)
    }
    extern void gen();
    extern void bind()
    extern void unbind()
    // fbo是否完整 
    // 附加至少一个缓冲（颜色、深度或模板缓冲）。
    // 至少有一个颜色附件(Attachment)。
    // 所有的附件都必须是完整的（保留了内存）。
    // 每个缓冲都应该有相同的样本数(sample)。
    extern bool isStatusComplete()
    extern int checkStatus()
    extern const char * statusDesc()

    extern void startDraw(float r, float g, float b, float a, bool clearColor, bool clearDepth, bool clearStencil)
    extern void endDraw()

    extern void setGlDrawBufferNone()
    extern void setGlReadBufferNone()

    extern void setGlDrawBufferDefault()
    extern void setGlReadBufferDefault()
    

    void attachColorTex2d(Tex2d* tex2d, int colorAttachmentIndex){
        self.tex2d = tex2d;
        self._attachColorTex2d(tex2d, colorAttachmentIndex)
    }
    void attachDepthTex2d(Tex2d* tex2d){
        self.depthTex2d = tex2d
        self._attachDepthTex2d(tex2d)

    }
    void attachStencilTex2d(Tex2d* tex2d){
        self.stencilTex2d = tex2d
        self._attachStencilTex2d(tex2d)
    }

    void attachRenderBuffer_asDepthStencil(Rbo* rbo){
        self.depthStencilRbo = rbo
        self._attachRenderBuffer_asDepthStencil(rbo)
    }

    //附加目标纹理
    //[colorAttachmentIndex] 是相对于GL_COLOR_ATTACHMENT0的偏移
    extern void _attachColorTex2d(Tex2d* tex2d, int colorAttachmentIndex)
    extern void _attachDepthTex2d(Tex2d* tex2d)
    extern void _attachDepthStencilTex2d(Tex2d* tex2d)
    extern void _attachStencilTex2d(Tex2d* tex2d)
    extern void _attachRenderBuffer_asDepthStencil(Rbo* rbo)

    void buildWithColorDepth32fStencil8Texture(int w, int h, bool colorTex, bool depthStencilTex){
        self.bind()
        if colorTex {
            Tex2d@ c = new Tex2d()
            c.initZerosRgba(w, h)
            self.attachColorTex2d(c, 0)
        }
        if depthStencilTex {
            Tex2d@ c = new Tex2d()
            c.initForDepth32fStencil8Attachment(w, h)
            self._attachDepthStencilTex2d(c)
            self.depthTex2d = c
        }
        printf("FBO status:%d. %s %x\n", self.isStatusComplete(), self.statusDesc(), self.checkStatus())
        self.unbind()
    }
    void buildWithColorDepth24Stencil8Texture(int w, int h, bool colorTex, bool depthStencilTex){
        self.bind()
        if colorTex {
            Tex2d@ c = new Tex2d()
            c.initZerosRgba(w, h)
            self.attachColorTex2d(c, 0)
        }
        if depthStencilTex {
            Tex2d@ c = new Tex2d()
            c.initForDepth24Stencil8Attachment(w, h)
            self._attachDepthStencilTex2d(c)
            self.depthTex2d = c
        }
        printf("FBO status:%d. %s %x\n", self.isStatusComplete(), self.statusDesc(), self.checkStatus())
        self.unbind()
    }
    //注意没办法同时挂载depth/stencil. 如果想同时挂载，请用Depth24Stencil8
    void buildWithColorDepthStencilTexture(int w, int h, bool colorTex, bool depthTex, bool stencilTex){
        self.bind()
        if colorTex {
            Tex2d@ c = new Tex2d()
            c.initZerosRgba(w, h)
            self.attachColorTex2d(c, 0)
        }
        if depthTex {
            Tex2d@ c = new Tex2d()
            c.setWrapClampToEdge()
            c.updateParameters()
            c.initForDepthAttachment(w, h)
            self.attachDepthTex2d(c)
        }
        if stencilTex {
            Tex2d@ c = new Tex2d()
            c.initForStencilAttachment(w, h)
            self.attachStencilTex2d(c)
            self.stencilTex2d = c
        }
        printf("FBO status:%d. %s %x\n", self.isStatusComplete(), self.statusDesc(), self.checkStatus())
        self.unbind()
    }

    void buildWithColorDepthStencil(int w, int h){
        self.bind()

        Tex2d@ colorTex = new Tex2d()
        colorTex.initZerosRgba(w, h)
        self.attachColorTex2d(colorTex, 0)

        Rbo@ rbo = new Rbo()
        rbo.storageAs_DEPTH24_STENCIL8(w, h)
        self.attachRenderBuffer_asDepthStencil(rbo)
        printf("FBO status:%d, %s\n", self.isStatusComplete(), self.statusDesc())

        self.unbind()

    }
}



extern void deleteFrameBuffer(GLuint id);

// Render buffer object. 专用于fbo.的附件缓冲区，特别：能被着色器
class Rbo {
    GLuint id;

    void ctor(){
        self.gen()
    }
    void dtor(){
        if self.id {
            GLuint id = self.id
            //确保在主线程释放
            mkTimerTimeout(^void(){
                deleteRenderBuffer(id);
            }, 0)
        }
    }
    extern void gen();
    extern void bind();
    extern void unbind();
    extern void storageAs_DEPTH24_STENCIL8(int w, int h)
}
extern void deleteRenderBuffer(GLuint id);