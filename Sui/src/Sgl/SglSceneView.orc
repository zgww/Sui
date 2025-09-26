package Sgl


#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/Orc.h"

import * from "./Mat.orc"

import * from "./Program.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Math.orc"
import * from "../Json/Json.orc"
import * from "../Sui/Core/Focus.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/View/Switch.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/Panel.orc"
import * from "../Sui/View/ColorPicker.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Layout/LayoutLinear.orc"

import * from "./Tex2d.orc"
import * from "./Fbo.orc"
import * from "./Draw.orc"
import * from "./Geometry.orc"

import * from "./Material.orc"
import * from "./DrawCtx.orc"
import * from "./Scene.orc"
import * from "./Buffer.orc"
import * from "./PointLight.orc"
import * from "./DirLight.orc"
import * from "./PixelsReader.orc"
import * from "./PerspectiveCamera.orc"


class SglSceneView extends ImageView {
    Fbo@ fbo 
    Material@ matl
    Draw@ drawObj
    DrawCtx@ drawCtx = new DrawCtx()
    Scene@ scene = null
    PerspectiveCamera@ camera = null

    void buildDrawObj(){
        // ObjLoader@ loader = new ObjLoader()
        // loader.load("../assimp/test/models/OBJ/spider.obj");

        self.drawObj = new Draw()
        self.drawObj.material = self.matl


        // self.drawObj.buildGeometryByJsonPathCstr("../asset/TriangleFix.json")

        // self.drawObj.geometry = loader.buildGeometry();

        // Material* o = self.matl
        // o.model.scale(0.02, 0.02, 0.02)
        // o.view.lookAt(mkVec3(0, -1000, 2000), mkVec3(0, 0, 0), mkVec3(0, 0, 1)) // xy为地面
        // o.view.lookAt(mkVec3(0, 2000, 1000), mkVec3(0, 0, 0), mkVec3(0, 1, 0)) // xz为地面
        // o.projection.perspective(45 / 180.0 * 3.1415926, 1.0, 0.1, 10000)

        // printf("mk draw succ\n");

        // self.applyModel()

        // self.fbo = new Fbo()
        // self.fbo.buildWithColorDepthStencil(200, 200)
    }

	void draw_self(Canvas* canvas) {

        {
            bool mkFbo = false
            if self.drawObj && self.fbo == null {
                mkFbo = true
            }
            else if self.fbo {
                Vec2 size = self.fbo.getSize()
                if size.x != (int)self.frame.width || size.y != (int)self.frame.height{
                    mkFbo = true
                }
            }
            if mkFbo {
                printf("重建fbo. size:%f,%f\n", self.frame.width, self.frame.height)
                self.fbo = new Fbo()



                // self.fbo.buildWithColorDepthStencil((int)self.frame.width, (int)self.frame.height)
                // self.fbo.buildWithColorDepth32fStencil8Texture(
                //     (int)self.frame.width, (int)self.frame.height,
                //     true, true)
                // self.fbo.buildWithColorDepth24Stencil8Texture(
                //     (int)self.frame.width, (int)self.frame.height,
                //     true, true)
                // self.fbo.setGlDrawBufferNone()
                // self.fbo.setGlReadBufferNone()
                self.fbo.buildWithColorDepthStencilTexture(
                    (int)self.frame.width, (int)self.frame.height,
                    true, 
                    true, 
                    false
                )
                //重建depthTex
                // self.depthTex = new Tex2d()
                // self.depthTex.initZerosRed8(
                //     (int)self.frame.width, (int)self.frame.height,
                // )
                // self.depthTex.initZerosRgba(
                //     (int)self.frame.width, (int)self.frame.height,
                // )

                // self.depthPreview.init(
                //     (int)self.frame.width, (int)self.frame.height,
                // )
                // self.depthPreview.showTextureWindow()

                // SglSceneView_showTextureWindow(self.fbo.tex2d, 400, 400)
                // SglSceneView_showTextureWindow(self.depthTex, 400, 400)
                // SceneView_showDepthTextureWindow(self.depthTex, 400, 400)
                // self.depthPreview.init(
                //     (int)self.frame.width, (int)self.frame.height,
                // )
            }
        }
        if self.fbo {
            Vec2 fboSize = self.fbo.getSize()
            self.camera.aspect = fboSize.x / fboSize.y
            //绘制fbo
            self.fbo.startDraw(0.0, 0.0, 0.0, 1.0, true, true, true)

            // self.drawObj.draw()

            // self.fbo.setGlDrawBufferNone()
            // self.fbo.setGlReadBufferNone()

            self.drawCtx.frameSize = fboSize
            self.drawCtx.draw(self.scene, self.camera)

            // self.fbo.setGlDrawBufferDefault()
            // self.fbo.setGlReadBufferDefault()

            // DepthFloatPixlesReader *dr = self.depthPixelsReader
            // int w = self.fbo.tex2d.width
            // int h = self.fbo.tex2d.height
            // float *floats = dr.read(0, 0, w, h) 

            // Image_writeFloatsAsGrey_toPng("depth.png", w, h, floats)

            // printf("depths:%s\n", dr.buffer.toFloatString().str)
            // int cnt = dr.buffer.floatSize()
            // for int i = 0; i < cnt; i++{
            //     float v = floats[i]
            //     if v <= 0.90{
            //         printf("v:%f\n", v)
            //     }
            // }
            // printf("cnt:%d,%d, %d %d\n", 
            //     self.fbo.tex2d.width, self.fbo.tex2d.height,
            //     self.fbo.tex2d.width * self.fbo.tex2d.height,
            //     )

            // exit(0)
            // self.depthPreview.readPixels(
            //     self.fbo.tex2d.width,
            //     self.fbo.tex2d.height,
            // )

            self.fbo.endDraw()

           
            // Image_convertFloatsToGreyBuffer(
            //     self.depthRedBuffer,
            //     w, h, floats
            // )
            // Image_convertFloatsToRgbaBuffer(
            //     self.depthRedBuffer,
            //     w, h, floats
            // )
            // int cnt = w * h
            // unsigned char *data = calloc(cnt * 4, 1)

            // for int r = 0; r < h; r++{
            //     for int c = 0; c < w; c++{
            //         int i = (r * w + c)*4
            //         data[i] = 0
            //         // self.depthRedBuffer.data[i] = 0
            //         if c < 100{
            //             // self.depthRedBuffer.data[i] = 255
            //             data[i] = 255
            //             data[i+3] = 255
            //         }
            //     }
            // }

            // static int i = 0
            // i++
            // char tmp[100];
            // sprintf(tmp, "depth%d.png", i)
            // Image_writeFloatsAsGrey_toPng(tmp, w, h, floats)
            // self.depthTex.image2dRed8(self.depthRedBuffer.data, w, h)
            // self.depthTex.image2dRed8(data, w, h)
            // self.depthTex.image2dRgba(data, w, h)

            // self.depthTex.image2dRgba(self.depthRedBuffer.data, w, h)

            // free(data)


            //do draw
            self._img = loadImageByTex2d(self.fbo.tex2d)

        }
        super.draw_self(canvas)

        //绘制opengl
    }
    // Tex2d @ depthTex
    // DepthFloatPixlesReader@ depthPixelsReader = new DepthFloatPixlesReader()
    // Buffer@ depthRedBuffer = new Buffer()

