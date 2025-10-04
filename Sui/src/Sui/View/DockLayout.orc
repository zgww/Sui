package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Event.orc"
import * from "../Core/Mouse.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/Frame.orc"
import * from "../Core/Canvas.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "./ViewBuilder.orc"
import * from "./Drag.orc"
import * from "../../Json/Json.orc"
import * from "../../SuiDesigner/Theme.orc"

static const char *SPLITTER = "splitter"
static const char *TAB = "tab"
static const char *ITEM= "item"


// class DockSplitterInfo{
//     ViewBase@ splitterView = null;
//     DockItem@ prev = null;
//     DockItem@ next = null;
// }


// splitter 包含tab, tab包含item
class DockItem {
    int intId = 0
    String@ id = str("")
    ViewBase@ view = null;

    //水平还是垂直方向,用于splitter
    bool isHorizontal = false;
    // item|splitter|tab
    String@ type = str(ITEM)
    float width = 0
    float weight = 1 //放大

    //>>帮助计算dragSplitter
    //实际的内容尺寸
    float _sumContentSize = 0
    //累计用来动态分配的空间
    float _sumFlexSize = 0
    //累加的权重
    float _sumWeight = 0
    //<<

    // Frame frame = mkFrame();

    // float shrink = 0 //缩小
    // bool isFixedWidth = false

    List@ children = new List()
    DockItem@ parent = null
    // 对于tab需要有spliiterView
    ViewBase@ nextSplitterView = null 
    ViewBase@ prevSplitterView = null 

    //对于type=splitter,需要记录splitterViews
    // List@ splitterViews = new List();

    void fromJson(Json@ jo){
        self.intId = jo.getNumber("intId")
        self.id = jo.getString("id")
        self.isHorizontal = jo.getBool("isHorizontal")
        self.type = jo.getString("type")
        self.width = jo.getNumber("width")
        self.weight = jo.getNumber("weight")
    }

    Json@ toJson(){
        Json@ jo = Json_mkObject()
        jo.putNumber("intId", self.intId)
        jo.putString("id", self.id)
        jo.putBool("isHorizontal", self.isHorizontal)
        jo.putString("type", self.type)
        jo.putNumber("width", self.width)
        jo.putNumber("weight", self.weight)

        Json@ kids = Json_mkArray()
        jo.put("children", kids)

        for (int i = 0; i < self.children.size(); i++){
            DockItem* kid = (DockItem*)self.children.get(i)
            Json@ kidJo = kid.toJson()
            kids.add(kidJo)
        }

        return jo
    }

    //对于tab的当前tab索引
    int tabActiveIndex = 0

    void setTabActiveIndex(int index){
        self.tabActiveIndex = clampInt(index, 0, self.children.size() - 1)
    }

    void dtor(){
        printf("释放DockItem:%p %s\n", self, self.id.str);
        if (self.parent){
            self.parent.printTree(0)
        }
    }

    //设置为当前tab项
    void setSelfActive_inTab(){
        if (self.parent && self.parent.type.equals(TAB)){
            int idx = self.parent.children.indexOf(self)
            self.parent.setTabActiveIndex(idx)
        }
    }

    //拖拽splitter，如果左右都是weight模式,
    //就需要计算新的weight值
    float calcWeight_ofKid_forDragSplitter(
        DockItem *kid,
        float delta,
        float minSize
    ){
        if (kid.width > 0){
            return 0;
        }

        float actualSize = kid.weight / self._sumWeight * self._sumFlexSize
        float newSize = maxFloat(minSize, actualSize + delta)
        float newWeight = newSize / self._sumFlexSize * self._sumWeight
        return newWeight
    }

