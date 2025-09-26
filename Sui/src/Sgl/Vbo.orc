
package Sgl

// #include <stdint.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "../Sui/Core/Timer.orc"


//Vertex Buffer Object
class Vbo{
    GLuint id

    //GL_STATIC_DRAW，GL_STATIC_READ，GL_STATIC_COPY GL_DYNAMIC_DRAW，GL_DYNAMIC_READ，GL_DYNAMIC_COPY GL_STREAM_DRAW，GL_STREAM_READ，GL_STREAM_COPY
    GLuint usage = GL_STATIC_DRAW;

    int byteSize = 0;
    //一个顶点数据有几个数
    int elementCount = 3;
    bool isFloat = true
    bool isInt = false
    int vaIndex = 0 // vertexAttribIndex


    int vaCount = 1 // 顶点属性细分数量。 像是mat4, 就占用4个顶点属性槽位。

    int divide = 0 // 实例化渲染要用。 如果开实例化渲染，就需要设置为非0值，一般是1，表示一个实例一份数据
    int drawInstanceCount = -1 //-1表示 自动计算。 >=0的值，表示手动指定实例数量

    //是不是索引数据
    bool isIndices = false;

    Buffer@ buf;

    void setInstancedRender(int elementCount, int drawInstanceCount){
        self.elementCount = elementCount
        self.divide = 1 //启用实例渲染
        self.usage = GL_DYNAMIC_DRAW  
        self.drawInstanceCount = drawInstanceCount //绘制实例数量
    }

    int calcInstanceCount(){
        //手动指定实例数量
        if self.drawInstanceCount >= 0 {
            return self.drawInstanceCount
        }
        if self.divide > 0 && !self.isIndices{
            if self.isFloat || self.isInt {
                int totalVertexCount = self.byteSize / (self.elementCount * 4)
                return totalVertexCount 
            }
        }
        return 1
    }
    int calcIndexCount(){
        return self.byteSize / 4;
    }


    void ctor(){
        self.genBuffer()
    }
    void dtor(){
        if self.id {
            GLuint id = self.id
            //确保在主线程释放
            mkTimerTimeout(^void(){
                deleteBuffer(id);
            }, 0)
        }
    }

    extern void bind();

    extern void genBuffer()
    // extern void bind();

    extern void setVertexAttrib()


    void intArrayBuffer(Buffer *buf){
        if buf && buf.data{
            self.buf = buf
            self.isInt = true
            self.isFloat = false
            self.arrayBufferData(buf.size, (float*)buf.data)
        }
    }
    void arrayBuffer(Buffer *buf){
        if buf && buf.data && buf.size > 0{
            self.buf = buf
            self.arrayBufferData(buf.size, (float*)buf.data)
        }
    }
    void elementBuffer(Buffer *buf){
        if buf && buf.data && buf.size > 0{
            self.buf = buf
            self.elementBufferData(buf.size, (int*)buf.data)
        }
    }

    extern void arrayBufferData(int byteSize, float *vertices)

    //元素(索引，面)
    extern void elementBufferData(int byteSize, int *indices)

}

extern void deleteBuffer(GLuint id)