    DepthTexturePreview@ depthPreview = new DepthTexturePreview()

    void onEvent(Event *e){
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e
            if me.button == 1 && me.isMouseDown && me.isBubble() {
                // self.drag.onDrag = ^void(Drag *d){
                //     if d.isDragging{
                //         // self.drawObj.material.model.translate(d.deltaPos.x, d.deltaPos.y, 0)
                //         if d.mouseDownButton == 1 {//rotate
                //             self.rotateY += toRad(d.deltaPos.x)
                //             self.applyModel()
                //         }
                //         if d.mouseDownButton == 3 {//scale
                //             self.scale = clampFloat(self.scale + d.deltaPos.x / 10000.0, 0.01, 2.0)
                //             self.applyModel()
                //         }
                //         // self.drawObj.material.model.scale(d.deltaPos.x, 0, 0)
                //     }
                // }
                self.drag.onMouseDown(me)
            }
        }
    }
    float rotateY = 0
    float scale = 0.02
    void applyModel(){
        if self.drawObj && self.drawObj.material {
            &self.drawObj.material.model.{
                o.identity()
                o.rotateY(self.rotateY)
                o.scale(self.scale, self.scale, self.scale)
            }
        }
    }
    
    void mkBaseScene(){
        self.scene = new Scene()
        self.camera = new PerspectiveCamera()
        
        // Initialize camera with default values
        self.camera.target = mkVec3(0, 0, 0)
        self.camera.up = mkVec3(0, 1, 0)
        self.camera.fov = 45 / 180.0 * PI
        self.camera.aspect = 1.0
        self.camera.nearPlane = 100.1
        self.camera.farPlane = 5000
        
        // Position camera
        // self.camera.position = mkVec3(100, 300, 500)
        self.camera.position = mkVec3(0, -100, 1000)

        
        // Update camera matrices; 不用调。在draw时会调
        // self.camera.updateProjectionMat()
        // self.camera.updateViewMat()
        
        // Add camera to scene
        self.scene.appendChild(self.camera)

        //添加灯
        {
            DirLight@ l = new DirLight()
            l.position.set(0, 10, 0)
            self.scene.appendChild(l)
        }
        
        printf("Base scene and camera initialized\n")
    }
    
    Drag@ drag = new Drag()
}
SglSceneView@ mkSglSceneView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (SglSceneView@)gocNode(sp, (Node*)parent, SglSceneView)
}

void SglSceneView_showTextureWindow(Tex2d *tex, int w, int h){
    new Window().{
        Window* win = o
        
        ImageView@ iv = new ImageView()
        iv.{
            win.rootView = iv
            iv._img = loadImageByTex2d(tex)
            // iv.setSrc(str("../asset/SpongeBob.png"))
        }


        o.setTitle("纹理预览")
        o.setSize(w, h)
        o.moveToCenter()
        o.show()
    }
}
 
class DepthTexturePreview{
    Tex2d @ depthTex// = new Tex2d()
    Buffer@ depthRedBuffer = new Buffer()
    DepthFloatPixlesReader@ depthPixelsReader = new DepthFloatPixlesReader()

    void init_readPixels(int w, int h){
        self.init(w, h)
        self.readPixels()
    }

    void init(int width, int height){
        self.depthTex = new Tex2d()
        self.depthTex.initZerosRgba(
            width, height,
        )
    }
    void showTextureWindow(){
        SglSceneView_showTextureWindow(self.depthTex, 400, 400)
    }
    void readPixels(){
        Vec2 size = self.depthTex.Size()
        // if !size.equals(mkVec2(width, height)){//宽高不一致，
            // self.depthTex = new Tex2d()
            // self.depthTex.initZerosRgba( width, height)
        // }


        DepthFloatPixlesReader *dr = self.depthPixelsReader
        int w = self.depthTex.width
        int h = self.depthTex.height
        float *floats = dr.read(0, 0, w, h) 

        Image_convertFloatsToRgbaBuffer(
            self.depthRedBuffer,
            w, h, floats
        )
        self.depthTex.image2dRgba(self.depthRedBuffer.data, w, h)
    }
}