    void appendChild(DockItem *item){
        item.removeSelf()

        self.children.add(item)
        item.parent = self
    }
    void removeSelf(){
        if (self.parent){
            self.parent.removeChild(self)
        }
    }
    bool insertBefore(DockItem *newItem, DockItem *relChild){
        return self.insertOffset(newItem, relChild, 0)
    }
    bool insertAfter(DockItem *newItem, DockItem *relChild){
        return self.insertOffset(newItem, relChild, 1)
    }
    bool insertOffset(DockItem *newItem, DockItem *relChild, int offset){
        if (newItem == null){
            return false
        }

        int idx = self.children.indexOf(relChild)
        if (idx == -1){
            return false
        }
        newItem.removeSelf()
        self.children.insert(newItem, idx + offset)
        newItem.parent = self
        return true
    }

    void removeChild(DockItem *kid){
        if (kid.parent == self){
            self.children.remove(kid)
            kid.parent = null
        }
    }

    DockItem* tryGetParentTab(){
        DockItem *cur = self.parent
        if (cur.type.equals(TAB)){
            return cur
        }
        return null
    }
    void printTree(int tab){
        for (int i = 0; i < tab; i++){
            printf("\t");
        }
        printf("%s@%p#%d[%f,%f]\n", self.id.str, self, self.intId, self.width, self.weight)
        for (int i = 0; i < self.children.size(); i++){
            DockItem* kid = (DockItem*)self.children.get(i)
            kid.printTree(tab + 1);
        }
    }
    bool isEmptySplitter(){
        if (self.type.equals(SPLITTER)){
            if (self.children.size() == 0){
                return true
            }
        }
        return false;
    }
    bool isEmptyTab(){
        if (self.type.equals(TAB)){
            if (self.children.size() == 0){
                return true
            }
        }
        return false;

    }
}

DockItem@ DockItem_fromJson(Json@ jo){
    DockItem@ di = new DockItem()

    di.fromJson(jo)

    Json@ children = jo.get("children")
    if children {
        int l = children.arraySize()
        for (int i = 0; i < l; i++){
            Json@ kid = children.at(i)
            DockItem@ kidDi = DockItem_fromJson(kid)
            di.appendChild(kidDi)
        }

    }
    return di
}
//用法
//mkDockItemSplitter(null, str("")).{
//    mkDockItem(o, str("hier"))
//    mkDockItem(o, str("console"))
//    mkDockItem(o, str("scene"))
//    mkDockItem(o, str(""))
//}
DockItem@ mkDockItem(DockItem *parent, String@ id){
    DockItem@ ins = new DockItem()
    if id {
        ins.id = id;
    }
    if (parent){
        parent.appendChild(ins)
    }
    return ins
}
DockItem@ mkDockItemSplitter(DockItem *parent, String@ id, bool isHorizontal){
    DockItem@ ins = mkDockItem(parent, id)
    ins.type = str(SPLITTER)
    ins.isHorizontal = isHorizontal
    return ins
}
DockItem@ mkDockItemTab(DockItem *parent, String@ id){
    DockItem@ ins = mkDockItem(parent, id)
    ins.type = str(TAB)
    return ins
}

/// 可停靠窗口
class DockLayout extends View {
    //分隔条占据的空间
    int splitterSize = 1
    float minItemSize = 10

    int tabHeadBg = themeIns().dock_headbar_bg//0x33ff0000

    DockItem@ root = mkDockItemSplitter(null, str(""), true) //new DockItem()
    // List<DockSplitterInfo>
    // List@ splitterInfos = new List()

    ^ViewBase * (DockItem *item, ViewBase *parent) cbRenderItemContentView;
    ^void (DockItem *item, ViewBase *parent, int kidIndex) cbRenderItemHeadView;

    // Drag@ dragSplitter = new Drag()
    Drag@ dragTab = new Drag()

    ^void () _afterDrawChildren 

    void ctor(){
        // self.dragSplitter.onDrag =^ void(Drag *d){
        //     printf("drag....\n");
        // }
        self.dragTab.onDrag = ^void(Drag *d){
            if (d.isDragging || d.isDragEnd){
                printf("\n\n\t drag tab\n")
                self.invalidDraw()
            }
            if (d.isDragEnd){
                self.doDrop()
            }
        }
    }

