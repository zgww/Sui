package SuiDesigner3d

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Time.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Json/Json.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Mouse.orc"
import * from "../Sui/Core/KeyEvent.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Dialog/FileDialog.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/View/DockLayout.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sgl/Buffer.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "./ChessBgViewCallback.orc"
import * from "./Theme.orc"
import * from "./W3e.orc"
import * from "./InvalidReact.orc"
import * from "./MenuBarCtrl.orc"
import * from "../Sgl/Material.orc"
import * from "../Sgl/Draw.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/Geometry.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/SkinMesh.orc"
import * from "../Sgl/Particle.orc"
import * from "../Sgl/GeometryHeightMap.orc"
import * from "../Sgl/GeometryBox.orc"
import * from "../Sgl/GeometryPlane.orc"
import * from "../Sgl/GeometryRect.orc"
import * from "../Sgl/GeometrySphere.orc"
import * from "../Sgl/GeometryCircle.orc"
import * from "../Sgl/GeometryRing.orc"
import * from "../Sgl/GeometryCylinder.orc"
import * from "../Sgl/GeometryCone.orc"
import * from "../Sgl/GeometryArrow.orc"
import * from "../Sgl/SglSceneView.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/PointLight.orc"
import * from "../Sgl/DrawCtx.orc"
import * from "../Sgl/Fbo.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "../Sgl/Skybox.orc"
import * from "./MdxReader.orc"
import * from "./SglSceneHierView.orc"
import * from "./SglEditCtx.orc"
import * from "./Asset/AssetDirView.orc"
import * from "./Asset/AssetDirTreeView.orc"
import * from "./Project.orc"
import * from "./SglInspectorView.orc"
import * from "./SglInspView.orc"



static DockLayout@ dockLayoutIns = null

class W3eEditor{
    SglEditCtx@ editCtx = new SglEditCtx()
    Window@ win

    LayoutAlignPositionCell@ imgCell
    LayoutAlignPositionCell@ previewCell

    InvalidReact@ invalidReact  = mkInvalidReact(self)

    String@ path = str("../build/././a.tilemap.json")

    Drag@ drag = new Drag()

    void printSceneTree(){
        // printNodeTree(self.sceneImageView, 0)
    }


    void ctor(){
        // self.curTilePosArr = mkVec2(-1, -1)
        self.drag.onDrag = ^ void (Drag *d){
            if d.isDragging {
                printf("isDragging tileset\n")

            }
        }

        String@ projectDirPath = Path_dirname(Path_getExecutionPath().str).add("/asset/styles")
        printf("projectDirPath:%s\n", projectDirPath.str)
        Project_ins().init(projectDirPath.str)
       
    }
    

    ChessBgViewCallback@ chessBg = new ChessBgViewCallback()


    ViewBase* reactPreview(Node* o, DockItem *item){
        layoutAlign(o, (long long)item).{
            o.useMaxConstraint = false
            // o.direction.set("column")
            // o.alignItems.set("start")
            o.needClip = true
            o.cb  = self.chessBg 
            o.cbOnEvent = ^void(Event*e){
                if e instanceof MouseEvent {
                    MouseEvent *me = (MouseEvent*)e;
                }
            }

            layoutLinearCell(o, 0)

            return o
        }
    }

    void showDialog_renameLayer(){
                                            // Toast_make(anim.name.str)
        MessageDialog_prompt("hi", "重命名", ^void (String@ newValue) {
            // layer.name = newValue
            self.invalidReact.invalid()
        })
    }
    MaterialPreviewView@ glPreviewView
    Material@ matl = null

