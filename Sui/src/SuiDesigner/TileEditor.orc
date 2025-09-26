package SuiDesigner

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
import * from "../Sui/Core/Mat2d.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Mouse.orc"
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
import * from "./InvalidReact.orc"

class Tile {
    int gid
}
class SpecialTile {
    int getGid(){
        return -1
    }

    void setTileAtGid(TileEditor* te, TileLayer* layer, Tileset *ts, int gid, int cellIndex){
    }
}
class RuleInfo {
    int gid; // global cell id
    int cid; // cell id
    // int startNeighborId;
    IntArray@ neighborIdArr = new IntArray()
    int ruleInt;


    bool hasByNeighPos(Tileset *ts, int x, int y){
        int nid = ts.cols * 3 * y + x;
        bool has = self.neighborIdArr.has(nid)
        return has
    }
    void buildRuleInt(Tileset *ts){
        self.gid = ts.startGid + self.cid;

        Vec2 pos = dissolveCidToGridPos(ts, self.cid)
        Vec2 npos = pos.scale(3)//neighbor pos
        // Vec2 gridPos =  ts.dissolveGidToGridPos(self.gid)
        bool lt = self.hasByNeighPos(ts, npos.x + 0, npos.y + 0) //0
        bool ct = self.hasByNeighPos(ts, npos.x + 1, npos.y + 0) //1
        bool rt = self.hasByNeighPos(ts, npos.x + 2, npos.y + 0) //2

        bool lm = self.hasByNeighPos(ts, npos.x + 0, npos.y + 1) //3
        bool cm = self.hasByNeighPos(ts, npos.x + 1, npos.y + 1) //4
        bool rm = self.hasByNeighPos(ts, npos.x + 2, npos.y + 1) //5

        bool lb = self.hasByNeighPos(ts, npos.x + 0, npos.y + 2) //6
        bool cb = self.hasByNeighPos(ts, npos.x + 1, npos.y + 2) //7
        bool rb = self.hasByNeighPos(ts, npos.x + 1, npos.y + 2) //8

        self.ruleInt = RuleInfo_mkRuleInt(
            lt, ct, rt, 
            lm, cm, rm,
            lb, cb, rb
        )
    }
}

int RuleInfo_mkRuleInt(
    bool lt, //0
    bool ct, //1
    bool rt, //2
    bool lm, //3
    bool cm, //4
    bool rm, //5
    bool lb, //6
    bool cb, //7
    bool rb, //8
){
    int v = 0
    if lt { v |= (1 << 0) }
    if ct { v |= (1 << 1) }
    if rt { v |= (1 << 2) }
    if lm { v |= (1 << 3) }
    if cm { v |= (1 << 4) }
    if rm { v |= (1 << 5) }
    if lb { v |= (1 << 6) }
    if cb { v |= (1 << 7) }
    if rb { v |= (1 << 8) }
    return v
}
static Vec2 dissolveCidToGridPos(Tileset *ts, int cid){
    int idx = cid//gid - ts.startGid
    int c = idx % ts.cols
    int r = idx / ts.cols
    return mkVec2(c, r)
}
static Vec2 dissolveNeighborIdoGridPos(Tileset *ts, int nid){
    int idx = nid //gid - ts.startGid
    int cols = ts.cols * 3
    int c = idx % cols
    int r = idx / cols
    return mkVec2(c, r)
}
//规则化、自动化的瓦片
//思路：
//3x3网格，用来表示邻近的瓦片是否也是同一个autotile,如果是的话，就选用该瓦片
class AutoTile extends SpecialTile{
    int gid = 0
    // 不是gid,是gid的变种。因为每个gid tile都变成3x3网格了。所以neighborId等于是w,h都x3了
    IntArray@ neighborIdArr = new IntArray()

    int getGid(){
        return self.gid
    }


    // neighborId转Cid cell id. gid是全局的。 cellid是当前tileset的
    int neighborIdToCid(Tileset *ts, int neighborId){
        Vec2 gridPos = dissolveNeighborIdoGridPos(ts, neighborId)
        int x = gridPos.x / 3
        int y = gridPos.y / 3

        int cid = y * ts.cols + x
        return cid
    }
    int neighborIdToGid(TileMap *map, int neighborId){
        Tileset *ts = map.findTilesetByGid(self.gid)// 当前autotile所在的tileset
        int cid = self.neighborIdToCid(ts, neighborId)

        int gid = ts.startGid + cid
        return gid;
    }


    //遍历当前autotile相关的所有gid, 如果gid在相关gid里，就算是autotile的一部分
    bool isAutoTileByGid(Tileset *ts, int gid){
        for int i = 0; i < self.neighborIdArr.size; i++{
            int nid = self.neighborIdArr.data[i]
            int curCid = self.neighborIdToCid(ts, nid)
            int curGid = ts.startGid + curCid
            if gid == curGid {
                return true
            }
        }
        return false
    }
    bool isAutoTileByLayerPos(TileMap*map, TileLayer *layer, Tileset *ts, int x, int y){
        if x < 0 || y < 0 || x >= map.width || y >= map.height {
            return false
        }
        int idx = x + y * map.width
        int gid = layer.data.data[idx]
        int bIs = self.isAutoTileByGid(ts, gid)
        return bIs
    }
    void setTileAtGid(TileEditor* te, TileLayer* layer, Tileset *ts, int gid, int cellIndex){
        layer.data.set(cellIndex, gid)

        //更新四周的格子
        int cx = cellIndex % te.map.width
        int cy = cellIndex / te.map.width

        self.buildRuleInfos(ts)

        for int dy = -1; dy <= 1; dy++{
            for int dx = -1; dx <= 1; dx++{
                int x = dx + cx
                int y = dy + cy
                int curCellIndex = y * te.map.width + x
                int curGid = layer.data.data[curCellIndex]
                int actualGid = self.getMatchedRuleGid(te.map, layer, ts, curGid, curCellIndex)
                layer.data.set(curCellIndex, actualGid)
            }
        }
    }
    //怎么计算规则： 遍历所有的neighborId, 按gid分组。 查找匹配的gid，然后返回
    int getMatchedRuleGid(TileMap* map, TileLayer *layer, Tileset *ts, int gid, int cellIndex){
        int v = self.mkRuleIntOfTile(map, layer, ts, cellIndex)
        for int i = 0; i < self.ruleInfos.size(); i++{
            RuleInfo* info = (RuleInfo*)self.ruleInfos.get(i)
            if info.ruleInt == v {
                return info.gid
            }
        }
        return gid
    }
    List@ ruleInfos = new List()


