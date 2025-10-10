package SuiDesigner

#include "../Orc/Orc.h"
#include <stdio.h>

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
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/View/DockLayout.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "./ChessBgViewCallback.orc"
import * from "./Theme.orc"
import * from "./InvalidReact.orc"

static DockLayout@ dockLayoutIns = null

//精灵帧动画播放器
class SpriteSheetPlayerView extends View{
    int coordIndex = 0
    Timer@ timer 

    void ctor(){
        self.timer = mkTimerInterval(^void (){
            printf("anim tick ms:%lld\n", Time_unixMs())
            if self.info && self.info.fps > 0{
                self.timer.intervalMs = 1000 / self.info.fps
            } else {
                self.timer.intervalMs = 100
            }
            self.coordIndex++
            self.invalidDraw()
        }, 100)
    }

    void onMounted(){
        super.onMounted()
    }
    void onUnmounting(){
        super.onUnmounting()
        self.timer.cancel()
    }

	void draw_self(Canvas* canvas) {
        super.draw_self(canvas)

        if self.info && self._anim && self._anim.coords.size() > 0 && self._isImageValid() {
            int w = self._img.width()
            int h = self._img.height()
            int rowh = h / self.info.rows
            int colw = w / self.info.cols
            self.coordIndex = self.coordIndex % self._anim.coords.size()
            SpriteSheetFrameCoord* coord = (SpriteSheetFrameCoord*)self._anim.coords.get(self.coordIndex)
            int x = coord.x * colw
            int y = coord.y * rowh

			drawImage_atRect(canvas, self._img, 
                x, y, colw, rowh,
                0, 0, colw, rowh 
				);
			canvas.fill();
        }
    }
	Image@ _img = NULL
    String@ src = str("")
    void setSrc(String@ src){
        if self.src && src && self.src.equals(src.str){
            return
        }

        self.src = src
        if src {
			self._img = loadImage(src.str)
        }
        else {
            self._img = null

        }
    }
	bool _isImageValid(){
		return self._img != NULL;
	}
    void updateAnim(){
        if self.info {
            if self.animName.empty(){
                if self._anim != null{
                    self._anim = null;
                }
                return;
            }

            if self._anim == null || !self.animName.equals (self._anim.name.str){
                self._anim = self.info.getAnimByName(self.animName.str)
                
            }
        }
        else {
            self._anim = null
        }
    }

    String@ animName = str("")

    void setAnimName(String@ animName){
        if self.animName && animName && animName.equals(self.animName.str){
            return;
        }
        self.animName = animName == null ? str(""): animName
        self.updateAnim()
    }

    SpriteSheetAnim@ _anim;
    SpriteSheetInfo@ info;
}
SpriteSheetPlayerView@ mkSpriteSheetPlayerView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (SpriteSheetPlayerView@)gocNode(sp, (Node*)parent, SpriteSheetPlayerView)
}


class SpriteSheetFrameCoord {
    int x = 0
    int y = 0


    void fromJson(Json* jo){
        self.x = jo.getInt("x")
        self.y = jo.getInt("y")
    }
    void toJson(Json* jo){
        jo.putNumber("x", self.x)
        jo.putNumber("y", self.y)
    }
}
class SpriteSheetAnim {
    String@ name = str("");
    //SpriteSheetFrameCoord
    List@ coords = new List()

    void fromJson(Json* jo){
        self.name = jo.getString("name")
        self.coords = jo.getObjectsByVtable("coords", SpriteSheetFrameCoord)
    }
    void toJson(Json* jo){
        jo.putString("name", self.name)
        jo.putObject("coords", self.coords)
    }