    ViewBase* reactScene(Node* o, DockItem *item){

        if 0 {
            mkMaterialPreviewView(o, (long long)item).{
                o.backgroundColor = 0x00222222
                o.setImageMode(Cover)
                if o.matl != self.matl {
                    o.matl = self.matl
                    o.buildDrawObj()
                }
                self.glPreviewView = o
                // o.width = 500
                // o.height = 500

                layoutLinearCell(o, 0)

                return o
            }
        }


        layoutAlign(o, (long long)item).{
            o.useMaxConstraint = false
            // o.direction.set("column")
            // o.alignItems.set("start")
            o.needClip = true
            o.cbOnEvent = ^void(Event*e){
                if e instanceof MouseEvent {
                    MouseEvent *me = (MouseEvent*)e;
                }
            }

            layoutLinearCell(o, 0)
                if 0 {
                    mkMaterialPreviewView(o, 0).{
                        // o.backgroundColor = 0xf1222222
                        o.backgroundColor = 0x00ffffff
                        o.setImageMode(Cover)
                        if o.matl != self.matl {
                            o.matl = self.matl
                            o.buildDrawObj()
                            o.drawObj.geometry = self.geom

                            // for int i = 0; i < self.w3e.groundTexs.size(); i++{
                            //     Tex2d* tex = self.w3e.groundTexs.get(i)
                            //     o.drawObj.material.setUniformTex2d(str("tex").addi(i).str, tex)
                            // }
                            // self.w3e.setUniformTexs(o.drawObj.material)


                            Tex2d@ tex = new Tex2d()
                            tex.loadImageByPathCstr("../asset/terrain.png")
                            o.drawObj.material.setUniformTex2d("tex", tex)

                            // Tex2d@ tex = new Tex2d()
                            // tex.loadImageByPathCstr("../asset/Lgrd.png")
                            // o.drawObj.material.setUniformTex2d("tex", tex)

                            // Tex2d@ tex1 = new Tex2d()
                            // tex1.loadImageByPathCstr("../asset/Ldrt.png")
                            // o.drawObj.material.setUniformTex2d("tex1", tex1)
                        }
                        self.glPreviewView = o

                        o.width = 500
                        o.height = 500

                        layoutAlignPositionCell(o, 0).{
                            // self.imgCell = o
                            o.left = 0
                            o.top = 0
                            o.right = 0
                            o.bottom  = 0
                        }

                    }
                }

                if 1 {
                    mkSglSceneView(o, 0).{
                        
                        self.sceneView = o
                        // Initialize scene and camera
                        
                        // o.backgroundColor = 0xf1222222
                        o.backgroundColor = 0x00ffffff
                        o.setImageMode(Cover)
                        if o.matl != self.matl {
                            o.mkBaseScene()
                            self.editCtx.setSceneView ( o)

                            useEbus().emit(new EventSglSceneChanged())

                            Tex2d@ tex = new Tex2d()
                            tex.loadImageByPathCstr("../asset/terrain.png")

                            DrawCtx@ dc = new DrawCtx()
                            self.matl = dc.depthMatl
                            o.matl = self.matl
                            o.buildDrawObj()

                            // GeometrySphere@ geom = new GeometrySphere()
                            // geom.radius = 100


                            // GeometryCone@ geom = new GeometryCone()
                            GeometryArrow@ geom = new GeometryArrow()
                            // // geom.planeType = 1
                            // geom.height = 800
                            // // geom.radiusTop = 100
                            // geom.radiusBottom = 200
                            // geom.width = 1000
                            // geom.height = 1000
                            // geom.depth = 1000
                            geom.build()
                            o.drawObj.geometry = geom

                            Mesh@ m = new Mesh()
                                self.meshSphere = m


                            // requestAnimationFrame(^bool(){
                            //     // printf("position.x:%f\n", m.position.x)
                            //     // m.position.x += 1
                            //     m.rotation.y += 0.01
                            //     return false
                            // })

                            m.material = new Material()
                            m.material.load("../asset/hi.matl.json")
                            m.material.setUniformTex2d("tex", tex)
                            // m.material = o.drawObj.material
                            m.geometry = geom
                            m.position.y = -50
                            m.position.z = 100
                            m.visible = true
                            // m.rotation.y = 0.1
                            // m.position.x = 0
                            o.scene.appendChild(m)

                            Scene* scene = o.scene
                            Draw * drawObj = o.drawObj

                            
                            new PointLight().{
                                o.position.set(-500, 100, 0)
                                scene.appendChild(o)
                                // requestAnimationFrame(^void(){
                                //     o.position.x += 10
                                //     printf("light. x:%f\n", o.position.x)
                                // })
                            }

                            new Mesh().{
                                m = o;
                                o.material = new Material()
                                o.material.load("../asset/heightmap.matl.json")
                                o.material.setUniformTex2d("tex", tex)
                                // o.material = drawObj.material

                                o.geometry = self.geom
                                o.position.y = 0
                                scene.appendChild(o)
                            }
                            if 0 {
                                MdxReader@ mr = new MdxReader()
                                // mr.loadByPathCstr("../asset/Human/Farm/Farm.mdx")
                                mr.loadByPathCstr("../asset/Units/Human/Footman/Footman.mdx")
                                MkMdx@ mkMdx = new MkMdx()
                                mkMdx.mr = mr
                                mkMdx.mkSkeleton()

                                new Obj3d().{
                                    if mkMdx.ske.parent != o{
                                        o.appendChild(mkMdx.ske)

                                        MdxSeqPlayer@ player = new MdxSeqPlayer()
                                        player.init(mr)
                                        o.appendChild(player)
                                        player.play("Stand - 1")
                                        // player.play("Walk")
                                        // player.play("Attack - 1")
                                    }
                                    m = o;
                                    // Material@ material = new Material()
                                    // material.load("../asset/mdx.matl.json")
                                    o.position.y = 0
                                    // o.rotation.x = 1.57

                                    scene.appendChild(o)
                                    Obj3d* parent = o

                                    for int i = 0; i < mr.geosets.size(); i++{
                                        Geoset* geoset = (Geoset*) mr.geosets.get(i)
                                        MdxMaterial*  mmatl = mr.matls.get(geoset.material_id)
                                        Layer* layer = mmatl.layers.get(0)
                                        LayerTexture* layerTexture = layer.textures.get(0)
                                        TextureData *texData = mr.texs.get(layerTexture.id)
                                        const char *texPath = texData.getRealPath()
                                        new SkinMesh().{
                                            // o.skeleton = mkMdx.ske
                                            Material@ material = new Material()
                                            material.load("../asset/mdx.matl.json")

                                            Tex2d@ tex = new Tex2d()
                                            tex.loadImageByPathCstr(str("../asset/").add(texPath).str)
                                            material.setUniformTex2d("tex", tex)

                                            o.material = material
                                            // o.material.setUniformTex2d("tex", tex)
                                            // o.material = drawObj.material

                                            o.geometry = geoset.geom
                                            mkMdx.ske.appendChild(o)
                                        }
                                    }
                                }
                            }
                            // new Skybox().{
                            //     // m = o
                            //     o.position.y = 300
                            //     scene.appendChild(o)
                            // }
                            o.drag.onDrag = ^void(Drag *d){
                                // m.rotation.x += toRad(d.deltaPos.x)
                                if d.mouseDownButton == 1 {
                                    m.rotation.y += toRad(d.deltaPos.x)
                                }
                                if d.mouseDownButton == 2 {
                                    m.rotation.x += toRad(d.deltaPos.y)
                                }
                                if d.mouseDownButton == 3 {
                                    m.scale.x = maxFloat(0.1, m.scale.x + d.deltaPos.x / 100.0)
                                    m.scale.y = m.scale.x
                                    m.scale.z = m.scale.x
                                }
                            }

                            new Mesh().{
                                self.mesh = o
                                
                                GeometryPlane@ geom = new GeometryPlane()
                                geom.width = 10000
                                geom.height = 10000
                                geom.planeType = 1
                                geom.build()

                                o.material = new Material()
                                o.material.load("../asset/hi.matl.json")
                                o.material.setUniformTex2d("tex", tex)
                                // o.material = drawObj.material

                                o.geometry = geom
                                o.position.y = 10
                                o.visible = false
                                scene.appendChild(o)
                            }
                            // new Mesh().{
                            //     GeometryBox@ geom = new GeometryBox()
                            //     geom.build()

                            //     Buffer@ insPos = new Buffer()
                            //     for int i = 0; i < 3; i++ {
                            //         float x = randRadiusf(400)
                            //         float z = randRadiusf(400)
                            //         // printf("x, z:%f,%f\n", x, z)
                            //         insPos.appendFloat3(x, 0, z)
                            //     }

                            //     geom.setInstanceAttrByBuffer("insPos", insPos, 3)

                            //     o.material = new Material()
                            //     o.material.load("../asset/hi.matl.json")
                            //     o.material.setUniformTex2d("tex", tex)

                            //     // o.material = drawObj.material

                            //     o.geometry = geom
                            //     o.position.z = 500

                            //     scene.appendChild(o)
                            // }
                            // new ParticleEmitter().{
                            //     scene.appendChild(o)
                            // }

                            o.drawObj.material.setUniformTex2d("tex", tex)
                        }

                        o.width = 500
                        o.height = 500

                        layoutAlignPositionCell(o, 0).{
                            // self.imgCell = o
                            o.left = 0
                            o.top = 0
                            o.right = 0
                            o.bottom  = 0
                        }

                    }
                }

            // printNodeTree(o, 0)
            return o
        }
    }
    Mesh@ mesh
    Mesh@ meshSphere
    SglSceneView@ sceneView