    RuleInfo* gocRuleInfoByCid(int cid){
        RuleInfo *info = self.findRuleInfoByCid(cid)
        if info == null {
            info = new RuleInfo()
            info.cid = cid
            self.ruleInfos.add(info)
        }
        return info
    }
    RuleInfo* findRuleInfoByCid(int cid){
        for int i = 0; i < self.ruleInfos.size(); i ++{
            RuleInfo *info = (RuleInfo*)self.ruleInfos.get(i)
            if info.cid == cid{
                return info
            }
        }
        return null
    }
    void buildRuleInfos(Tileset *ts){
        self.ruleInfos.clear()
        //按cid分组
        for int i = 0; i < self.neighborIdArr.size; i++{
            int neighborId = self.neighborIdArr.data[i]
            int cid = self.neighborIdToCid(ts, neighborId)
            RuleInfo* info = self.gocRuleInfoByCid(cid)

            info.neighborIdArr.append(neighborId)
        }

        // Tileset *ts = map.findTilesetByGid(self.gid)
        //计算ruleInt
        for int i = 0; i < self.ruleInfos.size(); i++{
            RuleInfo* info = (RuleInfo*)self.ruleInfos.get(i)
            info.buildRuleInt(ts)
        }
    }
    //取四周的格子,构建匹配int
    int mkRuleIntOfTile(TileMap*map, TileLayer *layer, Tileset *ts, int cellIndex){
        int x = cellIndex % map.width
        int y = cellIndex / map.width

        int lt = self.isAutoTileByLayerPos(map, layer, ts, x - 1, y - 1)
        int ct = self.isAutoTileByLayerPos(map, layer, ts, x - 0, y - 1)
        int rt = self.isAutoTileByLayerPos(map, layer, ts, x + 1, y - 1)

        int lm = self.isAutoTileByLayerPos(map, layer, ts, x - 1, y - 0)
        int cm = self.isAutoTileByLayerPos(map, layer, ts, x - 0, y - 0)
        int rm = self.isAutoTileByLayerPos(map, layer, ts, x + 1, y - 0)

        int lb = self.isAutoTileByLayerPos(map, layer, ts, x - 1, y + 1)
        int cb = self.isAutoTileByLayerPos(map, layer, ts, x - 0, y + 1)
        int rb = self.isAutoTileByLayerPos(map, layer, ts, x + 1, y + 1)

        int ret = RuleInfo_mkRuleInt(
            lt, //0
            ct, //1
            rt, //2
            lm, //3
            cm, //4
            rm, //5
            lb, //6
            cb, //7
            rb, //8
        )
        return ret
    }
}
class RandomTile extends SpecialTile{
    // int gid;
    IntArray@ gidArr = new IntArray()
    // Vec2Array@ posArr = new Vec2Array()
    int getGid(){
        if self.gidArr.size > 0{
            return self.gidArr.get(0)
        }
        return -1
    }
    void setTileAtGid(TileEditor* te, TileLayer* tileLayer, Tileset *ts, int gid, int cellIndex){
        int idx = randRange(0, self.gidArr.size)
        int actualGid = self.gidArr.get(idx)
        tileLayer.data.set(cellIndex, actualGid)
    }
}
class AnimTile extends SpecialTile{
    // int gid;
    IntArray@ gidArr = new IntArray()
    // Vec2Array@ posArr = new Vec2Array()
    int getGid(){
        if self.gidArr.size > 0{
            return self.gidArr.get(0)
        }
        return -1
    }
    void setTileAtGid(TileEditor* te, TileLayer* tileLayer, Tileset *ts, int gid, int cellIndex){
        // int idx = randRange(0, self.gidArr.size)
        // int actualGid = self.gidArr.get(idx)
        tileLayer.data.set(cellIndex, gid)
    }
    int getDrawGid(int frameId){
        if self.gidArr.size > 0 {
            int idx = frameId % self.gidArr.size
            return self.gidArr.get(idx)
        }
        return -1
    }
}

class Tileset {
    String@ imgPath = str("")
    int startGid = 1000000;

    int rows = 1
    int cols = 1

    Vec2 _imgSize
    int _tileWidth
    int _tileHeight

    List@ specialTiles = new List()

    SpecialTile* getSpecialTileAtGid(int gid){
        for int i = 0; i < self.specialTiles.size(); i++{
            SpecialTile* st = (SpecialTile*)self.specialTiles.get(i)
            if st.getGid() == gid{
                return st
            }
        }
        return null
    }



    void fromJson(Json *jo){
        self.rows = jo.getNumber("rows")
        self.cols = jo.getNumber("cols")
        self.startGid = jo.getNumber("startGid")
        self.imgPath = jo.getString("imgPath")
    }
    void toJson(Json *jo){
        jo.putNumber("rows", self.rows)
        jo.putNumber("cols", self.cols)
        jo.putNumber("startGid", self.startGid)
        jo.putString("imgPath", self.imgPath)
    }

    int calcEndGid(){
        int gid = self.startGid + self.cols * self.rows
        return gid
    }
    bool isGidBelong(int gid){
        int end = self.calcEndGid()
        return gid >= self.startGid && gid < end
    }

    int calcGid(Vec2 gridPos){
        int gid = self.startGid + gridPos.y * self.cols + gridPos.x
        return gid
    }

    Vec2 dissolveGidToGridPos(int gid){
        int idx = gid - self.startGid
        int c = idx % self.cols
        int r = idx / self.cols
        return mkVec2(c, r)
    }

    Image@ img

    Image* loadImage(){
        if self.img == null{
            self.img = loadImage(self.imgPath.str)
        }
        return self.img
    }


    void calcRowsCols(Vec2 imgSize, int tileWidth, int tileHeight){
        if tileWidth <= 0 || tileHeight <= 0 {
            printf("ERROR: tile size is 0\n");
            return
        }

        self._imgSize = imgSize
        self._tileWidth = tileWidth
        self._tileHeight = tileHeight
        self.cols = ceil(imgSize.x / (float)tileWidth)
        self.rows = ceil(imgSize.y / (float)tileHeight)

        printf("calcRowsCols:. size:%f,%f, tile:%d,%d, cols:%d, rows:%d\n"
            , 
            imgSize.x,
            imgSize.y,
            tileWidth,
            tileHeight,
            self.cols,
            self.rows,
        );
    }
}
class Layer {
    String@ name = str("")

    void fromJson(Json *jo){
        self.name = jo.getString("name")
    }
    void toJson(Json *jo){
        jo.putString("name", self.name)
    }
}
class TileLayer extends Layer{
    //<Tile>
    // List@ tiles = new List()
    IntArray@ data = new IntArray()

    void fromJson(Json *jo){
        super.fromJson(jo)
        self.data.fromJson(jo.get("data"))
    }
    void toJson(Json *jo){
        super.toJson(jo)
        jo.put("data", self.data.mkJson())
    }
}


class TileMap {
    int fps = 2
    int width = 100
    int height = 100
    int tileWidth = 32
    int tileHeight = 32

    // <Tileset>
    List@ tilesets = new List()
    // <Layer>
    List@ layers = new List()


    void fromJson(Json *jo){
        self.width = jo.getNumber("width")
        self.height = jo.getNumber("height")
        self.tileWidth = jo.getNumber("tileWidth")
        self.tileHeight = jo.getNumber("tileHeight")
        self.tilesets = jo.getObjectsByVtable("tilesets", Tileset)
        self.layers = jo.getObjectsByVtable("layers", TileLayer)

    }
    void toJson(Json *jo){
        jo.putNumber("width", self.width)
        jo.putNumber("height", self.height)
        jo.putNumber("tileWidth", self.tileWidth)
        jo.putNumber("tileHeight", self.tileHeight)

        jo.put("tilesets", Json_toJson(self.tilesets))
        jo.put("layers", Json_toJson(self.layers))
    }


    void ctor(){
        // for int i = 0; i < 3; i++{
        //     TileLayer@ layer = new TileLayer()
        //     layer.data.initSize(self.width * self.height)

        //     layer.name.set("图层")
        //     layer.name.addi(i)
        //     self.layers.add(layer)
        // }

        {
            Tileset@ layer = new Tileset()
            layer.imgPath.set("../asset/DungeonTileset/dungeon.png")
            self.tilesets.add(layer)
        }
    }

    Tileset* findTilesetByGid(int gid){
        int l = self.tilesets.size()
        for int i = 0; i < l; i++{
            Tileset* ts = (Tileset*)self.tilesets.get(i)
            if ts.isGidBelong(gid){
                return ts
            }
        }
        return null
    }

    int findFreeStartGid(){
        //从1m开始
        for int i = 1; i < 200; i++{
            int startGid = i * 1000000;
            bool found = false
            for int j = 0; j < self.tilesets.size(); j++{
                Tileset* ts = (Tileset*)self.tilesets.get(j)
                if ts.startGid == startGid {
                    found = true
                    break;
                }
            }
            if !found {//空闲
                return startGid;
            }
        }
        return -1
    }
}

class ElapsedMs {
    long long prevMs = 0
    long long accumMs = 0

