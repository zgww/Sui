package Sgl

// #include <stdint.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "../Sui/Core/Timer.orc"


class Vao {
    //此vao为此材质和geometry服务
    Material@ material
    Geometry@ geometry

    GLuint id = 0;

    // void ctor(){
        // self.gen()
    // }

    int geometryVersion = 0

    void regen(){
        if self.id {
            deleteVertexArray(self.id);
        }
        self.gen()
    }
    void dtor(){
        if self.id {
            GLuint id = self.id
            //确保在主线程释放
            mkTimerTimeout(^void(){
                deleteVertexArray(id);
            }, 0)
        }
    }

    bool isNeedBuild(
        Geometry* geometry,
        Material *material
    ){
        return material && geometry 
        && ( //关联不一样，也需要重建
            self.material != material
            || self.geometry != geometry
            || geometry.version != self.geometryVersion //版本有变化，说明需要更新
        )
    }
    bool build(
        Geometry* geometry,
        Material *material
    ){
        if self.isNeedBuild(geometry, material) {
            self.regen()//重新生成id

            self.material = material
            self.geometry = geometry
            self.material.program.use()

            self.bind()
            bool ok = geometry.bindVertexAttribs(material)

            if geometry.ibo {
                geometry.ibo.bind()
            }

            self.geometryVersion = geometry.version

            self.unbind()

            return ok
        }
        return true
    }

    extern void gen()

    extern void bind()
    extern void unbind()

    void draw(
        Geometry* geometry,
        Material *matl
    ){
        if geometry.ibo == null{
            return
        }
        self.build(geometry, matl)

        self.material.program.use()

        self.bind()

        self.material.prepareDraw()
        self.material.updateUniforms()

        // self.doDraw()


        //实例化渲染
        if geometry.instanceVbo {
            self.drawInstanced(geometry, matl)
            // glDrawElementsInstanced(
            //     GL_TRIANGLES, 
            //     indexCount, 
            //     GL_UNSIGNED_INT, 
            //     0,
            //     instanceCount);
        }
        else {
            int indexCount = geometry.ibo.calcIndexCount()
            glDrawElements(GL_TRIANGLES, 
                indexCount, GL_UNSIGNED_INT, 0);
        }

        self.material.endDraw()

        self.unbind()
    }
    extern void drawInstanced(
        Geometry* geometry,
        Material *matl
    )
    // extern void doDraw()
}

extern void deleteVertexArray(GLuint id)