    void doDrop(){
        Vec2 mousePos = Mouse_getPosOfWindow(self.ownerWindow)
        DockItem *target = self.findDockItem_containsVec2(self.root, mousePos.x, mousePos.y)

        if (target && target.view){
            Rect absRect = target.view.get_abs_rect()
            printf("mousePos.:%f,%f abs:%f,%f,%f,%f\n", mousePos.x, mousePos.y
            , absRect.x, absRect.y, absRect.w, absRect.h
            )
            // drop type
            // Vec2 geo = absRect.containsPositionIn9Patch(mousePos.x, mousePos.y)
            int geoType = -1
            Rect geo = absRect.containsPositionIn5Patch_withOutType(mousePos.x, mousePos.y,
                mkRect(0.2, 0.2, 0.6, 0.6), &geoType
            )
            if (geo.x == -1){
                printf("放置tab无效，未找到目标\n")
                return 
            }
            
            if (self.dragTab.data instanceof DockItem){
                DockItem@ source = (DockItem*)self.dragTab.data
                printf("do Drop source:%s, target:%s, geoType:%d\n"
                    , source.id.str
                    , target.id.str
                    , geoType
                );

                if (source == target){ //如果目标就是自己，不处理
                    return;
                }

                if (geoType == 0){ //上
                    self.dropInSplitter(source, target, false, true)
                }
                if (geoType == 1){ //左
                    self.dropInSplitter(source, target, true, true)
                }
                if (geoType == 2){ //中
                    DockItem@ tab = self.upto_getOrWrap_DockItemTab(target)
                    if (tab){
                        printf("doDrop. create tab:%p %s\n", tab, tab.id.str);
                        tab.appendChild(source)
                        self.invalidReact()
                    }
                }
                if (geoType == 3){ //右
                    self.dropInSplitter(source, target, true, false)
                }
                if (geoType == 4){ //下
                    self.dropInSplitter(source, target, false, false)
                }
                self.clearAllEmptyTab(self.root)
            }
        }
        self.root.printTree(0)
    }

    void react(){
        self.startInnerReact()

        self.eachThenWrapTab_forNakeDockItemInSplitter(self.root)
        // self.root.printTree(0)

        self._reactDockItem(self.root)

        self.endInnerReact()
        // printNodeTree(self, 0)
    }

    //用来唯一标识一个
    // int viewIndex = 1000

    void onDragSplitter(Drag *drag, DockItem *parentDockItem, 
        DockItem *prevDockItem, 
        DockItem *nextDockItem){

        printf("drag SPlitter. parent:%s, prev:%s, next:%s\n", 
            parentDockItem.id.str,    prevDockItem.id.str
            , nextDockItem.id.str);

        if (drag.isDragChecking){
            drag.cursor = 
                parentDockItem.isHorizontal ? str("sizewe")
                :  str("sizens")
        }
        if (drag.isDragging){
            float delta = drag.deltaPos.y
            if (parentDockItem.isHorizontal){
                delta = drag.deltaPos.x
            }

            //根据width/weight的不同组合，有不同的反应
            if (prevDockItem.width > 0 && nextDockItem.width > 0){
                // printf(">0, >0\n");
                prevDockItem.width = maxFloat(self.minItemSize, prevDockItem.width + delta)
                nextDockItem.width = maxFloat(self.minItemSize, nextDockItem.width - delta)
            }
            else if (prevDockItem.width > 0 && nextDockItem.width == 0){
                // printf(">0, =0\n");
                prevDockItem.width = maxFloat(self.minItemSize, prevDockItem.width + delta)
            }
            else if (prevDockItem.width == 0 && nextDockItem.width > 0){
                // printf("=0, >0\n");
                nextDockItem.width = maxFloat(self.minItemSize, nextDockItem.width - delta)
            }
            else {// 都是weight模式
                // (w - delta) / flexSize = weight / sumWeight
                // printf("=0, =0\n");
                prevDockItem.weight = parentDockItem.calcWeight_ofKid_forDragSplitter(
                    prevDockItem,
                    delta,
                    self.minItemSize
                )
                nextDockItem.weight = parentDockItem.calcWeight_ofKid_forDragSplitter(
                    nextDockItem,
                    -delta,
                    self.minItemSize
                )
                // printf("\t\t\t更新dock item weight:%f, %f\n",
                //     prevDockItem.weight,
                //     nextDockItem.weight,
                // );
            }

            // parentDockItem.printTree(2)

            self.invalidLayout()
        }
    }

