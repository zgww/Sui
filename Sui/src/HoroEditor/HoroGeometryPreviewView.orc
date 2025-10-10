package HoroEditor


#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Time.orc"
import * from "../Orc/Number.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Json/Json.orc"

import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/Fbo.orc"
import * from "../Sgl/Draw.orc"
import * from "../Sgl/Geometry.orc"
import * from "../Sgl/GeometryPlane.orc"
import * from "../Sgl/GeometryBox.orc"
import * from "../Sgl/GeometryCapsule.orc"
import * from "../Sgl/GeometrySphere.orc"
import * from "../Sgl/Mesh.orc"

import * from "../Sgl/Material.orc"
import * from "../Sgl/DrawCtx.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/Buffer.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/PointLight.orc"
import * from "../Sgl/DirLight.orc"
import * from "../Sgl/PixelsReader.orc"
import * from "../Sgl/PerspectiveCamera.orc"

import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/SplitterView.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../Sui/Dialog/Toast.orc"

import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Image.orc"
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
import * from "../Sui/Core/KeyEvent.orc"

import * from "./HoroEditor.orc"
import * from "./UiAct.orc"

import * from "../SuiDesigner/Theme.orc"
import * from "../SuiDesigner/Insp.orc"
import * from "../SuiDesigner/InvalidReact.orc"


class HoroGeometryPreviewView extends ImageView {
    Window@ win;
    Fbo@ fbo 
    DrawCtx@ drawCtx = new DrawCtx()
    Scene@ scene = null
    PerspectiveCamera@ camera = null
    Drag@ drag = new Drag()

    InvalidReact@ _invalid = new InvalidReact().bind(self, "reactWindow")
    
    Mesh@ groundGrid = new Mesh()
    Insp@ inspObj = new Insp()
    Mesh@ mesh = new Mesh()


    void ctor(){
        super.ctor()
        Material@ matl = new Material()
        matl.load(Path_resolveFromExecutionDir("../asset/basic.matl.json").str)
        self.mesh.material = matl

        self.mkBaseScene()

        self.inspObj.cbSetAttr = ^void (Object* obj, OrcMetaField*mf, Object* inspValue){
            Orc_setField(obj, mf, inspValue)
            self.mesh.geometry.version++
            self.mesh.geometry.build()
            self._invalid.invalid()
        }


        self.drag.onDrag = ^void(Drag*d){
            if d.isDragging {
                printf("dragging scene\n")
                self.camera.rotation.y += d.deltaPos.x * 0.001
                self.camera.rotation.x += d.deltaPos.y * 0.001
            }

        }

        {

            GeometryPlane@ geom = new GeometryPlane()
            geom.planeType = 1
            geom.width = 10000
            geom.height = 10000
            geom.widthSegments = 100
            geom.heightSegments = 100
            geom.build()

            self.groundGrid.geometry = geom

            Material@ matl = new Material()
            matl.load(Path_resolveFromExecutionDir("../asset/basic.matl.json").str)
            self.groundGrid.material = matl
        }

    }

    void dtor(){
        printf(".....HoroGeometryPreviewView\n\n");
    }
    void reactWindow(){
        printf("reactWindow========================================\n");
        LayoutLinear *ll = (LayoutLinear*)self.win.rootView
        ll.{
            o.backgroundColor = themeIns().bg1 //0xffffffff
            o.direction.set("row")
            o.alignItems.set("stretch")

            o.placeKid(self)
            self.{
                layoutLinearCell(o, 0).{o.grow = 2}
            }

            mkSplitterView(o, 0).{}

            layoutLinear(o, 0).{
                o.column()
                layoutLinearCell(o, 0)
                
                if self.mesh.geometry{
                    self.inspObj.insp(o, self.mesh.geometry)
                    mkDrawButton(o, 0).{
                        layoutLinearCell(o, 0).{o.grow = 0; o.alignSelf = str("stretch")}

                        o.text = str("print")
                        o.onClick = ^void(MouseEvent*me){
                            printNodeTree(self, 0)
                        }
                    }
                    mkDrawButton(o, 0).{
                        layoutLinearCell(o, 0).{o.grow = 0; o.alignSelf = str("stretch")}

                        o.text = str("保存")
                        o.onClick = ^void(MouseEvent*me){
                            Json@ jo = Json_toJson(self.mesh.geometry)
                            printf("save geometry:%s\n", jo.dump().str)
                            if Path_writeText(self.path.str, jo.dump().str) {
                                Toast_make(str("保存成功:{0}").replaceAll("{0}", self.path.str).str)
                            }
                        }
                    }
                }
                else {
                    mkTextView(o, 0).{
                        o.setText(str("Create Geometry Instance fail"))
                    }
                }

            }
        }
    }
    String@ path

    void showWindow(const char *path){
        self.path = str(path)

        Json@ jo = Json_parseByPathCstr(path)
        printf("loadjson %s :%s\n", path, jo.dump().str)
        PointerArray@ vts = new PointerArray()

        vts.add(GeometryBox)
        vts.add(GeometrySphere)
        vts.add(GeometryPlane)
        vts.add(GeometryCapsule)

        Object* obj = jo.toObjectByVtables(vts)
        if !(obj instanceof Geometry) {
            Toast_make("not geometry.json file")
            return;
        }
        self.mesh.geometry = (Geometry@)obj
        self.mesh.geometry.build()

        self.win = new Window() //先创建窗口，初始化opengl环境
        self.win.{
            o.cbOnEvent = ^void (Event*e){
                self.onWindowEvent(e)
            }

            self.win.setRootView(new LayoutLinear())
            self.reactWindow()

            o.setTitle(str("预览几何体{0}").replaceAll("{0}", path).str)
            o.setSize(800, 600)
            o.moveToCenter()
            o.show()
        }
    }