    int getIndexOfFrame(int x, int y){
        for int i = 0; i < self.coords.size(); i++{
            SpriteSheetFrameCoord* e = (SpriteSheetFrameCoord*)self.coords.get(i)
            if e.x == x && e.y == y{
                return i
            }
        }
        return -1
    }
    void addFrame(int x, int y){
        int idx = self.getIndexOfFrame(x, y)
        if idx == -1 {
            SpriteSheetFrameCoord@ e = new SpriteSheetFrameCoord()
            e.x = x 
            e.y = y 
            self.coords.add(e)
        }
    }
    void removeFrame(int x, int y){
        for int i = 0; i < self.coords.size(); i++{
            SpriteSheetFrameCoord* e = (SpriteSheetFrameCoord*)self.coords.get(i)
            if e.x == x && e.y == y{
                self.coords.removeAt(i)
                i--
            }
        }
    }
}
class SpriteSheetInfo {
    float fps = 10
    int rows = 9
    int cols = 8
    //<SpriteSheetAnim>
    List@ anims = new List()

    SpriteSheetAnim@ getAnimByName(const char *name){
        for int i = 0; i < self.anims.size(); i++{
            SpriteSheetAnim* anim = (SpriteSheetAnim*)self.anims.get(i)
            if anim.name.equals(name){
                return anim
            }
        }
        return null
    }

    void fromJson(Json* jo){
        self.fps = jo.getNumber("fps")
        self.rows = jo.getInt("rows")
        self.cols = jo.getInt("cols")
        self.anims = jo.getObjectsByVtable("anims", SpriteSheetAnim)
    }
    void toJson(Json* jo){
        jo.putNumber("fps", self.fps)
        jo.putNumber("rows", self.rows)
        jo.putNumber("cols", self.cols)
        jo.put("anims", Json_toJson(self.anims))
    }
}
// class TmpCb extends ViewCallback{
//     bool cbLayout(View*div, Frame *ctx){
//         printf("tmpCb cbLayout\n")
//         return false;
//     }
// }
class SpriteSheetEditor{
    Window@ win
    Drag@ drag = new Drag()
    Drag@ dragPreview = new Drag()
    //选择帧用的
    Drag@ dragChoose = new Drag()

    LayoutAlignPositionCell@ imgCell
    LayoutAlignPositionCell@ previewCell

    InvalidReact@ invalidReact  = mkInvalidReact(self)

    String@ path = str("a.spriteSheet.json")
    SpriteSheetInfo@ info = new SpriteSheetInfo()
    SpriteSheetAnim@ curAnim 

    // List@ activeAnims = new List()

    ImageView@ sceneImageView
    SpriteSheetPlayerView@ playerView
    // ViewCallback@ viewCb = new TmpCb()


    void printSceneTree(){
        printNodeTree(self.sceneImageView, 0)
    }

    int getFrameIndex(int x, int y){
        if self.curAnim {
            int idx = self.curAnim.getIndexOfFrame(x, y)
            return idx 
        }
        return -1
    }

    void ctor(){
        self.drag.onDrag = ^void(Drag *d){
            if d.isDragging {
                self.imgCell.left += d.deltaPos.x
                self.imgCell.top += d.deltaPos.y

                self.invalidReact.invalid()
            }
        }
        self.dragPreview.onDrag = ^void(Drag *d){
            if d.isDragging {
                self.previewCell.left += d.deltaPos.x
                self.previewCell.top += d.deltaPos.y

                self.invalidReact.invalid()
            }
        }
        self.dragChoose.onDrag = ^void(Drag *d){
            if d.isDragStart|| d.isDragging {
                if self.sceneImageView {
                    ViewBase* vb = self.sceneImageView.hitTest(d.currentClientPos.x, d.currentClientPos.y)
                    if vb instanceof View && vb.name.startsWith("cell:"){
                        int x = 0
                        int y = 0
                        sscanf(vb.name.str, "cell:%d,%d", &x, &y)
                        printf("hover cell:%s. x,y:%d,%d\n", vb.name.str, x, y)

                        if self.curAnim {
                            if d.mouseEvent.ctrl{
                                self.curAnim.removeFrame(x, y)
                            }
                            else {
                                self.curAnim.addFrame(x, y)
                            }
                            self.invalidReact.invalid()
                        }
                    }
                }
            }
        }
    }
    