    void _reactDockItem(DockItem* item){
        DockItem @parentItem = item
        if (item.type.equals(SPLITTER)){
            View *splitterView = null
            int l = item.children.size()
            for (int i = 0; i < l; i++){
                int index = i

                DockItem* kid = (DockItem*)item.children.get(i)

                kid.prevSplitterView = splitterView
                self._reactDockItem(kid);
                if (i < l - 1){
                    DockItem* nextKid = (DockItem*)item.children.get(i + 1)
                    //创建splitterview
                    // DockSplitterInfo@ info = new DockSplitterInfo()
                    // 2000用来表示 splitterView
                    // 这个key的选择，极端情况下可能会导致key重复? 如果item的值不同得很刚好
                    dockSplitterView(self, ((long long)item) + 2000 + i).{
                        o.z = 10
                        o.drag.onDrag = ^ void (Drag *d){
                            // printf("drag i:%d, index:%d\n", i, index);
                            self.onDragSplitter(
                                d, parentItem, kid, nextKid
                            )
                        }
                        
                        o.cursor = item.isHorizontal ? str("sizewe"): str("sizens")
                        // kid.view = o
                        // self.viewIndex = self.viewIndex + 1
                        kid.nextSplitterView = o
                        splitterView = o
                    }
                }
            }
        }
        if (item.type.equals(TAB)){
            layoutLinear(self, (long long)item).{
                // o.backgroundColor = 0xffffffff
                o.needClip = true
                item.view = o

                o.direction = str("column")
                o.alignItems = str("stretch")

                //渲染头部视图
                self._reactTabHeads(item, o)
                //渲染内容视图
                self._reactTabContent(item, o)
            }
        }
        if (item.type.equals(ITEM)){
            if (self.cbRenderItemContentView){
                ViewBase* v = self.cbRenderItemContentView(item, self)
                item.view = v
            }
        }
    }

    //处理事件：点击tab项
    void _onClickTabItemHead(DockItem *kid){
        kid.setSelfActive_inTab()
        self.invalidReact()
    }
    //处理事件：tab项
    void _onEvent_tabItemHead(Event *e, DockItem *kid){
        if (e instanceof MouseEvent){
            MouseEvent *me = (MouseEvent*)e

            if (me.isMouseDown){
                // MessageDialog_alert("click tab head", "title标题")
                self._onClickTabItemHead(kid)
            }

            self.dragTab.data = kid
            self.dragTab.onMouseDown(me)
        }
    }

    // ^void (Event *e) _onEvent_tabItem 
    void _reactTabHeads(DockItem *tab, ViewBase *parent){
        layoutLinear(parent, 0).{
            o.direction = str("row")
            // o.backgroundColor = 0xff0000ff
            o.backgroundColor = self.tabHeadBg
            int l = tab.children.size()
            for (int i = 0; i < l; i++){
                DockItem@ kid = (DockItem@)tab.children.get(i)
                if (kid.type.equals(ITEM)){
                    layoutLinear(o, (long long)kid).{
                        // printf("设置tabHead cbOnEvent:%p %s\n", kid, kid.id.str);
                        o.cbOnEvent = ^void(Event *e){
                            self._onEvent_tabItemHead(e, kid)
                        }
                        if (self.cbRenderItemHeadView){
                            self.cbRenderItemHeadView(kid, o, i)
                        }
                    }
                }
            }
        }
    }
    void _reactTabContent(DockItem *tab, ViewBase *parent){
        layoutLinear(parent, 0).{
            o.direction = str("column")
            o.alignItems = str("stretch")
            // o.backgroundColor = 0xffffff00
            // o.padding.setAll(10)

            layoutLinearCell(o, 0).{
                o.grow = 1
            }

            DockItem* kid = (DockItem*)tab.children.get(tab.tabActiveIndex)
            if (kid){
                if (self.cbRenderItemContentView){
                    ViewBase *view = self.cbRenderItemContentView(kid, o)
                    kid.view = view;
                }
            }
        }
    }

