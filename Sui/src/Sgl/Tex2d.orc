

package Sgl

#include <stdio.h>

#include "./UnitOpengl.h"
#include "../nanovg/stb_image.h"

import * from "../Sui/Core/Global.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./Vao.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Color.orc"


class Tex2d {
    GLuint id;

    GLuint wrapS = GL_REPEAT;
    GLuint wrapT = GL_REPEAT;
    GLuint minFilter = GL_LINEAR//;GL_NEAREST;//GL_TEXTURE_MIN_FILTER;
    GLuint magFilter = GL_LINEAR//GL_TEXTURE_MIN_FILTER;

    int width = 0;
    int height = 0;
    int format = 4;//GL_RGB|GL_RGBA|GL_RED
    int channelCount = 4;

    //路径。 可能有，也可能没有
    //有的话，才能序列化.
    String@ path = null

    void setWrapClampToEdge(){
        self.wrapS = GL_CLAMP_TO_EDGE;
        self.wrapT = GL_CLAMP_TO_EDGE;
    }
    void setWrapClampToBorder(int color){
        self.wrapS = GL_CLAMP_TO_BORDER;
        self.wrapT = GL_CLAMP_TO_BORDER;

        self.bind()
        Rgbaf c = mkRgbafByInt(color)
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (float*)&c)
    }

    void ctor(){
        self.gen()
        self.updateParameters()
    }
    void dtor(){
        if self.id {
            GLuint id = self.id
            //确保在主线程释放
            mkTimerTimeout(^void(){
                deleteTexture(id);
            }, 0)
        }
    }
    Vec2 Size(){
        return mkVec2(self.width, self.height)
    }

    extern void updateParameters()

    extern void gen()
    extern void bind()
    extern void unbind()
    extern void active(int offset)
    extern void generateMipmap()

    //分配显存，，并填充像素
    extern void image2dRgba(unsigned char* buf, int w, int h)
    //分配显存，，并填充像素
    extern void image2dRgb(unsigned char* buf, int w, int h)

    //分配显存，，并填充像素.只有8位红色
    extern void image2dRed8(unsigned char* buf, int w, int h)

    //分配显存,但没有填充
    void initZerosRgb(int w, int h){
        self.bind()
        self.updateParameters()
        self.image2dRgb(null, w, h)
    }
    void initZerosRed8(int w, int h){
        self.bind()
        self.updateParameters()
        self.image2dRed8(null, w, h)
    }
    //分配显存,但没有填充
    void initZerosRgba(int w, int h){
        self.bind()
        self.updateParameters()
        self.image2dRgba(null, w, h)
    }
    //初始化，作为fbo的深度附件
    extern void initForDepthAttachment(int w, int h)
    //初始化，作为fbo的stencil附件
    extern void initForStencilAttachment(int w, int h)
    extern void initForDepth32fStencil8Attachment(int w, int h)
    extern void initForDepth24Stencil8Attachment(int w, int h)

    bool loadImageByPathCstr(const char *path){
        int width = 0
        int height = 0
        int channel = 0;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path, &width, &height, &channel, 0);
        if data {
            printf("load image. data:%p,  width:%d, height:%d, ch:%d\n", data, width, height, channel);

            if channel == 4 {
                // self.active(0)
                self.bind()
                self.updateParameters()
                self.image2dRgba(data, width, height)
                self.unbind()
            }
            else if channel == 3 {
                // self.active(0)
                self.bind()
                self.updateParameters()
                self.image2dRgb(data, width, height)
                self.unbind()
            }
            stbi_image_free(data);
            self.path = str(path)
            return true;
        }
        printf("\n\t\t加载纹理失败。 path:%s\n\n", path);
        return false;
    }

}

Tex2d@ mkTex2dByPathCstr(const char *path){
    Tex2d@ r = new Tex2d()
    r.loadImageByPathCstr(path)
    return r
}

Image@ loadImageByTex2d(Tex2d *tex){
    static Map@ imageMap = null
    if !imageMap {
        imageMap = new Map()
    }
    String@ key = str("").addi(tex.id)
    Image@ ret = (Image@)imageMap.get(key.str)
    if ret {
        return ret;
    }

    int imgId = __nvglCreateImageFromTexId(tex.id, tex.width, tex.height, true)

    ret = new Image()
    ret._img = imgId
    imageMap.put(key.str, ret)
    return ret
}
extern int __nvglCreateImageFromTexId(
    int texId, int w, int h, bool flipY)

extern void deleteTexture(GLuint id)