    void onWindowEvent(Event *e){
        if e instanceof KeyEvent {
            KeyEvent *ke = (KeyEvent*)e
            printf("2窗口收到键盘消息:%s\n", ke.key.str);
            if self.camera && ke.isKeyDown {

                //前进
                if ke.ctrl {
                    if ke.key.equalsIgnoreCase("S"){//保存场景
                        UiAct_savePrefab(self)
                    }
                }
                else if ke.shift {
                    if ke.key.equalsIgnoreCase("A"){
                        printf("左旋转\n");
                        self.camera.rotation.y += 0.01
                    }
                    else if ke.key.equalsIgnoreCase("D"){
                        printf("右旋转\n");
                        self.camera.rotation.y -= 0.01
                    }
                    else if ke.key.equalsIgnoreCase("W"){
                        printf("左旋转\n");
                        self.camera.rotation.x -= 0.01
                    }
                    else if ke.key.equalsIgnoreCase("S"){
                        printf("右旋转\n");
                        self.camera.rotation.x += 0.01
                    }
                }
                else if ke.key.equals("W"){
                    Vec3 dir = self.camera.applyRotationToVec3(mkVec3(0, 0, -1.0))
                    dir.multiplyScalarLocal(10)
                    printf("apply dir:%s\n", dir.toString().str);
                    self.camera.position.addLocal(dir)
                    // self.camera.moveForward()
                }
                else if ke.key.equals("S"){
                    // self.camera.moveBackward()
                    Vec3 dir = self.camera.applyRotationToVec3(mkVec3(0, 0, 1.0))
                    dir.multiplyScalarLocal(10)
                    printf("apply dir:%s\n", dir.toString().str);
                    self.camera.position.addLocal(dir)
                }
                //左转
                else if ke.key.equals("A"){
                    // self.camera.rotateLeft()
                    Vec3 dir = self.camera.applyRotationToVec3(mkVec3(-1, 0, 0.0))
                    dir.multiplyScalarLocal(10)
                    printf("apply dir:%s\n", dir.toString().str);
                    self.camera.position.addLocal(dir)
                }
                else if ke.key.equals("D"){
                    // self.camera.rotateRight()
                    Vec3 dir = self.camera.applyRotationToVec3(mkVec3(1, 0, 0.0))
                    dir.multiplyScalarLocal(10)
                    printf("apply dir:%s\n", dir.toString().str);
                    self.camera.position.addLocal(dir)
                }
                //升降
                else if ke.key.equals("E"){
                    // self.camera.rise()
                    Vec3 dir = self.camera.applyRotationToVec3(mkVec3(0, 1, 0.0))
                    dir.multiplyScalarLocal(10)
                    printf("apply dir:%s\n", dir.toString().str);
                    self.camera.position.addLocal(dir)
                }
                else if ke.key.equals("Q"){
                    // self.camera.fall()
                    Vec3 dir = self.camera.applyRotationToVec3(mkVec3(0, -1, 0.0))
                    dir.multiplyScalarLocal(10)
                    printf("apply dir:%s\n", dir.toString().str);
                    self.camera.position.addLocal(dir)
                }
            }
        }
    }

	void draw_self(Canvas* canvas) {

        {
            bool mkFbo = false
            if self.fbo == null {
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
                self.fbo.buildWithColorDepthStencilTexture(
                    (int)self.frame.width, (int)self.frame.height,
                    true, 
                    true, 
                    false
                )
            }
        }
        if self.fbo {
            Vec2 fboSize = self.fbo.getSize()
            self.camera.aspect = fboSize.x / fboSize.y
            //绘制fbo
            self.fbo.startDraw(0.0, 0.0, 0.0, 1.0, true, true, true)

            self.drawCtx.frameSize = fboSize
            self.drawCtx.draw(self.scene, self.camera)

            // self.mesh.draw(self.drawCtx)

            // self.groundGrid.draw(self.drawCtx)

            self.fbo.endDraw()

            self._img = loadImageByTex2d(self.fbo.tex2d)
        }
        super.draw_self(canvas)

    }

    void onEvent(Event *e){
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e
            if me.button == 1 && me.isMouseDown && me.isBubble() {
                self.drag.onMouseDown(me)
            }
        }
    }
    void mkBaseScene(){
        self.scene = new Scene()
        self.camera = new PerspectiveCamera()
        
        // Initialize camera with default values
        // self.camera.target = mkVec3(0, 0, 0)
        self.camera.up = mkVec3(0, 1, 0)
        self.camera.fov = 45 / 180.0 * PI
        self.camera.aspect = 1.0
        self.camera.nearPlane = 100.1
        self.camera.farPlane = 5000
        
        // Position camera
        // self.camera.position = mkVec3(100, 300, 500)
        self.camera.position = mkVec3(100, 0, 1000)

        self.camera.updateWorldMatrixUptoRoot()
        self.camera.lookAt(0, 0, 0)

        
        // Update camera matrices; 不用调。在draw时会调
        // self.camera.updateProjectionMat()
        // self.camera.updateViewMat()
        
        // Add camera to scene
        self.scene.appendChild(self.camera)
        self.scene.appendChild(self.mesh)

        //添加灯

        // {
        //     DirLight@ l = new DirLight()
        //     l.position.set(0, 10, 0)
        //     self.scene.appendChild(l)
        // }
        
        printf("Base scene and camera initialized\n")
    }
}
HoroGeometryPreviewView@ mkHoroGeometryPreviewView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (HoroGeometryPreviewView@)gocNode(sp, (Node*)parent, HoroGeometryPreviewView)
}
