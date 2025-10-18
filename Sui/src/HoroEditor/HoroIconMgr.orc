package HoroEditor

#include <stdio.h>
#include <string.h>

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
import * from "../Sgl/Obj3d.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/Fbo.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/PointLight.orc"
import * from "../Sgl/Geometry.orc"
import * from "../Sgl/GeometrySphere.orc"
import * from "../Sgl/SglSceneView.orc"
import * from "../Sgl/PixelsReader.orc"
import * from "../Sgl/ModelLoader.orc"

import * from "./HoroGeometryPreviewView.orc"

// 材质图标
class HoroMaterialIconCreator{
    Fbo@ fbo = new Fbo()
    Vec2 size = mkVec2(128, 128)

    DrawCtx@ drawCtx = new DrawCtx()
    Scene@ scene 
    PerspectiveCamera@ camera

    String@ materialPath
    String@ savePath

    void create(String* materialPath){
        self.materialPath = materialPath

        self.mkScene()

        self.fbo.buildWithColorDepthStencilTexture(
            (int)self.size.width(), (int)self.size.height(),
            true, 
            true, 
            false
        )
        self.draw()

        // self.saveAsPng("materialicon.png")
        self.saveAsPng(self.savePath ? self.savePath.str: "materialicon.png")
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

//模型图标
class HoroModelIconCreator{
    Fbo@ fbo = new Fbo()
    Vec2 size = mkVec2(256, 256)

    DrawCtx@ drawCtx = new DrawCtx()
    Scene@ scene 
    PerspectiveCamera@ camera

    String@ modelPath
    String@ savePath

    void create(String *modelPath){
        self.modelPath = modelPath

        self.mkScene()

        self.fbo.buildWithColorDepthStencilTexture(
            (int)self.size.width(), (int)self.size.height(),
            true, 
            true, 
            false
        )
        self.draw()

        // self.saveAsPng("modelicon.png")
        self.saveAsPng(self.savePath ? self.savePath.str: "modelicon.png")
        // self.showTextureWindow()
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
        r.flipY()
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
        self.fbo.startDraw(1.0,10.0, 1.0, 0.0, true, true, true)
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
        self.camera.position = mkVec3(500, 300, 500)

        self.camera.updateWorldMatrixUptoRoot()
        self.camera.lookAt(0, 100, 0)

        self.scene.appendChild(self.camera)

        {
            new PointLight()~{
                o.position.set(500, 500, 500)
                self.scene.appendChild(o)
            }
        }



        AssimpLoader@ l = new AssimpLoader()
        l.load(self.modelPath.str)
        Obj3d@ root = l.buildSglTree()
        root.scale.set(100, 100, 100)
        root.updateWorldTransformAndSubtree()

        self.scene.appendChild(root)


        // Mesh@ mesh = new Mesh()

        // new GeometrySphere()~{
        //     o.build()
        //     mesh.geometry = o
        // }

        // new Material()~{
        //     o.load(Path_resolveFromExecutionDir("../asset/basic.matl.json").str)
        //     mesh.material = o
        // }


        // self.scene.appendChild(mesh)
    }

}


//模型图标
class HoroGeometryJsonIconCreator{
    Fbo@ fbo = new Fbo()
    Vec2 size = mkVec2(256, 256)

    DrawCtx@ drawCtx = new DrawCtx()
    Scene@ scene 
    PerspectiveCamera@ camera

    String@ modelPath
    String@ savePath

    void create(String *modelPath){
        self.modelPath = modelPath

        self.mkScene()

        self.fbo.buildWithColorDepthStencilTexture(
            (int)self.size.width(), (int)self.size.height(),
            true, 
            true, 
            false
        )
        self.draw()

        // self.saveAsPng("modelicon.png")
        self.saveAsPng(self.savePath ? self.savePath.str: "geometryicon.png")
        self.showTextureWindow()
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
        r.flipY()
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
        self.fbo.startDraw(1.0,1.0, 1.0, 0.0, true, true, true)
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
        self.camera.position = mkVec3(500, 300, 500)

        self.camera.updateWorldMatrixUptoRoot()
        self.camera.lookAt(0, 0, 0)

        self.scene.appendChild(self.camera)

        {
            new PointLight()~{
                o.position.set(500, 500, 500)
                self.scene.appendChild(o)
            }
        }


        Mesh@ mesh = new Mesh()
        Geometry@ geom = HoroGeometry_parseGeometryJson(self.modelPath.str)
        mesh.geometry = geom

        new Material()~{
            o.load(Path_resolveFromExecutionDir("../asset/basicWire.matl.json").str)
            mesh.material = o
        }

        self.scene.appendChild(mesh)
    }

}


bool HoroIconMgr_checkPath(String*path){
    return path.endsWith(".obj")
    || path.endsWith(".matl.json")
    || path.endsWith(".geometry.json")
}

// 材质图标缓存管理
class HoroIconMgr{
    Map@ cache = new Map()


    Image* load(String*path){
        //判断需要不需要
        if 
        !(
            
            HoroIconMgr_checkPath(path)
        )
        {
            return null 
        }


        String@ key = String_md5(path.str)
        // 先写成同步的
        // 判断内存cache中有没有
        {
            Image* img = (Image*)self.cache.get(key.str)
            if img != null {
                return img
            }
        }

        // 判断硬盘里有没有,有就加载,然后发布事件
        String@ iconPath = str(".horo/FileIcons/").add(key.str).add(".png")
        if !Path_exists(iconPath.str){
            //确保目录存在
            Path_mkdirsByFilePath(iconPath.str)


            // 创建图标并加载, 然后发布事件
            if  path.endsWithIgnoreCase(".matl.json"){
                HoroMaterialIconCreator@ c = new HoroMaterialIconCreator()
                c.savePath = iconPath
                c.create(path)
            }
            else if path.endsWithIgnoreCase(".obj") {
                HoroModelIconCreator@ c = new HoroModelIconCreator()
                c.savePath = iconPath
                c.create(path)
            }
            else if path.endsWithIgnoreCase(".geometry.json") {
                HoroGeometryJsonIconCreator@ c = new HoroGeometryJsonIconCreator()
                c.savePath = iconPath
                c.create(path)
            }
        }

        Image@ img = loadImage(iconPath.str)
        if img {

        }
        else {
            printf("加载图标失败。path:%s, iconPath:%s\n", path.str, iconPath.str)
        }

        self.cache.put(key.str, img)
        return img
    }
}
HoroIconMgr* insHoroIconMgr(){
    static HoroIconMgr@ ins = null
    if ins == null{
        ins = new HoroIconMgr()
    }
    return ins
}

//测试程序
void testHoroMaterialIconCreator(){
    HoroMaterialIconCreator@ c = new HoroMaterialIconCreator()
    c.create(str("../asset/basic.matl.json"))
}
//测试程序
void testHoroModelIconCreator(){
    HoroModelIconCreator@ c = new HoroModelIconCreator()
    c.create(str("halloween/obj/fence.obj"))

    // char md5bin[100];
    // char out[100];
    // char *path = "halloween/obj/fence.obj";
    // MD5Buffer(path, strlen(path), md5bin);
    // MD5String(md5bin, out);

    printf("md5:%s\n", String_md5("halloween/obj/fence.obj").str);
}
//测试程序
void testHoroGeometryJsonIconCreator(){
    HoroGeometryJsonIconCreator@ c = new HoroGeometryJsonIconCreator()
    c.create(str("Geometry/box2.geometry.json"))

    // char md5bin[100];
    // char out[100];
    // char *path = "halloween/obj/fence.obj";
    // MD5Buffer(path, strlen(path), md5bin);
    // MD5String(md5bin, out);

    printf("md5:%s\n", String_md5("halloween/obj/fence.obj").str);
}

void testHoroIconMgr(){
    HoroIconMgr@ mgr = new HoroIconMgr()
    mgr.load("halloween/obj/fence.obj")
}