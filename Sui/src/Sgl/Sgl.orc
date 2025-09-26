package Sgl

#include <stdio.h>
#include "./UnitOpengl.h"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Core/Vec3.orc"

import * from "./Vbo.orc"
import * from "./Vao.orc"
import * from "./Buffer.orc"
import * from "./Program.orc"
import * from "./Draw.orc"
import * from "./Tex2d.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"

import * from "../Orc/String.orc"
import * from "../Json/Json.orc"
import * from "./Fbo.orc"

//主类
class Sgl{

}
int fboTex;

static class Test{
    void ctor(){
        printf("init Test")
        self.init()
    }
    Program@ program
    Vbo@ vbo
    Vbo@ ibo
    Vbo@ tbo
    Vbo@ cbo
    Tex2d@ tex
    Fbo@ fbo

    void init(){
        Program@ p = new Program()
        self.program = p
        bool ok = p.compileByPathCstr("./asset/a.vs", "./asset/a.fs")
        printf("compile program :%d\n", ok)

        Json@ triJo = Json_parseByPathCstr("./asset/Triangle.json")
        Buffer@ verBuf = mkBufferFloatByJsonArray(triJo.get("position"))
        Buffer@ indicesBuf = mkBufferIntByJsonArray(triJo.get("face"))


        Buffer@ cBuf = mkBufferFloatByJsonArray(triJo.get("color"))
        Buffer@ tBuf = mkBufferFloatByJsonArray(triJo.get("texCoord"))
        printf("ver:%s\n\nindices:%s\ntexCoord:%s\n", 
            verBuf.toFloatString().str,
            indicesBuf.toIntString().str,
            tBuf.toFloatString().str,
        );

        Vbo@ vbo = new Vbo()
        vbo.arrayBuffer(verBuf)
        self.vbo = vbo

        self.cbo = new Vbo()
        self.cbo.arrayBuffer(cBuf)

        self.tbo = new Vbo()
        self.tbo.arrayBuffer(tBuf)

        Vbo@ ibo = new Vbo()
        ibo.elementBuffer(indicesBuf)
        self.ibo = ibo

        {
            Tex2d@ tex = new Tex2d()
            self.tex = tex
            bool ok = tex.loadImageByPathCstr("./asset/SpongeBob.png")
            printf("load tex :%d\n", ok)
        }


        self.fbo = new Fbo()
        self.fbo.bind()
        {//创建附件
            Tex2d@ colorTex = new Tex2d()
            colorTex.initZerosRgba(800, 600)
            self.fbo.attachColorTex2d(colorTex, 0)

            fboTex = colorTex.id;

            Rbo@ rbo = new Rbo()
            rbo.storageAs_DEPTH24_STENCIL8(800, 600)
            self.fbo.attachRenderBuffer_asDepthStencil(rbo)
            printf("FBO status:%d\n", self.fbo.isStatusComplete())
        }

        self.fbo.unbind()
    }

    extern void draw()
}
static class TestDraw{
    void ctor(){
        printf("init Test")
    }
    // Program@ program
    // Vbo@ vbo
    // Vbo@ ibo
    // Vbo@ tbo
    // Vbo@ cbo
    Tex2d@ tex
    Fbo@ fbo

    Draw@ drawObj = new Draw();

    void init(){

        // Program@ p = new Program()
        // self.program = p
        // bool ok = p.compileByPathCstr("../asset/a.vs", "../asset/a.fs")
        // printf("compile program :%d\n", ok)

        // Json@ triJo = Json_parseByPathCstr("./asset/Triangle.json")
        // Buffer@ verBuf = mkBufferFloatByJsonArray(triJo.get("position"))
        // Buffer@ indicesBuf = mkBufferIntByJsonArray(triJo.get("face"))


        // Buffer@ cBuf = mkBufferFloatByJsonArray(triJo.get("color"))
        // Buffer@ tBuf = mkBufferFloatByJsonArray(triJo.get("texCoord"))
        // printf("ver:%s\n\nindices:%s\ntexCoord:%s\n", 
        //     verBuf.toFloatString().str,
        //     indicesBuf.toIntString().str,
        //     tBuf.toFloatString().str,
        // );

        {
            Tex2d@ tex = new Tex2d()
            self.tex = tex
            bool ok = tex.loadImageByPathCstr("./asset/SpongeBob.png")
            printf("load tex :%d\n", ok)
        }


        {
            ObjLoader@ loader = new ObjLoader()
            loader.load("../assimp/test/models/OBJ/spider.obj");
            // loader.load("../assimp/test/models/OBJ/rect.obj");
            self.drawObj.geometry = loader.buildGeometry();
        }
        // self.drawObj.buildGeometryByJsonPathCstr("../asset/TriangleFix.json")
        new Material().{
            o.buildByShaderPathCstr("../asset/a.vs", "../asset/a.fs")
            self.drawObj.material = o
            // o.setUniform4f("uColor", 1.0, 0.0, 0, 1.0)
            o.setUniformTex2d("tex", self.tex)

            // o.mvp.scale(0.5, 2.5, 0.5)
            o.model.scale(0.02, 0.02, 0.02)
            // o.model.setTransalte(10.5, 0.3, 0)
            // o.model.translate(0.5, 0.3, -100)
            // o.model.scale(0.5, 0.5, 1)

            // o.view.translate(0, 0, -80)
            // o.view.identity()
            // o.view.translate(4, 0, 8)
            o.view.lookAtFake(mkVec3(10, 10, 10), mkVec3(0, 0, 0), mkVec3(0, 1, 0))
            // o.view.invertSelf()

            o.projection.perspective(45 / 180.0 * 3.1415926, 1.0, 0.1, 1000)
            // o.projection.ortho(-100, 100, -100, 100, 0.1, 1000)
            // o.projection.ortho(-2, 2, -2, 2, 0.1, 10)
            // o.model.rotateZ(1.0)
        }
        // self.drawObj.material.program = p

        // self.drawObj.buildVaoIfNeed()



        self.fbo = new Fbo()
        self.fbo.buildWithColorDepthStencil(800, 600)
        fboTex = self.fbo.tex2d.id;
        // self.fbo.bind()
        // {//创建附件
        //     Tex2d@ colorTex = new Tex2d()
        //     colorTex.initZerosRgba(800, 600)
        //     self.fbo.attachColorTex2d(colorTex, 0)

        //     fboTex = colorTex.id;

        //     Rbo@ rbo = new Rbo()
        //     rbo.storageAs_DEPTH24_STENCIL8(800, 600)
        //     self.fbo.attachRenderBuffer_asDepthStencil(rbo)
        //     printf("FBO status:%d\n", self.fbo.isStatusComplete())
        // }

        // self.fbo.unbind()

        // new MaterialInsp().{
        //     o.showWindow(self.drawObj.material)
        // }
    }

    extern void draw()
}

void testDrawSgl0(){
    static Test@ t
    if t == null {
        t = new Test()
    }
    t.draw()
}
void testDrawSgl(){
    static TestDraw@ t
    // if t == null {
    //     t = new TestDraw()
    //     t.init()
    // }
    // t.draw()
}