    void removeCurAnim(){
        if self.curAnim {
            int index = self.info.anims.indexOf(self.curAnim)
            self.info.anims.remove(self.curAnim)
            index = minInt(index, self.info.anims.size() - 1)
            self.curAnim = self.info.anims.get(index)
            self.invalidReact.invalid()
        }
    }


    ChessBgViewCallback@ chessBg= new ChessBgViewCallback()

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
                    if me.button == 3 && me.isBubble() && me.isMouseDown {
                        self.dragPreview.onMouseDown(me)
                    }
                }
            }

            layoutLinearCell(o, 0)


            mkSpriteSheetPlayerView(o, 0).{
                // o.border.setAll(1, 0xffff0000)
                o.setSrc(str("../asset/AnimationSheet_Character.png"))
                o.info = self.info
                o.setAnimName(self.curAnim? self.curAnim.name : null)
                self.playerView = o

                layoutAlignPositionCell(o, 0).{
                    self.previewCell = o
                    // o.left = 100
                    // o.top = 100
                }
            }
            return o
        }
    }
    void showDialog_rename(SpriteSheetAnim@ anim){
                                            // Toast_make(anim.name.str)
        MessageDialog_prompt(anim.name.str, "重命名", ^void (String@ newValue) {
            anim.name = newValue
            self.invalidReact.invalid()
        })
    }
    ViewBase* reactAnimNames(Node* o, DockItem *item){
        mkScrollArea(o, (long long)item).{
            o.useMinWidthConstraint = true
            o.alignItems .set("stretch")
            // o.width = 10
            // o.height = 10

            layoutLinearCell(o, 0)

            layoutLinear(o, (long long)item).{
                o.direction.set("column")
                o.alignItems.set("maxOrStretch")
                o.backgroundColor = 0x33ffff00

                for int i = 0; i < self.info.anims.size(); i++{
                    SpriteSheetAnim@ anim = (SpriteSheetAnim@)self.info.anims.get(i)

                    mkTextView(o, (long long)anim).{
                        o.setText(anim.name)
                        o.cursor.set("pointer")


                        mkHoverViewEffect(o, 0).{
                            o.hoverBorder.setAll(1, 0x00000000)
                            o.activeBorder.setAll(1, 0x00000000)
                            o.backgroundColor = i% 2 == 0 ? 0x00ffff00: 0x33ffffff
                            o.hoverBackgroundColor = 0x33ff0000
                            o.activeBackgroundColor = 0x66ff0000
                            o.isActive = self.curAnim == anim

                            o.onHostEvent = ^bool (Event *e){
                                MouseEvent *me = (MouseEvent*)e
                                if me.button == 3 && me.isClickInBubble() {
                                    ^void onActive(MenuNativeItem *item){
                                        if item.cmd.equals("重命名"){
                                            self.showDialog_rename(anim)
                                        }
                                    }
                                    mkMenuNativeItem(null, str(""), onActive).{
                                        mkMenuNativeItem(o, str("重命名"), onActive).{ }

                                        MenuNative@ n = new MenuNative()
                                        n.create(o)
                                        n.showAtMouse()
                                    }
                                    return true
                                }

                                return false;
                            }

                            o.onClick = ^void(MouseEvent*me){
                                self.curAnim = anim
                                self.invalidReact.invalid()
                                // // o.isActive = !o.isActive 
                                // o.react()
                            }
                        }
                    }
                }
            }
            return o
        }
    }
    ViewBase* reactScene(Node* o, DockItem *item){
        layoutAlign(o, (long long)item).{
            o.useMaxConstraint = false
            // o.direction.set("column")
            // o.alignItems.set("start")
            o.needClip = true
            o.cb  = self.chessBg 
            o.cbOnEvent = ^void(Event*e){
                if e instanceof MouseEvent {
                    MouseEvent *me = (MouseEvent*)e;
                    if me.button == 3 && me.isBubble() && me.isMouseDown {
                        self.drag.onMouseDown(me)
                    }
                    if me.button == 1 && me.isBubble() && me.isMouseDown {
                        self.dragChoose.onMouseDown(me)
                    }
                }

            }

            layoutLinearCell(o, 0)


            mkImageView(o, 0).{
                o.border.setAll(1, 0xffff0000)
                o.setSrc(str("../asset/AnimationSheet_Character.png"))

                self.sceneImageView = o


                layoutAlignPositionCell(o, 0).{
                    self.imgCell = o
                    // o.left = 100
                    // o.top = 100
                }

                int w = o._img.width()
                int h = o._img.height()
                int rowh = h / self.info.rows
                int colw = w / self.info.cols

                //行线
                for int i = 0; i < self.info.rows; i++{
                    mkView(o, 1000+i).{
                        o.name  = str("rowLine:").addi(i)
                        o.frame.y = i * rowh
                        o.backgroundColor = 0xffff0000
                        o.height = 1
                        o.width = w
                    }
                }
                //列线
                for int i = 0; i < self.info.cols; i++{
                    mkView(o, 2000+i).{
                        o.name  = str("colLine:").addi(i)
                        o.frame.x = i * colw
                        o.backgroundColor = 0xffff0000
                        o.width = 1
                        o.height = h
                    }
                }
                //格子
                for int y = 0; y < self.info.rows; y++{
                    for int x = 0; x < self.info.cols; x++{
                        mkView(o, 30000+y * 100 + x).{
                            o.name  = str("cell:").addi(x).add(",").addi(y)
                            o.frame.x = x * colw
                            o.frame.y = y * rowh
                            o.width = colw
                            o.height = rowh
                            o.frame.width = colw
                            o.frame.height = rowh

                            // o.cb = self.viewCb

                            int frameIndex = self.getFrameIndex(x, y)


                            mkHoverViewEffect(o, 0).{
                                o.hoverBorder.setAll(1, 0x00000000)
                                o.activeBorder.setAll(1, 0x00000000)
                                o.backgroundColor = 0x00ff0000
                                o.hoverBackgroundColor = 0x33ff0000
                                o.activeBackgroundColor = 0x66ff0000
                                o.isActive = frameIndex != -1
                                // o.onClick = ^void(MouseEvent*me){
                                    // o.isActive = !o.isActive 
                                    // o.react()
                                // }
                            }

                            if  frameIndex != -1 {
                                mkTextView(o, 0).{
                                    o.frame.x = 0
                                    o.frame.y = 0
                                    o.width = colw
                                    o.height = rowh

                                    // o.backgroundColor = 0x33ffff00
                                    o.text_align.set("center")
                                    o.setText(str("").addi(frameIndex))
                                    o.color = 0xffffffff
                                    o.hitTestType.set("none")
                                }
                            }
                        }
                    }
                }
                // printf("render grid\n");
            }

            // printNodeTree(o, 0)
            return o
        }
    }

    void react(){
        printf("react SpriteSheetEditor\n")
        Theme* t = themeIns()
        self.win.rootView.{
            layoutLinear(self.win.rootView, 0).{
                mkTextView(o, 0).{
                    o.setText(str("rows:"))
                }
                mkEditText(o, 0).{
                    o.setValue_notInFocus(str("").addi(self.info.rows))
                    o.onValueChanged = ^void (EditText*et){
                        int rows = et.value.toInt()
                        self.info.rows = rows
                        self.invalidReact.invalid()
                    }
                    // o.setText(str("你vb"))
                }
                mkTextView(o, 0).{
                    o.setText(str("cols:"))
                }
                mkEditText(o, 0).{
                    o.setValue_notInFocus(str("").addi(self.info.cols))
                    o.onValueChanged = ^void (EditText*et){
                        int v = et.value.toInt()
                        self.info.cols = v
                        self.invalidReact.invalid()
                    }
                    // o.setText(str("你vb"))
                }
                mkTextView(o, 0).{
                    o.setText(str("fps:"))
                }
                mkEditText(o, 0).{
                    o.setValue_notInFocus(str("").addi(self.info.fps))
                    o.onValueChanged = ^void (EditText*et){
                        int v = et.value.toFloat()
                        self.info.fps = v
                        self.invalidReact.invalid()
                    }
                    // o.setText(str("你vb"))
                }
                mkDrawButton(o, 0).{
                    o.text = str("添加动画")
                    o.onClick = ^void(MouseEvent *me){
                        SpriteSheetAnim@ anim = new SpriteSheetAnim()
                        anim.name.set("新建动画")
                        self.info.anims.add(anim)
                        self.invalidReact.invalid()
                        // Toast_make("添加动画")
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("删除动画")

                    o.onClick = ^void(MouseEvent*me){
                        self.removeCurAnim()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("打印树")
                    o.onClick = ^void(MouseEvent*me){
                        self.printSceneTree()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("播放动画")
                    o.onClick = ^void(MouseEvent*me){
                        self.playCurAnim()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("保存")
                    o.onClick = ^void(MouseEvent*me){
                        Json@ jo = Json_toJson(self.info)
                        String@ s = jo.dump()
                        printf("jo:%s\n", s.str)
                        Path_writeText(self.path.str, s.str)
                        Toast_make(str("保存成功:").addString(self.path).str)
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("加载")
                    o.onClick = ^void(MouseEvent*me){
                        Json@ jo = Json_parseByPathCstr(self.path.str)

                        SpriteSheetInfo@ info = jo.toObjectByVtable(SpriteSheetInfo)
                        self.info = info
                        self.invalidReact.invalid()
                        Json@ newjo = Json_toJson(info)
                        printf("new jo:%s\n", newjo.dump().str)
                    }
                }
            }

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
                        // if (item.id.equals("project")){
                        //     mkAssetDirTreeView(o, (long long)item).{
                        //         o.backgroundColor = t.dock_content_bg
                        //         return o
                        //     }
                        // }
                        // if (item.id.equals("hier")){
                        //     mkSceneHierView(o, (long long)item).{
                        //         o.backgroundColor = t.dock_content_bg
                        //         return o
                        //     }
                        // }
                        // if (item.id.equals("inspector")){
                        //     mkInspectorView(o, (long long)item).{
                        //         o.backgroundColor = t.dock_content_bg
                        //         return o
                        //     }
                        // }
                        if (item.id.equals("image-view")){
                            return self.reactScene(o, item)
                        }
                        if (item.id.equals("preview")){
                            return self.reactPreview(o, item)
                        }
                        if (item.id.equals("anim-names")){
                            return self.reactAnimNames(o, item)
                        }
                        // if (item.id.equals("scene")){
                        //     mkSceneView(o, (long long)item).{
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

                    DockItem *root = o.root
                    mkDockItem(root, str("anim-names")).{
                        o.intId = 0;
                        o.width = 150
                    }
                    mkDockItem(root, str("image-view")).{
                        o.intId = 0;
                    }
                    mkDockItem(root, str("preview")).{
                        o.intId = 0;
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

    void playCurAnim(){
    }

    void showWindow(){
        new Window().{
            self.win = o

            new LayoutLinear().{
                o.direction.set("column")
                o.alignItems.set("stretch")

                // ChessBgViewCallback@ tmp= new ChessBgViewCallback()
                // o.cb  = tmp

                self.win.setRootView(o)
            }

            self.react()


            o.setTitle("精灵表动画编辑器")
            o.setSize(800, 600)
            o.show()
        }

    }
}