    void tick(){
        long long nowMs = Time_unixMs()
        if self.prevMs == 0 {
            self.accumMs = 0
        } 
        else {
            self.accumMs += nowMs - self.prevMs
        }
        self.prevMs = nowMs
    }
    long long calcFrameIndex(int fps){
        double frameIndex = self.accumMs / (1000L / (double)fps)
        return frameIndex
    }
}

class TileMapEditView extends ViewBase {
    TileMap@ map = null;
    ViewBase@ viewportView = null


    //相对于viewportView的坐标
    Vec2 mousePosInViewport
    SceneCtrl@ sceneCtrl = null
    TileEditor@ tileEditor = null

    Drag@ drag = new Drag()
    ElapsedMs@ elapsedMs = new ElapsedMs()

    void ctor(){
        self.drag.onDrag = ^void (Drag *d){
            if d.isDragging{
                printf("dragging\n")

                Vec2 gridPos = self.calcMouseGridPos()
                self.setTileAtGrid(gridPos)
            }
        }
    }


    Vec2 getMouseScenePos(){
        Vec2 clientPos = Mouse_getPosOfWindow(self.ownerWindow)
        self.mousePosInViewport = self.viewportView.worldToLocal(clientPos.x, clientPos.y)
        Vec2 scenePos = self.sceneCtrl.worldToLocal(self.mousePosInViewport.x, self.mousePosInViewport.y)
        return scenePos
    }

    void setTileAtGrid(Vec2 gridPos){
        if self.tileEditor == null || self.tileEditor.curLayer == null 
            || self.tileEditor.curTileset == null
            || self.tileEditor.curTilePosArr.size == 0
            // .x < 0 
            // || self.tileEditor.curTilePos.y < 0 
        {
            printf("参数异常，无法设置tile\n");
            return
        }

        Layer* layer = self.tileEditor.curLayer
        if !(layer instanceof TileLayer) {
            printf("当前layer不是TileLayer\n");
        }
        TileLayer* tileLayer = (TileLayer*)layer
        Vec2 firstPos = self.tileEditor.curTilePosArr.data[0]
        for int i = 0; i < self.tileEditor.curTilePosArr.size; i++{
            Vec2 tilePos = self.tileEditor.curTilePosArr.data[i]
            Vec2 offset = tilePos.sub(firstPos)
            Vec2 curGridPos = gridPos.add(offset)

            int cellIndex = self.gridPosToCellIndex(curGridPos)
            if cellIndex >= 0 {
                int gid = self.tileEditor.curTileset.calcGid(
                    tilePos
                )
                
                SpecialTile* st = self.tileEditor.curTileset.getSpecialTileAtGid(gid)
                if st {
                    st.setTileAtGid(
                        self.tileEditor, 
                        tileLayer, self.tileEditor.curTileset, gid, cellIndex
                    )
                }
                else {
                    printf("set tile: cellIndex:%d, gid:%d\n", cellIndex, gid)
                    tileLayer.data.set(cellIndex, gid)
                }
            }
        }
    }

    int gridPosToCellIndex(Vec2 gridPos){
        if self.tileEditor && self.tileEditor.map{
            int idx = self.tileEditor.map.width * gridPos.y + gridPos.x
            return idx
        }
        return -1
    }


    // 视口事件
    // return true if processed
    bool onViewportEvent(Event *e){
        if e instanceof MouseEnterEvent {
            printf("鼠标进入事件\n")
            self.setHover(true)
        }
        if e instanceof MouseLeaveEvent {
            self.setHover(false)
            printf("鼠标离开事件\n")
        }
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e;
            if self.viewportView {
                self.mousePosInViewport = self.viewportView.worldToLocal(me.clientX, me.clientY)
            }

            if me.button == 1 && me.isMouseDown {
                self.drag.onMouseDown(me)
            }

            if me.button == 1 && me.isClickInBubble(){
                Vec2 scenePos = self.sceneCtrl.worldToLocal(self.mousePosInViewport.x, self.mousePosInViewport.y)
                Vec2 gridPos = self.calcMouseGridPos()

                self.setTileAtGrid(gridPos)

                printf("\nclient pos:%d,%d  down:%d,%d,%d,%d.  mousePosInViewport:%f,%f. scenePos:%f,%f. gridPos:%f,%f\n", 
                    me.clientX, me.clientY,
                    me.isMouseDown,
                    me.isMouseUp,
                    me.isMouseMove,
                    me.isWheel,
                    self.mousePosInViewport.x,
                    self.mousePosInViewport.y,
                    scenePos.x,
                    scenePos.y,
                    gridPos.x,
                    gridPos.y,
                );
                // Toast_make("hi")
                return true
            }
        }
        return false
    }
    //计算当前鼠标所在的网格
    Vec2 calcMouseGridPos(){
        Vec2 pos = self.getMouseScenePos()
        int tilew = self.map.tileWidth
        int tileh = self.map.tileHeight
        //绘制tile
        int col = pos.x / tilew
        int row = pos.y / tileh
        printf("calcMouseGridPos. pos:%f,%f, tilew:%d,%d, grid:%d,%d\n", pos.x, pos.y, tilew, tileh, col, row);

        return mkVec2(col, row)
    }
    void draw_tileLayer(Canvas *canvas, TileLayer *layer){
        long long frame = self.elapsedMs.calcFrameIndex(self.map.fps)
        // printf("frame:%lld accumMs:%lld\n", frame, self.elapsedMs.accumMs)

        int w = self.map.width
        int h = self.map.height
        int tilew = self.map.tileWidth
        int tileh = self.map.tileHeight
        for int r = 0; r < h; r++{
            for int c = 0; c < w; c++{
                int cell = r * self.map.width + c
                int gid = layer.data.at(cell)
                if gid != 0 {
                    Tileset *ts = self.map.findTilesetByGid(gid)
                    if ts {
                        int drawGid = gid


                        SpecialTile *st = ts.getSpecialTileAtGid(gid)
                        if st {
                            if st instanceof AnimTile {
                                AnimTile *at = (AnimTile*)st
                                drawGid = at.getDrawGid(frame)
                                // printf("drawGid:%d\n", drawGid)
                            }
                        }



                        Image* img = ts.loadImage()
                        if img {
                            int x = c * tilew
                            int y = r * tileh

                            Vec2 tileGridPos = ts.dissolveGidToGridPos(drawGid)
                            int tileX = tileGridPos.x * tilew
                            int tileY = tileGridPos.y * tileh

                            canvas.drawImageAtRect(
                                img,
                                tileX, tileY,
                                tilew, tileh,
                                x, y, 
                                tilew, tileh,
                                1, 
                            )
                        }
                    }
                }
            }
        }
    }
    void draw_map(Canvas *canvas){
        if self.map{
            self.elapsedMs.tick()


            int l = self.map.layers.size()
            for int i = 0; i < l; i++{
                Layer* layer = (Layer*)self.map.layers.get(i)
                if layer instanceof TileLayer {
                    self.draw_tileLayer(canvas, (TileLayer*)layer)
                }
            }
        }
    }
    void draw_self(Canvas *canvas){

        // canvas.fillColorByInt32(0xff000033)
        // canvas.strokeColorByInt32(0xffff0033)
        // canvas.strokeWidth(10)
        // canvas.beginPath()

        // canvas.rect(10, 10, 100, 100)
        // canvas.fill()
        // if self.hover {
        //     canvas.stroke()
        // }
        self.draw_map(canvas)

        //画线
        if self.map{

            if self.hover {
                Vec2 pos = self.getMouseScenePos()
                //中心线
                if 0 {
                    canvas.beginPath()
                    canvas.moveTo(pos.x - 10000, pos.y)
                    canvas.lineTo(pos.x + 10000, pos.y)

                    canvas.moveTo(pos.x, pos.y - 10000)
                    canvas.lineTo(pos.x, pos.y + 10000)
                    canvas.strokeWidth(1)
                    canvas.strokeColorByInt32(0xffff0000)
                    canvas.stroke()
                }

                int tilew = self.map.tileWidth
                int tileh = self.map.tileHeight
                //绘制tile
                int col = pos.x / tilew
                int row = pos.y / tileh

                int radius = 3
                //画线
                {
                    canvas.strokeWidth(1)
                    //水平线
                    for int r = -radius; r <= radius; r++{
                        int x = maxInt(col + -radius, 0) * tilew
                        int x2 = minInt(col + radius, self.map.width) * tilew


                        int y = clampInt(row + r, 0, self.map.height) * tileh

                        canvas.beginPath()
                        canvas.strokeColorByInt32(0xffff0000)
                        canvas.moveTo(x, y)
                        canvas.lineTo(x2, y)
                        canvas.stroke()
                    }
                    //垂直线
                    for int r = -radius; r <= radius; r++{
                        int y = maxInt(row + -radius, 0) * tileh
                        int y2 = minInt(row + radius, self.map.height) * tileh
                        int x = clampInt(col + r, 0, self.map.width) * tilew

                        canvas.beginPath()
                        canvas.strokeColorByInt32(0xffff0000)
                        canvas.moveTo(x, y)
                        canvas.lineTo(x, y2)
                        canvas.stroke()
                    }
                }

                // for int r = -radius; r <= radius; r++{
                //     for int c = -radius; c <= radius; c++{
                //         int x = (col + c) * tilew
                //         int y = (row + r) * tileh

                //         // canvas.beginPath()
                //         // canvas.rect(x, y, tilew - 5, tileh - 5)
                //         // canvas.fillColorByInt32(0x9900ff00)
                //         // canvas.fill()
                //     }
                // }

            }
        }

    }
}

