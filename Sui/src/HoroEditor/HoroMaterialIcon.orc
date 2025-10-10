package HoroEditor

#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"

import * from "../Json/Json.orc"

import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Image.orc"

import * from "../Sgl/Material.orc"
import * from "../Sgl/DrawCtx.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/Fbo.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/Geometry.orc"
import * from "../Sgl/GeometrySphere.orc"
import * from "../Sgl/SglSceneView.orc"
import * from "../Sgl/PixelsReader.orc"

// 材质图标
class HoroMaterialIconCreator{
    Fbo@ fbo = new Fbo()
    Vec2 size = mkVec2(128, 128)

    DrawCtx@ drawCtx = new DrawCtx()
    Scene@ scene 
    PerspectiveCamera@ camera

    String@ materialPath

    void create(const char *materialPath){
        self.materialPath = str(materialPath)

        self.mkScene()

        self.fbo.buildWithColorDepthStencilTexture(
            (int)self.size.width(), (int)self.size.height(),
            true, 
            true, 
            false
        )
        self.draw()

        self.saveAsPng("materialicon.png")
    }
    void showTextureWindow(){
        // 注意。 测试时，fbo已被释放，可能导致tex2d在拖动窗口重画时，无效
        SglSceneView_showTextureWindow(
            self.fbo.tex2d, self.size.x, self.size.y)
    }
    void saveAsPng(const char *path){
        self.fbo.bind()
        RgbaPixelsReader@ r = new RgbaPixelsReader()
        unsigned char* floats = r.readFromColorAttachment(0, 0, 0, self.size.x, self.size.y)
        self.fbo.unbind()

        Image_writeRgbas_toPng(path, 
            self.size.width(), self.size.height(), 
            floats
            )
    }
    void draw(){
        Vec2 fboSize = self.fbo.getSize()
        self.camera.aspect = fboSize.x / fboSize.y
        //绘制fbo
        self.fbo.startDraw(0.0, 0.0, 0.0, 0.0, true, true, true)
        self.drawCtx.frameSize = fboSize
        self.drawCtx.draw(self.scene, self.camera)
        self.fbo.endDraw()
    }
    void mkScene(){
        self.scene = new Scene()
        self.camera = new PerspectiveCamera()


        self.camera.up = mkVec3(0, 1, 0)
        self.camera.fov = 45 / 180.0 * PI
        self.camera.aspect = 1.0
        self.camera.nearPlane = 100.1
        self.camera.farPlane = 5000
        
        // Position camera
        // self.camera.position = mkVec3(100, 300, 500)
        self.camera.position = mkVec3(0, 0, 300)

        self.camera.updateWorldMatrixUptoRoot()
        self.camera.lookAt(0, 0, 0)

        self.scene.appendChild(self.camera)



        Mesh@ mesh = new Mesh()

        new GeometrySphere()~{
            o.build()
            mesh.geometry = o
        }
        new Material()~{
            o.load(self.materialPath.str)
            mesh.material = o
        }


        self.scene.appendChild(mesh)
    }

}


// 材质图标缓存管理
class HoroMaterialIconMgr{
}

//测试程序
void testHoroMaterialIconCreator(){
    HoroMaterialIconCreator@ c = new HoroMaterialIconCreator()
    c.create("../asset/basic.matl.json")
}