    void layoutContent(Frame *frame){
        //不处理非tight的情况
        if (!frame.isTight()){
            printf("\n\nDockLayout layoutContent. 非tight\n");
            return;
        }
        //tight模式
        // printf("\n\nDockLayout layoutContent. tight\n");
        // super.layoutContent(frame)
        self.layoutContentDockItem(frame, self.root, 0, 0)

        // printNodeTree(self, 0)
    }
    void layoutContentDockItem(Frame *frame, DockItem *item, int px, int py){
        if (item.type.equals(SPLITTER)){
            // Frame kidFrame = mkFrame()
            int kidsSize  = item.children.size()
            float sumSplitterSize = (kidsSize - 1) * self.splitterSize
            float mainSize = item.isHorizontal ? frame.width : frame.height
            float sumContentSize = mainSize - sumSplitterSize
            float sumWeight = 0
            float sumWidth = 0
            int l = kidsSize
            for (int i = 0; i < l; i++){
                DockItem* kid = (DockItem*)item.children.get(i)
                float w = maxFloat(0.0, kid.width)
                if (w > 0){ //width优先
                    sumWidth = sumWidth + w
                } 
                else {
                    sumWeight = sumWeight + maxFloat(0.0, kid.weight)
                }
            }
            if (sumWeight <= 0) { //确保不为0
                sumWeight = 1.0
            }
            // 动态分配的内容空间
            float flexSpaceSize = maxFloat(0.0, sumContentSize - sumWidth)


            item._sumContentSize = sumContentSize
            item._sumFlexSize = flexSpaceSize
            item._sumWeight = sumWeight

            float pos = 0.0
            l = kidsSize
            for (int i = 0; i < l; i++){
                DockItem* kid = (DockItem*)item.children.get(i)
                Frame tmpFrame = mkFrame()
                Frame *kidFrame = kid.view ? &kid.view.frame : &tmpFrame

                float kidSize = 0.0
                if (item.isHorizontal){ //水平方向
                    kidFrame.x = pos + px
                    kidFrame.y = 0.0 + py
                    // float placeSize = maxFloat(0.0, kid.width)
                    kidSize = kid.width > 0 
                    ? kid.width 
                    : maxFloat(0.0, kid.weight)  / sumWeight * flexSpaceSize
                    kidFrame.setTight(
                        kidSize, 
                        frame.height,
                    )
                } else { //垂直方向
                    kidFrame.x = 0.0 + px
                    kidFrame.y = pos + py
                    kidSize = kid.width > 0 
                    ? kid.width 
                    : maxFloat(0.0, kid.weight)  / sumWeight * flexSpaceSize
                    kidFrame.setTight(
                        frame.width,
                        kidSize, 
                    )
                }

                if (kid.type.equals(SPLITTER)){
                    self.layoutContentDockItem(kidFrame, kid, kidFrame.x, kidFrame.y)
                } else {
                    //布局子视图
                    if (kid.view){
                        kid.view.layout(kidFrame)
                    }
                }
                pos = pos + kidSize
                //布局splitter
                if (kid.nextSplitterView){
                    // kid.nextSplitterView.frame.
                    Frame *f = &kid.nextSplitterView.frame
                    if (item.isHorizontal){
                        f.x = pos + px
                        f.y = 0 + py
                        f.setTight(
                            self.splitterSize,
                            frame.height,
                        )
                    } else {
                        f.x = 0 + px
                        f.y = pos + py
                        f.setTight(
                            frame.width,
                            self.splitterSize,
                        )
                    }
                    kid.nextSplitterView.layout(f);
                    pos = pos + self.splitterSize
                }
            }
        }

    }