TileMapEditView@ mkTileMapEditView(void* parent, long long key){
    return (TileMapEditView@)gocNode(
        key ? (void *)key : __builtin_return_address(0) , 
        (Node*)parent, TileMapEditView)
}

class SceneViewCb extends ChessBgViewCallback {
    SceneCtrl@ ctrl = null
    // 如果返回true,会屏蔽原来的draw_self
    void afterDrawSelf(View *div, Canvas *canvas){
        if self.ctrl {
            Rect r = div.getViewRect();
            self.ctrl.degree.draw(canvas, self.ctrl.mat, r.w, r.h, 0, 0)
        }
    }
}

class SceneCtrl {
    Vec3 _translate;
    float _scale = 1;
    Mat2d mat = mkMat2d()//最终生成的矩阵

    Drag@ drag = new Drag()
    DrawDegree@ degree = new DrawDegree()
    View@ contentView = null
    SceneViewCb@ sceneViewCb = new SceneViewCb()

    void ctor(){
        self.sceneViewCb.ctrl = self
        self.drag.onDrag = ^void(Drag *d){
            if d.isDragging {
                self.translate(d.deltaPos.x, d.deltaPos.y, 0)
                if self.contentView {
                    self.contentView.transform = self.mat
                }
                printf("SceneCtrl.onDragging\n");
                
                // self.imgCell.left += d.deltaPos.x
                // self.imgCell.top += d.deltaPos.y

                // self.invalidReact.invalid()
            }
        }
    }
    bool onEvent(Event *e){
        if e instanceof WheelEvent {
            WheelEvent *we = (WheelEvent *)e;
            if we.isCapture {
                Node* parent = self.contentView.parent
                if parent instanceof ViewBase {
                    self.performScaleByWheelEventAndSceneView(
                        we, parent
                    )
                    return true
                }
            }
        }
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e;
            if me.button == 3 && me.isBubble() && me.isMouseDown {
                self.drag.onMouseDown(me)
                return true
            }
        }

        return false
    }

    void setScale(float s){
        self._scale = s
        self.updateMat()
    }

    void updateMat(){
        self.mat.identity()
        self.mat.translate(
            self._translate.x,
            self._translate.y,
            self._translate.z,
        )
        self.mat.scale(
            self._scale,
            self._scale,
            self._scale,
        )
    }
    Vec2 localToWorld(float x, float y){
        Vec2 ret = mkVec2(0,0);
        Vec3 p = self.mat.transformPoint(x, y, 0.f);
        ret.x = p.x
        ret.y = p.y
        return ret
    }

    Vec2 worldToLocal(float x, float y){
        Vec2 ret = mkVec2(0,0);
        Mat2d inv = self.mat;//.copy()
        inv.inverse()

        Vec3 p = inv.transformPoint(x, y, 0.f);
        ret.x = p.x
        ret.y = p.y
        return ret
    }

    // 客户区坐标（相对于窗口
    Vec2 clientToWorld(float x, float y){
        if !self.contentView {
            return mkVec2(0, 0)
        }
        ViewBase *viewportView = self.contentView.parent
        Vec2 viewPos = viewportView.worldToLocal(x, y)
        return viewPos;
    }
    // 客户区坐标（相对于窗口
    Vec2 clientToLocal(float x, float y){
        if !self.contentView {
            return mkVec2(0, 0)
        }
        Vec2 worldPos = self.clientToWorld(x,  y)
        Vec2 localPos = self.worldToLocal(worldPos.x, worldPos.y)
        return localPos;
    }


    void translate(float x, float y, float z){
        self._translate = self._translate.add3f(x, y, z)
        self.updateMat()
    }
    void setTranslate(float x, float y, float z){
        self._translate.set(x, y, z)
        self.updateMat()
    }
    void identity(){
        self._translate.set(0, 0, 0)
        self._scale = 1
        self.updateMat() 
    }

    void performScaleByWheelEventAndSceneView(
        WheelEvent* we,
        ViewBase* v
    ){
        Vec2 viewPos = v.worldToLocal(we.clientX, we.clientY)
        Mat2d invMat = self.mat.inverseNew()
        Vec3 scenePos = invMat.transformPoint(viewPos.x, viewPos.y, 0)

        // float s = self._scale
        // float nextScale = maxFloat(0.01, self._scale + (we.deltaY > 0 ? 1 : -1) * 0.1)
        // int idx = v.degree.levelOptions.indexOf(v.degree.curOption)
        // int nextIdx = minInt(maxInt(0, idx + (we.deltaY > 0 ? 1 : -1)), v.degree.levelOpotions.size() - 1)
        // // DrawDegreeItem@ opt = v.degree.findAndUpdateCurOption(nextScale)
        // self.setScale(opt.value)
        DrawDegreeItem@ opt = self.degree.findAndReturnOffset(self._scale, we.deltaY > 0 ? 1 : -1)
        self.degree.curOption = opt
        self.degree.curScale = opt.value
        self.setScale(opt.value)


        Vec3 newViewPos = self.mat.transformPoint(scenePos.x, scenePos.y, 0)
        printf("scale. client:%d,%d, viewPos:%f,%f, scenePos:%f,%f,newViewPos:%f,%f, delta:%f,%f\n",
            we.clientX, 
            we.clientY, 
            viewPos.x,
            viewPos.y,
            scenePos.x,
            scenePos.y,
            newViewPos.x,
            newViewPos.y,
            viewPos.x - 
            newViewPos.x,
            viewPos.y - 
            newViewPos.y,
        )
        self.translate(
            viewPos.x - 
            newViewPos.x,
            viewPos.y - 
            newViewPos.y,
            0,
        )
        if self.contentView {
            self.contentView.transform = self.mat
        }

        printf("wheel. result:%f opt:%f,degree:%f\n", 
            self._scale, opt.value, opt.degree);
    }
}


static DockLayout@ dockLayoutIns = null

class TileEditor{
    Window@ win

    LayoutAlignPositionCell@ imgCell
    LayoutAlignPositionCell@ previewCell

    InvalidReact@ invalidReact  = mkInvalidReact(self)

    String@ path = str("../build/././a.tilemap.json")