    void drawDepthView(){
        DrawCtx@ dctx = new DrawCtx()

        // dctx.depthMatl = self.sceneView.drawObj.material

        Fbo@ fbo = new Fbo()
        Frame frame = self.sceneView.frame
        fbo.buildWithColorDepthStencilTexture(
            (int)frame.width, (int)frame.height,
            true, 
            true, 
            false
        )
        fbo.setGlDrawBufferNone()

        fbo.startDraw(0.2, 0.2, 0.2, 1.0, true, true, true)


        PerspectiveCamera@ cam = new PerspectiveCamera()

        cam.target = mkVec3(0, 0, 0)
        cam.up = mkVec3(0, 1, 0)
        cam.fov = 45 / 180.0 * PI
        cam.aspect = 1.0
        cam.nearPlane = 100.1
        cam.farPlane = 5000
        
        // Position camera
        // cam.position = mkVec3(0, 2500, 500)
        cam.position.set(-10, 2000, 0.10) //注意up。不要跟up同一直线了
        cam.updateWorldTransformAndSubtree()

        dctx.drawDepth(
            self.sceneView.scene,
            // self.sceneView.camera
            cam
        )

        DepthTexturePreview@ prev = new DepthTexturePreview()
        prev.init_readPixels( (int)frame.width, (int)frame.height)

        fbo.endDraw()


        fbo.setGlDrawBufferDefault()
        SglSceneView_showTextureWindow(fbo.tex2d, (int)frame.width, (int)frame.height)
        prev.showTextureWindow()

        // self.meshSphere.material.setUniformTex2d("tex", fbo.depthTex2d)
        self.mesh.material.setUniformTex2d("shadowMap", fbo.depthTex2d)
        self.mesh.material.setUniform1i("hasShadow", 1)
        self.mesh.material.setUniformMat4("shadowVp", cam.calcVp())
        // self.mesh.material.setUniformTex2d("tex", fbo.tex2d)
        // self.meshSphere.visible = false
    }