    // void draw_self(Canvas *canvas){
    //     super.draw_self(canvas)
    //     self.drawDndIndicator(canvas)
    // }
    void drawSelfBorder(Canvas *canvas){
        super.drawSelfBorder(canvas)
        self.drawDndIndicator(canvas)
    }
    void drawDndIndicator(Canvas *canvas){
        Drag *drag = self.dragTab

        if (!drag.isDragging){
            return
        }
        if (!self.ownerWindow){
            return;
        }
        //计算绘制的位置
        Vec2 mousePos = Mouse_getPosOfWindow(self.ownerWindow)
        DockItem *target = self.findDockItem_containsVec2(self.root, mousePos.x, mousePos.y)

        if (target && target.view){
            canvas.save()

            canvas.translate(
                self.padding.left + self.border.l.w, 
                self.padding.top + self.border.t.w
            );

            Rect absRect = target.view.get_abs_rect()
            printf("mousePos.:%f,%f abs:%f,%f,%f,%f\n", mousePos.x, mousePos.y
            , absRect.x, absRect.y, absRect.w, absRect.h
            )
            // drop type
            // Vec2 geo = absRect.containsPositionIn9Patch(mousePos.x, mousePos.y)
            Rect geo = absRect.containsPositionIn5Patch(mousePos.x, mousePos.y,
                mkRect(0.2, 0.2, 0.6, 0.6)
            )

            Rect r = target.view.frame.toRect()

            canvas.beginPath()
                canvas.fillColor( 255, 0, 0, 64)
                canvas.rect(
                    r.x + r.w * geo.x 
                    , r.y + r.h * geo.y 
                    , r.w * geo.w
                    , r.h * geo.h)
            canvas.fill()

            canvas.restore()

        }
    }
    DockItem* findDockItem_containsVec2(DockItem *item, int clientX, int clientY){
        if (item.view){//是子视图
            Rect r = item.view.get_abs_rect()
            bool ok = r.containsPosition(clientX, clientY)
            if (ok){
                return item;
            }
        }
        //不是子视图
        int l = item.children.size()
        for (int i = 0; i < l; i++){
            DockItem* kid = (DockItem*)item.children.get(i)
            DockItem *ret = self.findDockItem_containsVec2(kid, clientX, clientY)
            if (ret){
                return ret
            }
        }
        return null
    }

    //向上找到离splitter最近 dockItem(非splitter)
    DockItem@ upto_findMostAncestorInDockItemSplitter(DockItem@ item){
        DockItem *cur = item;
        while (cur && cur.parent){
            if (cur.parent.type.equals(SPLITTER)){
                return cur
            }
            cur = cur.parent
        }
        return null
    }

    bool dropInSplitter(DockItem@ source, DockItem@ target, bool isHorizontal, bool isBefore){
        DockItem@ ancestor = self.upto_findMostAncestorInDockItemSplitter(target)
        if (!ancestor){ //没有目标
            return false
        }
        DockItem@ splitter = ancestor.parent
        if (!splitter.type.equals(SPLITTER)){
            return false;
        }
        source.removeSelf()

        if (splitter.isHorizontal == isHorizontal){ //同向
            splitter.insertOffset(source, ancestor, isBefore ? 0 : 1)
        }
        else { //异向，需要包裹一个splitter
            DockItem@ newSplitter = mkDockItemSplitter(null, str("splitter-of-")
                .addString(ancestor.id), isHorizontal)

            // 添加splitter
            splitter.insertOffset(newSplitter, ancestor, 0)

            //按顺序加入source/ancestor
            newSplitter.appendChild(ancestor)
            newSplitter.insertOffset(source, ancestor, isBefore ? 0 : 1)
        }
        self.invalidReact()

        return true
    }