    TileMap@ map = new TileMap()

    Layer@ curLayer = null
    Tileset@ curTileset = null

    //当前编辑中的AutoTile
    AutoTile@ editingAutoTile = null

    // tile|editingAutoTile
    String@ tilesetStatus = str("tile")


    SceneCtrl@ tilesetSceneCtrl = new SceneCtrl()
    SceneCtrl@ sceneCtrl = new SceneCtrl()
    // String@ curTileKey = str("")
    TileMapEditView@ tileMapEditView = null

    Vec2Array@ curTilePosArr = new Vec2Array();// = mkVec2(-1, -1)

    Drag@ tilesetDrag = new Drag()

    void editAutoTile(AutoTile* at){
        if at {
            self.tilesetStatus.set("editingAutoTile")
        }
        else {
            self.tilesetStatus.set("tile")
        }
        self.editingAutoTile = at;
        self.invalidReact.invalid()
    }


    void printSceneTree(){
        // printNodeTree(self.sceneImageView, 0)
    }

    int getFrameIndex(int x, int y){
        return -1
    }

    void ctor(){
        // self.curTilePosArr = mkVec2(-1, -1)
        self.tilesetDrag.onDrag = ^ void (Drag *d){
            if d.isDragging {
                printf("isDragging tileset\n")

                //拖拽选中rule 
                if self.tilesetStatus.equals("editingAutoTile"){
                    Vec2 localPos = self.tilesetSceneCtrl.clientToLocal(d.currentClientPos.x, d.currentClientPos.y)

                    Tileset *ts = self.curTileset
                    float cw = self.map.tileWidth / 3.0
                    float ch = self.map.tileHeight / 3.0
                    int x = localPos.x / cw
                    int y = localPos.y / ch
                    int neighborId = y * ts.cols * 3 + x;

                    // if !self.editingAutoTile.neighborIdArr.has(neighborId){
                    //     self.editingAutoTile.neighborIdArr.append(neighborId)
                    //     self.invalidReact.invalid()
                    // }
                    self.editingAutoTile.neighborIdArr.{
                        if !o.has(neighborId){
                            o.append(neighborId)
                            printf("add neighborId:%d\n", neighborId);
                            self.invalidReact.invalid()
                        }
                        else {
                            printf("neighborId exist:%d\n", neighborId);
                        }
                    }

                    printf("localPos:%f,%f. grid:%d,%d. neighborIdArr size:%d. nid:%d\n", 
                        localPos.x, localPos.y, x, y,

                        self.editingAutoTile.neighborIdArr.size,
                        neighborId,
                    )
                }
            }
        }
       
    }
    

    ChessBgViewCallback@ chessBg= new ChessBgViewCallback()


    void ui_addtileset(){
        String@ abspath = Path_toAbsolute(self.path.str)
        // printf("abspath:%s\n", abspath.str)
        printf("cwd:%s\n", Path_getcwd().str)
        List@ paths = FileDialog_getOpenFileName("./", "选择图片")
        printf("after cwd:%s\n", Path_getcwd().str)
        for int i = 0; i < paths.size(); i++{
            String* s = (String*)paths.get(i)

            String@ relpath = Path_relPathToFile(s.str, abspath.str)
            printf("选择了图片:%s, rel:%s\n", s.str, relpath.str)

            Tileset@ ts = new Tileset()
            ts.imgPath.set(relpath.str)
            ts.startGid = self.map.findFreeStartGid()
            self.map.tilesets.add(ts)
        }
        self.invalidReact.invalid()
    }
    void addTileLayer(){
        TileLayer@ layer = new TileLayer()
        layer.data.initSize(self.map.width * self.map.height)

        layer.name.set("图层")
        layer.name.addi(self.map.layers.size())
        self.map.layers.add(layer)
        self.invalidReact.invalid()
    }
    void delLayer(Layer* layer){
        self.map.layers.remove(layer)
        self.invalidReact.invalid()
    }


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