    void react(){
        printf("react SpriteSheetEditor\n")
        Theme* t = themeIns()
        self.win.rootView.{
            if 1 {
                //菜单
                layoutLinear(o, 0).{
                    // o.height = 30
                    o.backgroundColor = t.menubar_bg
                    // o.backgroundColor = 0xcc000000
                    o.padding.setAxis(0, 6)
                    String@ btnsStr = str("文件,项目,视图,调试,窗口,帮助")
                    List@ btns = btnsStr.splitByRe(",")
                    MenuBarCtrl@ group = new MenuBarCtrl()
                    group.cbCreateMenuNativeItem = ^MenuNativeItem@ (MenuButton* mbutton){
                        ^void onActive(MenuNativeItem*item){
                            printf("\n\n========================================onActive menu:%s\n", item.label.str)
                            if item.label.equals("退出"){
                                exit(0);
                            }
                            if item.label.equals("绘制深度图"){
                                // Toast_make(item.label.str)
                                self.drawDepthView()
                            }
                        }
                        mkMenuNativeItem(null, null, null).{
                            if mbutton.text.equals("文件"){
                                mkMenuNativeItem(o, str("新建场景"), onActive)
                                mkMenuNativeItem(o, str("打开场景"), onActive)
                                mkMenuNativeItem(o, str("保存场景"), onActive)
                                mkMenuNativeItem(o, str("最近打开"), onActive).{
                                    mkMenuNativeItem(o, str("场景1"), onActive)
                                    mkMenuNativeItem(o, str("场景2"), onActive)
                                }
                                mkMenuNativeItem(o, str("另存为场景"), onActive)
                                mkMenuNativeItem(o, str("保存所有场景"), onActive)
                                mkMenuNativeItem(o, str("关闭场景"), onActive)
                                mkMenuNativeItem(o, str("重载已保存的场景"), onActive)
                                mkMenuNativeItem(o, str("设置"), onActive)
                                mkMenuNativeItem(o, str("退出"), onActive)
                            }
                            else if mbutton.text.equals("调试"){
                                mkMenuNativeItem(o, str("绘制深度图"), onActive)
                            }
                            else {
                                mkMenuNativeItem(o, str("退出"), onActive)
                            }
                            return o;
                        }
                    }
                    // group.window = win;
                    for (int i = 0; i < btns.size(); i++){
                        Object* obj = btns.get(i)
                        String@ btn = (String@)btns.get(i)
                        mkMenuButton(o, i).{
                            MenuButton@ mbutton = o

                            o.text = btn
                            o.onMouseMove = ^void(MouseEvent *me){
                                // printf("onmove:%p\n", mbutton)
                                group.onmove(mbutton, me)
                            }
                            o.onClick =^void(MouseEvent *me){
                                group.onclick(mbutton, me)
                            }
                        }
                    }
                }

                layoutLinear(self.win.rootView, 0).{
                    mkDrawButton(o, 0).{
                        o.text = str("设置")
                        o.onClick = ^void(MouseEvent *me){
                            // Toast_make("设置地图属性")
                            // self.showWindow_mapSetting()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("添加tilelayer")
                        o.onClick = ^void(MouseEvent *me){
                            // self.addTileLayer()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("添加tileset")
                        o.onClick = ^void(MouseEvent *me){
                            // self.ui_addtileset()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("创建随机tile")

                        o.onClick = ^void(MouseEvent*me){
                            // self.removeCurAnim()
                            // self.ui_createRandomTile()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("创建动画tile")

                        o.onClick = ^void(MouseEvent*me){
                            // self.removeCurAnim()
                            // self.ui_createAnimTile()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("创建AutoTile")

                        o.onClick = ^void(MouseEvent*me){
                            // self.removeCurAnim()
                            // self.ui_createAutoTile()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("打印树")
                        o.onClick = ^void(MouseEvent*me){
                            self.printSceneTree()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("保存")
                        o.onClick = ^void(MouseEvent*me){
                            // long long t0 = Time_unixMs()
                            // Json@ jo = Json_toJson(self.map)
                            // long long t1 = Time_unixMs()
                            // printf(" toJson ms:%lld\n", t1 - t0)
                            // String@ json = jo.dump()
                            // // printf("json:%s\n", json.str)
                            // Path_writeText(self.path.str, json.str)
                            Toast_make("保存成功")
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("加载")
                        o.onClick = ^void(MouseEvent*me){
                            // Json@ jo = Json_parseByPathCstr(self.path.str)
                            // // printf("加载. json:%s\n", jo.dump().str)
                            // printf("加载json完成\n")
                            // TileMap@ map = jo.toObjectByVtable(TileMap)
                            // self.map = map
                            // printf("new map tilesets :%d, layers:%d\n",
                            //     self.map.tilesets.size(),
                            //     self.map.layers.size(),
                            // )
                            self.invalidReact.invalid()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("lala")
                        o.onClick = ^void(MouseEvent*me){
                        }
                    }
                }
            }

            // mkMaterialPreviewView(o, 0).{
            //     o.backgroundColor = 0x00222222
            //     o.setImageMode(Cover)
            //     if o.matl != self.matl {
            //         o.matl = self.matl
            //         o.buildDrawObj()
            //     }
            //     self.glPreviewView = o
            //     o.width = 500
            //     o.height = 500
            // }

            if 1 {

                dockLayout(o, 0).{
                    dockLayoutIns = o
                    o.width = 100
                    o.height = 20

                    o.backgroundColor = 0x30000033
                    if(o.isNewForReact){
                        o.cbRenderItemHeadView = ^void (
                            DockItem *item, ViewBase *o, int kidIndex
                        ){
                            DockItem@ tmpItem = item
                            DockLayout@ tmpDock = dockLayoutIns
                            mkTextView(o, (long long)item).{
                                o.cursor = str("pointer")
                                o.setText(item.id)
                                // o.color = 0xff00ff00
                                o.color = t.dock_head_c
                                o.padding.top = 4
                                o.padding.setHor(8)
                                // o.margin.right = 4
                                // o.margin.top = 8
                                o.border.setAll(0.0f, 0xffaeaeb2)

                                bool active =  item.parent.tabActiveIndex == kidIndex 
                                if active {
                                    o.border.t.w = 2.f;
                                    o.border.t.color = t.c_main
                                }

                                if kidIndex < item.parent.children.size() - 1{
                                    o.border.r.w = 1.f;
                                }
                                // o.backgroundColor = 
                                    // item.parent.tabActiveIndex == kidIndex ? 0x99000030l
                                    // : 0x66000030
                                o.backgroundColor = 
                                    active ? t.dock_head_bg_active
                                    : t.dock_head_bg
                            }
                        }
                        o.cbRenderItemContentView = ^ViewBase* (DockItem *item, ViewBase *o){
                            if (item.id.equals("project")){
                                mkAssetDirTreeView(o, (long long)item).{
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("dir")){
                                mkAssetDirView(o, (long long)item).{
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("hier")){
                                mkSglSceneHierView(o, (long long)item).{
                                    o.editCtx = self.editCtx
                                    // o.backgroundColor = t.dock_content_bg
                                    o.backgroundColor = 0xffffffff
                                    return o
                                }
                            }
                            if (item.id.equals("inspector")){
                                mkSglInspView(o, (long long)item).{
                                    o.editCtx = self.editCtx
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("scene")){
                                return self.reactScene(o, item)
                            }
                            if (item.id.equals("inspector")){
                                // return self.reactPreview(o, item)
                            }
                            if (item.id.equals("layers")){
                                // return self.reactLayers(o, item)
                            }
                            if (item.id.equals("tilesets-list")){
                                // return self.reactTilesetsNames(o, item)
                            }
                            if (item.id.equals("tileset-preview")){
                                // return self.reactTilesetView(o, item)
                            }
                            // if (item.id.equals("scene")){
                            //     mkSglSceneView(o, (long long)item).{
                            //         o.backgroundColor = t.dock_content_bg
                            //         layoutLinearCell(o, 0).{
                            //             o.grow = 1
                            //         }
                            //         return o
                            //     }
                            // }


                            mkTextView(o, (long long)item).{
                                o.needClip = true

                                printf("render dock content:%d, %s\n", item.intId, item.id.str);
                                o.setText(item.id)
                                o.font_size = 30
                                o.color = 0xff000000
                                o.radius.setAll(6)
                                o.padding.setAll(6)

                                o.backgroundColor = 
                                    item.intId == 0 ? 0x53ff0000
                                    : item.intId == 1 ? 0x53f0ff00
                                    : item.intId == 2 ? 0x5330ffff
                                    : 0x5300ffff

                                layoutLinearCell(o, 0).{
                                    o.grow = 1
                                }

                                return o
                            }
                        }

                        o.root.{
                            o.isHorizontal = false

                            mkDockItemSplitter(o, null, true).{
                                mkDockItem(o, str("hier")).{
                                    o.intId = 0;
                                    o.width = 150
                                }
                                mkDockItem(o, str("scene")).{
                                    o.intId = 0;
                                }
                                mkDockItem(o, str("inspector")).{
                                    o.intId = 0;
                                    o.width = 150
                                }
                            }
                            mkDockItemSplitter(o, null, true).{
                                o.width = 150
                                mkDockItem(o, str("project")).{
                                    o.intId = 0;
                                    o.width = 160
                                }
                                mkDockItem(o, str("dir")).{
                                    o.intId = 0;
                                }
                            }
                        }

                        // mkDockItemTab(root, str("tab-0")).{
                        //     o.width = 150
                        // }
            
                        // mkDockItemTab(root, str("tab-inspector")).{
                        //     o.width = 250
                        //     mkDockItem(o, str("inspector")).{
                        //         o.intId = 2 
                        //     }
                        // }
                    }

                    layoutLinearCell(o, 0){}
                }
            }
        }
    }



    void showWindow_mapSetting(){
        Window@ win = null


        ^void () reactMapSetting = ^ void () {
            win.rootView.{
                mkTextView(o, 0).{
                    o.setText(str("tileWidth:"))
                }
                mkEditText(o, 0).{
                    // o.setValue_notInFocus(str("").addi(self.map.tileWidth))
                    // o.onValueChanged = ^void (EditText*et){
                    //     int rows = et.value.toInt()
                    //     self.map.tileWidth = rows
                    //     reactMapSetting()
                    //     self.invalidReact.invalid()
                    // }
                }
                mkTextView(o, 0).{
                    o.setText(str("tileHeight:"))
                }
                mkEditText(o, 0).{
                    // o.setValue_notInFocus(str("").addi(self.map.tileHeight))
                    // o.onValueChanged = ^void (EditText*et){
                    //     int rows = et.value.toInt()
                    //     self.map.tileHeight = rows
                    //     reactMapSetting()
                    //     self.invalidReact.invalid()
                    // }
                }
                mkTextView(o, 0).{
                    o.setText(str("fps:"))
                }
                mkEditText(o, 0).{
                    // o.setValue_notInFocus(str("").addi(self.map.fps))
                    // o.onValueChanged = ^void (EditText*et){
                    //     int v = et.value.toInt()
                    //     self.map.fps = v
                    //     reactMapSetting()
                    //     self.invalidReact.invalid()
                    // }
                }
                // mkTextView(o, 0).{
                //     o.setText(str("fps:"))
                // }
                // mkEditText(o, 0).{
                // }
                mkDrawButton(o, 0).{
                    o.text = str("提交")
                    o.onClick = ^void (MouseEvent *me){
                        reactMapSetting()
                    }
                }
            }
        }

        new Window().{
            win = o
            new LayoutLinear().{
                o.backgroundColor = 0xffffffff
                o.direction.set("column")
                o.alignItems.set("stretch")
                win.setRootView(o)
            }

            reactMapSetting()

            o.setTitle("地图设置")
            o.setSize(300, 400)
            o.moveToCenter()
            o.show()
        }
    }
    W3e@ w3e
    Geometry@ geom

    void onWindowEvent(Event *e){
        if e instanceof KeyEvent {
            KeyEvent *ke = (KeyEvent*)e
            printf("2窗口收到键盘消息:%s\n", ke.key.str);
            //前进
            if ke.key.equals("W"){
                self.sceneView.camera.moveForward()
            }
            if ke.key.equals("S"){
                self.sceneView.camera.moveBackward()
            }
            //左转
            if ke.key.equals("A"){
                self.sceneView.camera.rotateLeft()
            }
            if ke.key.equals("D"){
                self.sceneView.camera.rotateRight()
            }
            //升降
            if ke.key.equals("E"){
                self.sceneView.camera.rise()
            }
            if ke.key.equals("Q"){
                self.sceneView.camera.fall()
            }
        }
    }

    void showWindow(){
        self.win = new Window() //先创建窗口，初始化opengl环境

        if 1 {
            W3e@ w3e = new W3e()
            self.w3e = w3e;
            w3e.load("../asset/100.w3e")

            self.geom = w3e.mkGeometry()

            GeometryHeightMap@ geom = new GeometryHeightMap();
            geom.buildByPath("../asset/heightmap.png")

            self.geom = geom

            w3e.mkGroundTexs()
            // testBuffer()
            // return;
        }

        self.win.{
            o.cbOnEvent = ^void (Event*e){
                self.onWindowEvent(e)
            }

            self.matl = new Material()
            self.matl.load("../asset/hi.matl.json")

            new LayoutLinear().{
                o.backgroundColor = 0xffffffff
                o.direction.set("column")
                o.alignItems.set("stretch")

                // ChessBgViewCallback@ tmp= new ChessBgViewCallback()
                // o.cb  = tmp

                self.win.setRootView(o)
            }

            self.react()


            o.setTitle("瓦片地图编辑器")
            o.setSize(800, 600)
            o.show()
        }
    }
}