    //向上，找到或者包装一下dockItemTab
    // 对于Splitter,返回null
    DockItem@ upto_getOrWrap_DockItemTab(DockItem@ item){
        if (item.type.equals(SPLITTER)){
            return null
        }
        //这是找到了
        if (item.type.equals(TAB)){
            return item
        }
        //这是未找到
        if (item.type.equals(ITEM)){
            DockItem *parent = item.parent
            if (parent){
                if (parent.type.equals(TAB)){
                    return parent
                }
                if (parent.type.equals(SPLITTER)){
                    //包装一下
                    DockItem@ tab = mkDockItemTab(null, str("tab-of-")
                        .addString(item.id))
                    tab.width = item.width
                    tab.weight = item.weight
                    parent.insertBefore(tab, item)
                    tab.appendChild(item)
                    return tab
                }
            }
        }
        return null
    }

    void clearAllEmptyTab(DockItem *item){
        for (int i = item.children.size() - 1; i >= 0; i--){
            DockItem* kid = (DockItem*)item.children.get(i)
            if (kid.type.equals(SPLITTER)){
                self.clearAllEmptyTab(kid)

                if (kid.children.size() == 0 ){//空的Splitter
                    kid.removeSelf()
                }
                else if (kid.children.size() == 1){//只有一个子的splitter,也没有意义
                    if (kid.parent){
                        DockItem@ solo = (DockItem@)kid.children.get(0)
                        if (solo){
                            kid.parent.insertBefore(solo, kid) //把子提出来
                            kid.removeSelf() //再把无效的splitter删掉
                        }
                    }
                }
            }
            else if (kid.isEmptyTab()){ //空的tab要删除
                kid.removeSelf()
            }
            //约束activeIndex
            if (kid.type.equals(TAB)){
                kid.setTabActiveIndex(kid.tabActiveIndex)
            }
        }
    }
    //为splitter下的裸的dockitem包装个tab
    void eachThenWrapTab_forNakeDockItemInSplitter(DockItem @item){
        for (int i = item.children.size() - 1; i >= 0; i--){
            DockItem* kid = (DockItem*)item.children.get(i)
            if (kid.type.equals(SPLITTER)){
                //递归处理
                self.eachThenWrapTab_forNakeDockItemInSplitter(kid)
            }
            else if (kid.type.equals(ITEM)){
                //包装在tab中
                self.upto_getOrWrap_DockItemTab(kid)
            }
        }
    }


    ViewBase* hitTestChildren(float x, float y){
        return hitTestChildren_withZ(self, x, y)
    }

}

class DockSplitterView extends View{
    Drag@ drag = new Drag()

    int hoverBg = themeIns().dock_splitterBgHover//0xff007aff//0xff00ff00
    int normalBg = themeIns().dock_splitterBg //0xffcdcdcf

    void ctor(){
        self.cursor = str("pointer")
        self.hitTestPadding = mkInset(3, 3, 3, 3)
    }
    void react(){
        self.backgroundColor = self.hover ? self.hoverBg : self.normalBg
        self.invalidDraw()
    }
    void onEvent(Event *e){
        if (e instanceof MouseEvent){
            if (self.drag){
                self.drag.onMouseDown((MouseEvent*)e)
            }
        }
    }
    // void draw_self(Canvas *canvas){
    //     if self.hover {
    //         canvas.save()
    //         self.frame.width += 4
    //         canvas.translate(-2, 0)
    //     }
    //     super.draw_self(canvas)
    //     if self.hover {
    //         canvas.restore()
    //     }
    // }
    
    void onHoverChanged(){
        self.invalidReact()
    }
}


DockLayout@ dockLayout(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (DockLayout@)gocNode(sp, (Node*)parent, DockLayout)
}
DockSplitterView@ dockSplitterView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (DockSplitterView@)gocNode(sp, (Node*)parent, DockSplitterView)
}