    void showDialog_renameLayer(Layer@ layer){
                                            // Toast_make(anim.name.str)
        MessageDialog_prompt(layer.name.str, "重命名", ^void (String@ newValue) {
            layer.name = newValue
            self.invalidReact.invalid()
        })
    }
    ViewBase* reactTilesetsNames(Node* o, DockItem *item){
        mkScrollArea(o, (long long)item).{
            o.backgroundColor = 0x33ff00ff
            o.useMinWidthConstraint = true
            o.alignItems .set("stretch")
            // o.width = 10
            // o.height = 10

            layoutLinearCell(o, 0)

            layoutLinear(o, (long long)item).{
                o.direction.set("column")
                o.alignItems.set("maxOrStretch")
                // o.backgroundColor = 0x33ff00ff

                for int i = 0; i < self.map.tilesets.size(); i++{
                    Tileset* tileset = (Tileset*)self.map.tilesets.get(i)
                    mkTextView(o, (long long)tileset).{
                        o.setText(tileset.imgPath)
                        o.cursor.set("pointer")


                        mkHoverViewEffect(o, 0).{
                            o.hoverBorder.setAll(1, 0x00000000)
                            o.activeBorder.setAll(1, 0x00000000)
                            o.backgroundColor = i% 2 == 0 ? 0x00ffff00: 0x33ffffff
                            o.hoverBackgroundColor = 0x33ff0000
                            o.activeBackgroundColor = 0x66ff0000
                            o.isActive = self.curTileset == tileset

                            o.onHostEvent = ^bool (Event *e){
                                MouseEvent *me = (MouseEvent*)e
                                if me.button == 3 && me.isClickInBubble() {
                                    ^void onActive(MenuNativeItem *item){
                                        if item.cmd.equals("重命名"){
                                            // self.showDialog_rename(anim)
                                        }
                                        if item.cmd.equals("删除"){
                                        }
                                    }
                                    mkMenuNativeItem(null, str(""), onActive).{
                                        mkMenuNativeItem(o, str("重命名"), onActive).{ }
                                        mkMenuNativeItem(o, str("删除"), onActive).{ }

                                        MenuNative@ n = new MenuNative()
                                        n.create(o)
                                        n.showAtMouse()
                                    }
                                    return true
                                }

                                return false;
                            }

                            o.onClick = ^void(MouseEvent*me){
                                // self.curAnim = anim
                                self.curTileset = tileset
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
    ViewBase* reactLayers(Node* o, DockItem *item){
        mkScrollArea(o, (long long)item).{
            o.backgroundColor = 0x33ff00ff
            o.useMinWidthConstraint = true
            o.alignItems .set("stretch")
            // o.width = 10
            // o.height = 10

            layoutLinearCell(o, 0)

            layoutLinear(o, (long long)item).{
                o.direction.set("column")
                o.alignItems.set("maxOrStretch")
                o.backgroundColor = 0x33ff00ff

                for int i = 0; i < self.map.layers.size(); i++{
                    Layer* layer = (Layer*)self.map.layers.get(i)
                    mkTextView(o, (long long)layer).{
                        o.setText(layer.name)
                        o.cursor.set("pointer")


                        mkHoverViewEffect(o, 0).{
                            o.hoverBorder.setAll(1, 0x00000000)
                            o.activeBorder.setAll(1, 0x00000000)
                            o.backgroundColor = i% 2 == 0 ? 0x00ffff00: 0x33ffffff
                            o.hoverBackgroundColor = 0x33ff0000
                            o.activeBackgroundColor = 0x66ff0000
                            o.isActive = self.curLayer == layer

                            o.onHostEvent = ^bool (Event *e){
                                MouseEvent *me = (MouseEvent*)e
                                if me.button == 3 && me.isClickInBubble() {
                                    ^void onActive(MenuNativeItem *item){
                                        if item.cmd.equals("重命名"){
                                            self.showDialog_renameLayer(layer)
                                        }
                                        if item.cmd.equals("删除") {
                                            self.delLayer(layer)
                                        }
                                    }
                                    mkMenuNativeItem(null, str(""), onActive).{
                                        mkMenuNativeItem(o, str("重命名"), onActive).{ }
                                        mkMenuNativeItem(o, str("删除"), onActive).{ }

                                        MenuNative@ n = new MenuNative()
                                        n.create(o)
                                        n.showAtMouse()
                                    }
                                    return true
                                }

                                return false;
                            }

                            o.onClick = ^void(MouseEvent*me){
                                self.curLayer = layer
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
            o.cb  = self.sceneCtrl.sceneViewCb 
            o.cbOnEvent = ^void(Event*e){
                if self.sceneCtrl.onEvent(e){
                    return
                }
                if self.tileMapEditView {
                    if self.tileMapEditView.onViewportEvent(e){
                        return
                    }
                }
                if e instanceof MouseEvent {
                    MouseEvent *me = (MouseEvent*)e;
                }
            }

            layoutLinearCell(o, 0)


            layoutAlign(o, 0).{
                o.useMaxConstraint = false
                self.sceneCtrl.contentView = o

                mkTileMapEditView(o, 0).{
                    o.map = self.map
                    o.tileEditor = self
                    o.sceneCtrl = self.sceneCtrl
                    o.viewportView =  (ViewBase*)self.sceneCtrl.contentView.parent

                    self.tileMapEditView = o
                }

                // mkImageView(o, 0).{
                //     o.border.setAll(1, 0xffff0000)
                //     o.setSrc(str("../asset/AnimationSheet_Character.png"))

                //     self.sceneImageView = o


                //     layoutAlignPositionCell(o, 0).{
                //         self.imgCell = o
                //         // o.left = 100
                //         // o.top = 100
                //     }

                //     int w = o._img.width()
                //     int h = o._img.height()
                //     o.width = w
                //     o.height = w
                // }
            }

            // printNodeTree(o, 0)
            return o
        }
    }
    ViewBase* reactTilesetView(Node*o, DockItem*item){
        layoutAlign(o, (long long)item).{
            layoutLinearCell(o, 0)

            o.useMaxConstraint = false
            o.needClip = true
            o.cb  = self.tilesetSceneCtrl.sceneViewCb 
            o.cbOnEvent = ^void(Event*e){
                if self.tilesetSceneCtrl.onEvent(e){
                    return
                }

                if e instanceof MouseEvent {
                    MouseEvent *me = (MouseEvent*)e;
                    if me.button == 3 && me.isBubble() && me.isMouseDown {
                        // self.tilesetSceneCtrl.drag.onMouseDown(me)
                    }
                }

            }

            if self.curTileset {
                Tileset *ts = self.curTileset
                printf("react TilesetView:%s\n", ts.imgPath.str)
                layoutAlign(o, 0).{
                    o.useMaxConstraint = false
                    self.tilesetSceneCtrl.contentView = o

                    mkImageView(o, 0).{
                        // o.border.setAll(1, 0xffff0000)
                        o.setSrc(ts.imgPath)

                        o.cbOnEvent = ^void (Event *e){
                            if e instanceof MouseEvent {
                                MouseEvent *me = (MouseEvent*)e;
                                if me.button == 1 && me.isCapture {
                                    self.tilesetDrag.onMouseDown(me)
                                }
                            }
                        }


                        layoutAlignPositionCell(o, 0).{
                            // self.imgCell = o
                            // o.left = 100
                            // o.top = 100
                        }

                        int w = o._img.width()
                        int h = o._img.height()
                        o.width = w
                        o.height = h

                        ts.calcRowsCols(
                            o._img.size(),
                            self.map.tileWidth,
                            self.map.tileHeight,
                        )

                        int colw = self.map.tileWidth
                        int rowh = self.map.tileHeight
                        
                        //行线
                        for int i = 0; 1&&i <= ts.rows; i++{
                            mkView(o, 1000+i).{
                                o.name  = str("rowLine:").addi(i)
                                o.frame.y = i * self.map.tileHeight
                                o.backgroundColor = 0xffff0000
                                o.height = 1
                                o.width = w
                            }
                        }
                        //列线
                        for int i = 0; 1&& i <= ts.cols; i++{
                            mkView(o, 2000+i).{
                                o.name  = str("colLine:").addi(i)
                                o.frame.x = i * self.map.tileWidth
                                o.backgroundColor = 0xffff0000
                                o.width = 1
                                o.height = h
                            }
                        }


                        if self.tilesetStatus.equals("tile"){
                            //格子
                            for int y = 0; y < ts.rows; y++{
                                for int x = 0; x < ts.cols; x++{
                                    Vec2 tilePos = mkVec2(x, y)
                                    String@ key = str("cell:").addi(x).add(",").addi(y)
                                    mkView(o, 30000+y * 100 + x).{
                                        o.name  = key
                                        o.frame.x = x * colw
                                        o.frame.y = y * rowh
                                        o.width = colw
                                        o.height = rowh
                                        o.frame.width = colw
                                        o.frame.height = rowh

                                        // o.cb = self.viewCb

                                        // int frameIndex = self.getFrameIndex(x, y)

                                        mkHoverViewEffect(o, 0).{
                                            o.hoverBorder.setAll(1, 0x00000000)
                                            o.activeBorder.setAll(1, 0x00000000)
                                            o.backgroundColor = 0x00ff0000
                                            o.hoverBackgroundColor = 0x33ff0000
                                            o.activeBackgroundColor = 0x66ff0000
                                            // o.isActive = self.curTileKey.equals(key.str)
                                            o.isActive = self.curTilePosArr.has(tilePos)//.x == x && self.curTilePos.y == y
                                            o.onClick = ^void(MouseEvent*me){
                                                if me.ctrl {
                                                    if !self.curTilePosArr.has(tilePos){
                                                        self.curTilePosArr.add(tilePos )
                                                    }
                                                }
                                                else if me.shift {
                                                    if self.curTilePosArr.size == 0{
                                                        self.curTilePosArr.add(tilePos )
                                                    }
                                                    else {
                                                        Vec2 start = self.curTilePosArr.data[0]
                                                        self.curTilePosArr.clear()
                                                        for int y = start.y; y <= tilePos.y; y++{
                                                            for int x = start.x; x <= tilePos.x; x++{
                                                                self.curTilePosArr.add(mkVec2(x, y))
                                                            }
                                                        }
                                                    }

                                                }
                                                else {
                                                    self.curTilePosArr.clear()
                                                    self.curTilePosArr.add(tilePos )
                                                }
                                                // self.curTilePos = tilePos
                                                // self.curTileKey = key

                                                self.invalidReact.invalid()
                                                // o.isActive = !o.isActive 
                                                // o.react()
                                            }
                                        }
                                    }


                                }
                            }
                        }

                        if self.tilesetStatus.equals("editingAutoTile"){
                            float cw = colw / 3.0
                            float ch = rowh / 3.0
                            float neighborRows = ts.rows * 3
                            float neighborCols = ts.cols * 3
                            //格子
                            for int y = 0; y < neighborRows; y++{
                                for int x = 0; x < neighborCols; x++{
                                    Vec2 tilePos = mkVec2(x, y)
                                    int neighborId = y * neighborCols + x;

                                    String@ key = str("cell:").addi(x).add(",").addi(y)
                                    mkView(o, 30000+y * 100 + x).{
                                        o.name  = key
                                        o.frame.x = x * cw
                                        o.frame.y = y * ch
                                        o.width = cw
                                        o.height = ch
                                        o.frame.width = cw
                                        o.frame.height = ch

                                        // o.cb = self.viewCb

                                        // int frameIndex = self.getFrameIndex(x, y)

                                        mkHoverViewEffect(o, 0).{
                                            o.hoverBorder.setAll(1, 0x00000000)
                                            o.activeBorder.setAll(1, 0x00000000)
                                            o.backgroundColor = 0x00ff0000
                                            o.hoverBackgroundColor = 0x33ff0000
                                            o.activeBackgroundColor = 0x66ff0000
                                            // o.isActive = self.curTileKey.equals(key.str)
                                            o.isActive = self.editingAutoTile.neighborIdArr.has(neighborId) //.x == x && self.curTilePos.y == y
                                            o.onClick = ^void(MouseEvent*me){
                                                self.editingAutoTile.neighborIdArr.{
                                                    printf("onclick neighbor cell. neighborId:%d\n", neighborId);
                                                    if o.has(neighborId){
                                                        printf(" remove neighbor cell. neighborId:%d\n", neighborId);
                                                        o.removeFirst(neighborId)
                                                    }
                                                    else {
                                                        printf(" append neighbor cell. neighborId:%d\n", neighborId);
                                                        o.append(neighborId)
                                                    }
                                                }

                                                self.invalidReact.invalid()
                                            }
                                        }
                                    }


                                }
                            }
                        }
                        //特殊tile
                        {
                            for int i = 0; i < self.curTileset.specialTiles.size(); i++{
                                SpecialTile@ st = (SpecialTile@)self.curTileset.specialTiles.get(i)
                                int gid = st.getGid()
                                if gid == -1 {
                                    continue
                                }
                                Vec2 pos = self.curTileset.dissolveGidToGridPos(gid)
                                int x = (int)pos.x
                                int y = (int)pos.y
                                if st instanceof RandomTile {
                                    RandomTile *rt = (RandomTile*)st;
                                    mkView(o, 40000+y * 100 + x).{
                                        // o.name  = key
                                        o.border.setAll(1, 0xffffffff)
                                        o.frame.x = x * colw + 3
                                        o.frame.y = y * rowh + 3
                                        o.width = colw / 4
                                        o.height = rowh / 4

                                        o.backgroundColor = 0x88ffff00
                                        o.cbOnEvent = ^void (Event*e){
                                            if e instanceof MouseEvent {
                                                MouseEvent *me = (MouseEvent*)e
                                                if me.button == 3 && me.isClickInBubble(){
                                                    ^void onActive(MenuNativeItem *item){
                                                        if item.cmd.equals("删除RandomTile"){
                                                            self.curTileset.specialTiles.remove(st)
                                                            self.invalidReact.invalid()
                                                            Toast_make("已删除RandomTile")
                                                            return
                                                        }
                                                        Toast_make(item.cmd.str)
                                                    }
                                                    mkMenuNativeItem(null, str(""), onActive).{
                                                        mkMenuNativeItem(o, str("删除RandomTile"), onActive).{ }

                                                        MenuNative@ n = new MenuNative()
                                                        n.create(o)
                                                        n.showAtMouse()
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    // 当前选中了RandomTile
                                    bool isActive = self.curTilePosArr.has(pos)
                                    if isActive {
                                        for int j = 1; j < rt.gidArr.size; j++{
                                            int gid = rt.gidArr.get(j)
                                            Vec2 pos = self.curTileset.dissolveGidToGridPos(gid)
                                            int x = (int)pos.x
                                            int y = (int)pos.y
                                            mkView(o, 50000+y * 100 + x).{
                                                // o.name  = key
                                                // o.border.setAll(1, 0xffffffff)
                                                o.frame.x = x * colw + 3
                                                o.frame.y = y * rowh + 3
                                                o.width = 4
                                                o.height = 4

                                                o.backgroundColor = 0x88ffff00
                                            }
                                        }
                                    }
                                }

                                else if st instanceof AnimTile {
                                    AnimTile *rt = (AnimTile*)st;
                                    mkView(o, 40000+y * 100 + x).{
                                        // o.name  = key
                                        o.border.setAll(1, 0xffffffff)
                                        o.frame.x = x * colw + 3
                                        o.frame.y = y * rowh + 3
                                        o.width = colw / 4
                                        o.height = rowh / 4

                                        o.backgroundColor = 0x88ff00ff
                                        o.cbOnEvent = ^void (Event*e){
                                            if e instanceof MouseEvent {
                                                MouseEvent *me = (MouseEvent*)e
                                                if me.button == 3 && me.isClickInBubble(){
                                                    ^void onActive(MenuNativeItem *item){
                                                        if item.cmd.equals("删除AnimTile"){
                                                            self.curTileset.specialTiles.remove(st)
                                                            self.invalidReact.invalid()
                                                            Toast_make("已删除AnimTile")
                                                            return
                                                        }
                                                        Toast_make(item.cmd.str)
                                                    }
                                                    mkMenuNativeItem(null, str(""), onActive).{
                                                        mkMenuNativeItem(o, str("删除AnimTile"), onActive).{ }

                                                        MenuNative@ n = new MenuNative()
                                                        n.create(o)
                                                        n.showAtMouse()
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    // 当前选中了RandomTile
                                    bool isActive = self.curTilePosArr.has(pos)
                                    if isActive {
                                        for int j = 1; j < rt.gidArr.size; j++{
                                            int gid = rt.gidArr.get(j)
                                            Vec2 pos = self.curTileset.dissolveGidToGridPos(gid)
                                            int x = (int)pos.x
                                            int y = (int)pos.y
                                            mkView(o, 50000+y * 100 + x).{
                                                // o.name  = key
                                                // o.border.setAll(1, 0xffffffff)
                                                o.frame.x = x * colw + 3
                                                o.frame.y = y * rowh + 3
                                                o.width = 4
                                                o.height = 4

                                                o.backgroundColor = 0x88ff00ff
                                            }
                                        }
                                    }
                                }

                                else if st instanceof AutoTile {
                                    AutoTile @rt = (AutoTile@)st;
                                    mkView(o, 40000+y * 100 + x).{
                                        // o.name  = key
                                        o.border.setAll(1, 0xffffffff)
                                        o.frame.x = x * colw + 3
                                        o.frame.y = y * rowh + 3
                                        o.width = colw / 4
                                        o.height = rowh / 4

                                        o.backgroundColor = 0x8800ffff
                                        o.cbOnEvent = ^void (Event*e){
                                            if e instanceof MouseEvent {
                                                MouseEvent *me = (MouseEvent*)e
                                                if me.button == 3 && me.isClickInBubble(){
                                                    ^void onActive(MenuNativeItem *item){
                                                        if item.cmd.equals("删除AutoTile"){
                                                            self.curTileset.specialTiles.remove(st)
                                                            self.invalidReact.invalid()
                                                            Toast_make("已删除AutoTile")
                                                            return
                                                        }
                                                        if item.cmd.equals("编辑规则"){
                                                            self.editAutoTile(rt)
                                                            return
                                                        }
                                                        if item.cmd.equals("退出编辑规则"){
                                                            self.editAutoTile(null)
                                                            return
                                                        }
                                                        Toast_make(item.cmd.str)
                                                    }
                                                    mkMenuNativeItem(null, str(""), onActive).{
                                                        mkMenuNativeItem(o, str("删除AutoTile"), onActive).{ }
                                                        mkMenuNativeItem(o, str("编辑规则"), onActive).{ }
                                                        mkMenuNativeItem(o, str("退出编辑规则"), onActive).{ }

                                                        MenuNative@ n = new MenuNative()
                                                        n.create(o)
                                                        n.showAtMouse()
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    // 当前选中了AutoTile
                                    bool isActive = self.curTilePosArr.has(pos)
                                    if isActive && self.tilesetStatus.equals("tile") {//在普通状态下选中了autotile

                                        float cw = colw / 3.0
                                        float ch = rowh / 3.0
                                        float neighborRows = ts.rows * 3
                                        float neighborCols = ts.cols * 3
                                        //格子
                                        for int j = 0; j < rt.neighborIdArr.size; j++{
                                            int neighborId = rt.neighborIdArr.get(j)
                                            Vec2 pos = dissolveNeighborIdoGridPos(self.curTileset, neighborId) //self.curTileset.dissolveGidToGridPos(gid)
                                            int x = (int)pos.x
                                            int y = (int)pos.y

                                            mkView(o, 50000+y * 100 + x).{
                                                // o.name  = key
                                                // o.border.setAll(1, 0xffffffff)
                                                o.frame.x = x * cw
                                                o.frame.y = y * ch
                                                o.width = cw
                                                o.height = ch

                                                o.backgroundColor = 0x88ff00ff
                                                o.hitTestType.set("none")
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }
            return o
        }
    }
    void ui_createAnimTile(){
        if self.curTileset == null 
        || self.curTilePosArr.size == 0 {
            Toast_make("未选中tile")
            return
        }
        if self.curTilePosArr.size < 2 {
            Toast_make("需要选中多个tile")
            return
        }
        AnimTile@ rt = new AnimTile()
        for int i = 0; i < self.curTilePosArr.size; i++{
            Vec2 pos = self.curTilePosArr.get(i)
            int gid = self.curTileset.calcGid(pos)
            rt.gidArr.append(gid)
        }
        self.curTileset.specialTiles.add(rt)
        self.invalidReact.invalid()
        Toast_make("已创建AnimTile")
    }
    void ui_createRandomTile(){
        if self.curTileset == null 
        || self.curTilePosArr.size == 0 {
            Toast_make("未选中tile")
            return
        }
        if self.curTilePosArr.size < 2 {
            Toast_make("需要选中多个tile")
            return
        }
        RandomTile@ rt = new RandomTile()
        for int i = 0; i < self.curTilePosArr.size; i++{
            Vec2 pos = self.curTilePosArr.get(i)
            int gid = self.curTileset.calcGid(pos)
            rt.gidArr.append(gid)
        }
        self.curTileset.specialTiles.add(rt)
        self.invalidReact.invalid()
        Toast_make("已创建RandomTile")
    }
    void ui_createAutoTile(){
        if self.curTileset == null 
        || self.curTilePosArr.size == 0 {
            Toast_make("未选中tile")
            return
        }
        if self.curTilePosArr.size != 1 {
            Toast_make("需要选中1个tile")
            return
        }
        AutoTile@ rt = new AutoTile()

        Vec2 pos = self.curTilePosArr.get(0)
        int gid = self.curTileset.calcGid(pos)

        rt.gid = gid

        self.curTileset.specialTiles.add(rt)
        self.invalidReact.invalid()
        Toast_make("已创建AutoTile")
    }

    void react(){
        printf("react SpriteSheetEditor\n")
        Theme* t = themeIns()
        self.win.rootView.{
            layoutLinear(self.win.rootView, 0).{
                mkDrawButton(o, 0).{
                    o.text = str("设置")
                    o.onClick = ^void(MouseEvent *me){
                        // Toast_make("设置地图属性")
                        self.showWindow_mapSetting()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("添加tilelayer")
                    o.onClick = ^void(MouseEvent *me){
                        self.addTileLayer()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("添加tileset")
                    o.onClick = ^void(MouseEvent *me){
                        self.ui_addtileset()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("创建随机tile")

                    o.onClick = ^void(MouseEvent*me){
                        // self.removeCurAnim()
                        self.ui_createRandomTile()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("创建动画tile")

                    o.onClick = ^void(MouseEvent*me){
                        // self.removeCurAnim()
                        self.ui_createAnimTile()
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("创建AutoTile")

                    o.onClick = ^void(MouseEvent*me){
                        // self.removeCurAnim()
                        self.ui_createAutoTile()
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
                        long long t0 = Time_unixMs()
                        Json@ jo = Json_toJson(self.map)
                        long long t1 = Time_unixMs()
                        printf(" toJson ms:%lld\n", t1 - t0)
                        String@ json = jo.dump()
                        // printf("json:%s\n", json.str)
                        Path_writeText(self.path.str, json.str)
                        Toast_make("保存成功")
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("加载")
                    o.onClick = ^void(MouseEvent*me){
                        Json@ jo = Json_parseByPathCstr(self.path.str)
                        // printf("加载. json:%s\n", jo.dump().str)
                        printf("加载json完成\n")
                        TileMap@ map = jo.toObjectByVtable(TileMap)
                        self.map = map
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
                        //     mkAssetDirTreeView(o, (long long)item)~{
                        //         o.backgroundColor = t.dock_content_bg
                        //         return o
                        //     }
                        // }
                        // if (item.id.equals("hier")){
                        //     mkSceneHierView(o, (long long)item)~{
                        //         o.backgroundColor = t.dock_content_bg
                        //         return o
                        //     }
                        // }
                        // if (item.id.equals("inspector")){
                        //     mkInspectorView(o, (long long)item)~{
                        //         o.backgroundColor = t.dock_content_bg
                        //         return o
                        //     }
                        // }
                        if (item.id.equals("scene")){
                            return self.reactScene(o, item)
                        }
                        if (item.id.equals("inspector")){
                            return self.reactPreview(o, item)
                        }
                        if (item.id.equals("layers")){
                            return self.reactLayers(o, item)
                        }
                        if (item.id.equals("tilesets-list")){
                            return self.reactTilesetsNames(o, item)
                        }
                        if (item.id.equals("tileset-preview")){
                            return self.reactTilesetView(o, item)
                        }
                        // if (item.id.equals("scene")){
                        //     mkSceneView(o, (long long)item)~{
                        //         o.backgroundColor = t.dock_content_bg
                        //         layoutLinearCell(o, 0)~{
                        //             o.grow = 1
                        //         }
                        //         return o
                        //     }
                        // }


                        mkTextView(o, (long long)item)~{
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

                            layoutLinearCell(o, 0)~{
                                o.grow = 1
                            }

                            return o
                        }
                    }

                    o.root.{
                        o.isHorizontal = false

                        mkDockItemSplitter(o, null, true).{
                            mkDockItem(o, str("layers")).{
                                o.intId = 0;
                                o.width = 150
                            }
                            mkDockItem(o, str("scene")).{
                                o.intId = 0;
                            }
                            mkDockItem(o, str("inspector")).{
                                o.intId = 0;
                            }
                        }
                        mkDockItemSplitter(o, null, true).{
                            mkDockItem(o, str("tilesets-list")).{
                                o.intId = 0;
                                o.width = 160
                            }
                            mkDockItem(o, str("tileset-preview")).{
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



    void showWindow_mapSetting(){
        Window@ win = null

        ^void () reactMapSetting = ^ void () {
            win.rootView.{
                mkTextView(o, 0).{
                    o.setText(str("tileWidth:"))
                }
                mkEditText(o, 0).{
                    o.setValue_notInFocus(str("").addi(self.map.tileWidth))
                    o.onValueChanged = ^void (EditText*et){
                        int rows = et.value.toInt()
                        self.map.tileWidth = rows
                        reactMapSetting()
                        self.invalidReact.invalid()
                    }
                }
                mkTextView(o, 0).{
                    o.setText(str("tileHeight:"))
                }
                mkEditText(o, 0).{
                    o.setValue_notInFocus(str("").addi(self.map.tileHeight))
                    o.onValueChanged = ^void (EditText*et){
                        int rows = et.value.toInt()
                        self.map.tileHeight = rows
                        reactMapSetting()
                        self.invalidReact.invalid()
                    }
                }
                mkTextView(o, 0).{
                    o.setText(str("fps:"))
                }
                mkEditText(o, 0).{
                    o.setValue_notInFocus(str("").addi(self.map.fps))
                    o.onValueChanged = ^void (EditText*et){
                        int v = et.value.toInt()
                        self.map.fps = v
                        reactMapSetting()
                        self.invalidReact.invalid()
                    }
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


            o.setTitle("瓦片地图编辑器")
            o.setSize(800, 600)
            o.show()
        }

    }
}