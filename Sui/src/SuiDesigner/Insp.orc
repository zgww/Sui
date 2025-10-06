package SuiDesigner

#include "../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
#include "../Json/cJSON.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"
import * from "../Json/Json.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Bezier.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"

import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/Switch.orc"
import * from "../Sui/View/Select.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/Slider.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/Panel.orc"
import * from "../Sui/Core/Window.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ColorPicker.orc"
import * from "./Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "./Asset/AssetDirView.orc"
import * from "./Asset/AssetDirTreeView.orc"
import * from "./SceneView.orc"
import * from "./SceneHierView.orc"
import * from "./ANode.orc"
import * from "./BezierEditView.orc"
import * from "./EditCtx.orc"
import * from "./EventANodeChanged.orc"
import * from "./FileChooser.orc"
import * from "./Theme.orc"



// 思路：
// 简化的inspector, 只编辑一层属性。 不用考虑嵌套属性

// 基于类型，提供通用型的insp
// 个别相同类型，但不同语义的，需要主动提供定义

// 尽量让用户只需要提供的信息最少

// 不支持嵌套的对象的属性编辑。
// insp就是用来insp  this object的属性的。
// 嵌套的对象，嵌套起来就没有边了。没有必要
// 如果是对象类型的属性，让其提供特定的insp, 或者走通用的对象属性 按钮?

// 都跟属性、反射有关。所以放在一起思考

// 期望：

// 尽可能自动化,尽可能简便，少提供信息或者写代码。

// 所以必然要用反射自动处理。也必然要支持按类型处理

// 只提供特例的信息。
// 特例的信息有：
// * 字段要不要忽略(序列化、insp)
// * 类型要不要忽略
// * 类型要不要自定义处理方法(序列化、insp)
// * 对象可以提供自定义的处理？甚至完全覆盖insp的逻辑


// 通例：
// * 下划线开头的字段，不处理
// * 默认按类型处理
// * 匹配特定规则的， 如int xxColor 


// 3d场景的保存，并不是序列化。  而是对场景描述文件的修改。
// 场景描述文件是dsl。所以可以支持if/for。 可以支持只写入有修改的属性。


// 2d/3d都统一场景描述方案

// insp都统一为 对象检视方案, 无关场景


class EventInspAttrChanged extends Event{
    OrcMetaField* mf;
    // String@ key;
    Object@ obj
    Object@ newValue
    InspAttr@ inspAttr
}

class InspOpt {
    int value
    String@ label;
}
class InspOpts {
    List@ opts = new List()
    InspOpts* set(int value, const char *label){
        for int i = 0; i < self.opts.size(); i++{
            InspOpt* opt = (InspOpt*)self.opts.get(i)
            if opt.value == value{
                opt.label = str(label);
                return self
            }
        }

        InspOpt@ opt = new InspOpt()
        opt.value = value
        opt.label = str(label)
        self.opts.add(opt)
        return self
    }
    int getValueByLabel(const char *label){
        for int i = 0; i < self.opts.size(); i++{
            InspOpt* opt = (InspOpt*)self.opts.get(i)
            if opt.label.equals(label) {
                return opt.value
            }
        }
        return -1
    }
    List@ getLabels(){
        List@ labels = new List()
        if self.opts {
            for int i = 0; i < self.opts.size(); i++{
                InspOpt* opt = (InspOpt*)self.opts.get(i)
                labels.add(opt.label)
            }
        }
        return labels
    }
}


//在insp过程中临时需要的信息
static struct TmpAttrInfo {
    String* panelName
    int hboxIdx

    bool isPanelStart
    bool isPanelEnd
    bool isHboxStart
    bool isHboxEnd

}
static struct MethodInfo {
    int hboxIdx
    bool isMethod
}

extension TmpAttrInfo {
    void init(){
        memset(self, 0, sizeof(*self))
    }
    void proc(OrcMetaField*mf, InspAttr* attr, Insp* insp){
        MethodInfo methodInfo = self.extractHboxIdx(mf)
        OrcMetaField* nextMf = OrcMetaField_getNext(mf)
        MethodInfo nextMethodInfo = self.extractHboxIdx(nextMf)

        int curHboxIdx = methodInfo.hboxIdx
        int nextHboxIdx = nextMethodInfo.hboxIdx

        String* curPanelName = attr ? attr._panelName : null
        String* nextPanelName = null
        if nextMf {
            InspAttr* nextAttr = insp.getAttr(nextMf.name)
            nextPanelName = nextAttr? nextAttr._panelName: null
        }

        //上升沿
        self.isHboxStart = self.hboxIdx != curHboxIdx && curHboxIdx > 0
        self.isHboxEnd = curHboxIdx != nextHboxIdx && curHboxIdx > 0
        //独立的Method也放在hbox中
        if !self.isHboxStart && !self.isHboxEnd && methodInfo.isMethod {
            self.isHboxStart = true
            self.isHboxEnd = true
        }

        self.isPanelStart = !self.panelName.equalsString(curPanelName) && curPanelName
        self.isPanelEnd = !curPanelName.equalsString(nextPanelName) && curPanelName

        self.panelName = curPanelName
        self.hboxIdx = curHboxIdx
    }

    MethodInfo extractHboxIdx(OrcMetaField*mf){
        MethodInfo r
        memset(&r, 0, sizeof(r))

        if mf && mf.type == OrcMetaType_method && String_startsWith(mf.name, "insp") && strlen(mf.name) > 5 {
            r.isMethod = true
            sscanf(mf.name, "insp%d", &r.hboxIdx);
        }
        return r
    }
}

class InspAttr{
    String@ _name = str("")
    // 指定面板名称
    String@ _panelName = null
    
    // String@ hbox = null

    //一般也不需要左右.
    bool _hbox = false
    // 忽略
    bool _ignore = false
    // int _hratio = 0.5

    // 适用于list, 提供成员的类型
    // Vtable_Object* typeVt;

    void bind(Insp* insp, const char* name, const char *panelName){
        // new InspAttrColor().{o.name.set("df");o.to(insp) }
        // new InspAttrColor().{o.bind(insp, "df")}
        // insp.bind(new InspAttrColor(), "df")
        // insp.color("df")
        self._name.set(name)
        if panelName {
            self._panelName = str(panelName)
        }
        insp.attrMap.put(self._name.str, self)
    }

    void to(Insp* insp){
        insp.attrMap.put(self._name.str, self)
    }

    void inspValue(Node* o, Object *obj, OrcMetaField *mf, Insp* insp){
        //值
        insp.inspValueDefault(o, obj, mf)
    }

    // void setAttr(){
    // }
}
class InspAttrColor extends InspAttr{
    void inspValue(Node*o, Object *obj, OrcMetaField *mf, Insp* insp){
        mkColorPicker(o, 0).{
            int* pColor = OrcMetaField_getIntPtr(mf, obj)

            o.backgroundColor = *pColor;
            o.onChanged = ^void (int newcolor){
                insp.setAttr(mf, mkInteger(newcolor))
            }
        }
    }
}
class InspAttrImageSrc extends InspAttr{
    void inspValue(Node*o, Object *obj, OrcMetaField *mf, Insp* insp){
        layoutLinear(o, (long long)mf).{
            o.direction.set("column")
            o.alignItems.set("start")

            String* src = *((String**)OrcMetaField_getPtr(mf, obj))
            mkImageView(o, 0).{
                o.width = 100
                o.height = 100
                o.setImageMode( WrapContent)
                o.border.setAll(1, 0xff999999)
                o.setSrc(src)
                o.cursor.set("pointer")
                o.cbOnEvent = ^ void(Event *e){
                    if e instanceof MouseEvent {
                        MouseEvent *me = (MouseEvent*)e;
                        if me.button == 1 && me.isClickInBubble(){
                            // Toast_make(str("click image").addString(src).str)
                            FileChooser@ fc = new FileChooser()
                            fc.use_filterImage()
                            fc.loadPaths()
                            fc.onChoose = ^ void(String@ newpath){
                                insp.setAttr(mf, newpath)
                            }
                            fc.showWindow()
                        }
                    }

                }
            }
            mkTextView(o, 0).{
                o.setText(src)
            }
        }
    }
}
class InspAttrFilePath extends InspAttr{
    void inspValue(Node*o, Object *obj, OrcMetaField *mf, Insp* insp){
        layoutLinear(o, (long long)mf).{
            o.direction.set("column")
            o.alignItems.set("start")

            String* src = *((String**)OrcMetaField_getPtr(mf, obj))
            mkDrawButton(o, 0).{
                if src && src.notEmpty(){
                    o.text = src
                }
                else {
                    o.text = str("null")
                }
                o.onClick = ^void(MouseEvent *me){
                    // Toast_make("HI click")
                    FileChooser@ fc = new FileChooser()
                    fc.dir.set("./asset")
                    // fc.use_filterImage()
                    fc.loadPaths()
                    fc.onChoose = ^ void(String@ newpath){
                        insp.setAttr(mf, newpath)
                    }
                    fc.showWindow()
                }
            }
        }
    }
}
class InspAttrSelect extends InspAttr{
    //枚举选项
    InspOpts@ opts = new InspOpts()

    void inspValue(Node*o, Object *obj, OrcMetaField *mf, Insp* insp){
        mkSelect(o,0).{
            o.options = self.opts.getLabels()
            o.onChanged = ^void(int i, String@ label){
                // Toast_make(str("on select:").addString(label).str)

                int intv = self.opts.getValueByLabel(label.str)
                insp.setAttr(mf, mkInteger(intv))
            }
        }
    }
}


//将要检视的属性等信息收集起来，再统一渲染
class InspNode extends Node{
}
class InspAttrItem extends InspNode{
    InspAttr* attr
    OrcMetaField *mf
}
class InspPanel extends InspNode{
    // String@ name
}


class Insp {
    // 维护当前的节点栈. peek 
    List@ curNodeStack = new List()
    Object@ obj

    Map@ attrMap = new Map()

    InspLib@ lib = useInspLib()

    // ^void (String@ chainKey, InspValue *data) onSetField

    InspAttr* getAttr(const char *key){
        // List@ keys = self.attrMap.keys()
        // int size = keys.size();
        // for int i = 0; i < size; i++{
        //     printf("key:%s\n", ((String*)keys.get(i)).str)
        // }
        InspAttr* a = (InspAttr*)self.attrMap.get(key)
        return a
    }

    // ' ' 分隔
    void excludes(const char *keys){
        List@ parts = str(keys).trim().splitByRe("\\s+")
        int size = parts.size();
        for int i = 0; i < size; i++{
            String* key = (String*)parts.get(i)
            self.exclude(key.str)
        }
    }
    void exclude(const char *key){
        // printf("exclude key:%s\n", key)
        InspAttr* a = self.getAttr(key)
        if a {
            a._ignore = true;
        }
        else {
            new InspAttr().{ o.bind(self, key, null); o._ignore = true; }
        }
    }

    // InspAttr* color(const char *name){ }
    // InspAttr* path(const char *name){ }
    // InspAttr* image(const char *name){ }
    // InspAttr* method(void (*pFn)(void *_self), void *_self){ }

    Node* peekParent(){
        return self.curNodeStack.last()
    }

    // void test(){
    //     for each vt {
    //         mkPanel(o, 0).{
    //             for each mf in vt {
    //                 if mf.onInspectProperties {
    //                 }
    //                 mkLine().{
    //                     mkLabel(mf.name)
    //                     mkForm()
    //                 }
    //             }
    //         }
    //     }
    // }


    //收集Insp所需要的元数据
    void call_insp(){
        void **ptr = orc_getFieldPtr(self.obj, "insp")
        if (ptr != null){ //有此属性
            void (*onInspect)(Object* _self, Insp* insp);
            onInspect = *ptr;
            if (onInspect){
                onInspect(self.obj, self)
            }
        }
    }

    // //是否走默认的Insp流程
    // bool bInspDefault = true
    // //屏蔽默认的渲染
    // void preventDefault(){
    //     self.bInspDefault = false
    // }
    // // 默认情况下， call insp会收集字段 信息。 如果call insp内部想完全自定义，就需要preventDefault

    ^void (Insp* insp, Node* o) beforeInsp
    ^void (Insp* insp, Node* o) afterInsp
    //如果有，就替换掉默认的insp流程
    ^void (Insp* insp, Node* o) cbInsp


    void insp(Node* o, Object *obj){
        // self.bInspDefault = true
        self.obj = obj
        self.curNodeStack.clear()

        self.call_insp()

        // if !self.bInspDefault { //被屏蔽了
        //     return;
        // }

        if self.beforeInsp {
            self.beforeInsp(self, o)
        }

        if self.cbInsp {
            self.cbInsp(self, o)
        }
        else {
            self.inspObj(o, obj)
        }

        if self.afterInsp {
            self.afterInsp(self, o)
        }
    }
    void inspObj(Node* o, Object *obj){
        self.curNodeStack.push(o)

        Vtable_Object *vt = orc_getVtableByObject(obj)
        self.inspExtends(obj, vt)

        self.curNodeStack.pop()
    }
    //从父到子
    void inspExtends(Object *obj, Vtable_Object* vt){
        if vt == null{
            return
        }
        Vtable_Object* superVt = Vtable_getSuper(vt);
        self.inspExtends(obj, superVt)

        self.inspVt(obj, vt)
    }


    void inspVt(Object *obj, Vtable_Object* vt){
        OrcMetaField *mf = orc_getOrInitMeta(vt)

        TmpAttrInfo tmp
        tmp.init()

        Panel* panel = null
        LayoutLinear* ll = null

        while mf {
            //识别method
            //函数可以被组织成按钮
            InspAttr* attr = self.getAttr(mf.name)

            if attr && attr._ignore { 
                mf = OrcMetaField_getNext(mf)
                continue 
            }

            tmp.proc(mf, attr, self)

            //成组
            if tmp.isPanelStart {
                Node* parent = self.peekParent()
                panel = mkPanel(parent, (long long)mf)
                if panel.isNewForReact {
                    panel.open = false
                }
                panel.title = tmp.panelName
                panel.react()
                // panel.body.padding.setHor(12)

                self.curNodeStack.push(panel.body)
            }

            if tmp.isHboxStart {
                Node* parent = self.peekParent()
                ll = layoutLinear(parent, (long long)mf)
                ll.row().jcsb()
                // ll.backgroundColor = 0xffff0000
                // ll.height = 50
                self.curNodeStack.push(ll)
            }

            self.inspField(obj, mf)

            // 结束panel
            if tmp.isPanelEnd && panel {
                panel.end()
                self.curNodeStack.pop()
            }
            // 结束行
            if tmp.isHboxEnd && ll{
                ll.end()
                self.curNodeStack.pop()
            }

            mf = OrcMetaField_getNext(mf)
        }
    }
    void inspField(Object *obj, OrcMetaField *mf){
        if self.isSkipAttr(obj, mf) { return }

        // String@ curKeyPath = str(keyPath.str).add(".").add(mf.name)

        InspAttr* attr = self.getAttr(mf.name)

        Node *o = self.peekParent()

        //方法
        if mf.type == OrcMetaType_method {
            if String_startsWith(mf.name, "insp_"){
                mkDrawButton(o, (long long)mf).{
                    // o.margin.setHor(8)
                    o.text = str(mf.name+5)
                    // layoutLinearCell(o, 0).{ o.grow = 1}
                    o.onClick = ^void(MouseEvent *me){
                        void **ptr = orc_getFieldPtr(self.obj, mf.name)
                        if (ptr != null){ //有此属性
                            void (*inspFn)(Object* _self);
                            inspFn = *ptr;
                            if (inspFn){
                                inspFn(self.obj)
                            }
                        }
                    }
                    layoutLinearCell(o, 0).{
                        o.grow = 1
                        o.alignSelf.set("stretch")
                    }
                }
            }
            return
        }

        //按类型
        layoutLinear(o, (long long)mf).{
            const char *dir = self.queryAttrDirection(mf)
            o.border.b.set(1, 0x13000000)

            o.direction.set( dir)

            self.mkFieldName(o, mf.name)
            //有元信息
            if attr {
                attr.inspValue(o, obj, mf, self)
            }
            else {
                //值
                self.inspValueDefault(o, obj, mf)
            }
        }
    }

    // 查询属性的朝向。 是不是行，还是说需要换行
    const char* queryAttrDirection(OrcMetaField *mf){
        if mf {
            if 
                mf.metaStruct == metaStructOf(Bezier)
            {
                return "column"
            }
        }
        return "row"
    }
    //是否要忽略的属性
    bool isSkipAttr(Object *obj, OrcMetaField *mf){
        // 以下划线开头
        if String_startsWith(mf.name, "_") { return true; }


        InspLibItem* libItem = useInspLib().getByObject(obj)
        if libItem {
            return false
        }
        if OrcMetaField_isStringRef(mf) { return false }
        if OrcMetaField_isPrimitive(mf) { return false }

        if mf.metaStruct == metaStructOf(Vec2) { return false } 
        if mf.metaStruct == metaStructOf(Vec3) { return false } 
        if mf.metaStruct == metaStructOf(Vec4) { return false } 
        if mf.metaStruct == metaStructOf(Rgba) { return false } 
        if mf.metaStruct == metaStructOf(Bezier) { return false } 

        if mf.type == OrcMetaType_method {
            // insp 功能按钮
            if String_startsWith(mf.name, "insp"){
                return false;
            }
        }

        return true
    }

    void inspValueDefault(Node*o, Object *obj, OrcMetaField *mf){
        //有注册类型
        InspLibItem* libItem = useInspLib().getByObject(obj)
        if libItem {
            libItem.inspValue(o, obj, mf, self)
            return
        }

        // if self.inspColor(o, obj, mf) { return}
        // if self.inspImageSrc(o, obj, mf) { return}
        // if self.inspFilePath(o, obj, mf) { return}
        if self.inspString(o, obj, mf) { return}
        if self.inspIntColor(o, obj, mf) { return}
        if self.inspInt(o, obj, mf) { return}
        if self.inspFloat(o, obj, mf) { return}
        if self.inspBool(o, obj, mf) { return}
        if self.inspVec2(o, obj, mf) { return}
        if self.inspVec3(o, obj, mf) { return}
        if self.inspVec4(o, obj, mf) { return}
        if self.inspRgba(o, obj, mf) { return}
        if self.inspRgbaf(o, obj, mf) { return}
        if self.inspBezier(o, obj, mf) { return}
    }

    bool inspString(Node*o, Object *obj, OrcMetaField *mf){
        if !OrcMetaField_isStringRef(mf) { return false}

        String * s = *((String**)OrcMetaField_getPtr(mf, obj))
        mkEditText(o, 0).{
            o.padding.left = 4
            o.setValue(s == null ? str(""):s)
            o.onValueChanged = ^void (EditText* et){
                self.setAttr(mf, et.value)
            }

            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        return true
    }
    bool inspInt(Node*o, Object *obj, OrcMetaField *mf){
        if !(OrcMetaField_isPrimitive(mf) && (
            OrcMetaField_getType(mf) == OrcMetaType_int
        ))  {
            return false;
        }

        int * pv = OrcMetaField_getPtr(mf, obj)
        mkEditText(o, 0).{
            String@ val = str("")
            val.addi(*pv)

            o.padding.left = 4
            o.setValue(val)

            o.onValueChanged = ^void(EditText *et){
                printf("onValueChanged:%s\n", et.value.str)
                double nv = atof(et.value.str)
                printf("\t  double value:%f\n", nv);
                //设值
                self.setAttr(mf, mkDouble(nv))
            }

            layoutLinearCell(o, 0).{ o.grow = 1}
        }

        return true
    }
    bool inspFloat(Node*o, Object *obj, OrcMetaField *mf){
        if !(OrcMetaField_isPrimitive(mf) && OrcMetaField_getType(mf) == OrcMetaType_float) {
            return false;
        }

        float* pv = OrcMetaField_getPtr(mf, obj)
        mkEditText(o, 0).{
            String@ val = str("")
            val.addf(*pv)

            o.padding.left = 4
            o.setValue(val)

            o.onValueChanged = ^void(EditText *et){
                printf("onValueChanged:%s\n", et.value.str)
                double nv = atof(et.value.str)
                printf("\t  double value:%f\n", nv);
                //设值
                self.setAttr(mf, mkDouble(nv))
            }

            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        return true
    }
    bool inspBool(Node*o, Object *obj, OrcMetaField *mf){
        if !(OrcMetaField_isPrimitive(mf) && OrcMetaField_getType(mf) == OrcMetaType_bool)  {
            return false;
        }

        bool* pv = ((bool*)OrcMetaField_getPtr(mf, obj))
        layoutLinear(o, (long long)mf).{
            mkSwitch(o, 0).{
                o.setChecked(*pv)
                o.onCheckedChanged = ^void(Switch *v){
                    //设值
                    self.setAttr(mf, mkBoolean(v.checked))
                }
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }

        return true
    }
    bool inspVec2(Node*o, Object *obj, OrcMetaField *mf){
        if mf.metaStruct != metaStructOf(Vec2) { return false } 

        layoutLinear(o, (long long)mf).{
            Vec2 v = *((Vec2*)OrcMetaField_getPtr(mf, obj))

            mkEditText(o, 0).{
                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.x))
                o.border.setAll(1, 0xffff0000)

                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)

                    printf("set x:%f=>%f\n", v.x, nv)
                    v.x = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec2), &v))
                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            mkEditText(o, 0).{
                o.border.setAll(1, 0xff00ff00)

                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.y))
                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)
                    printf("set y:%f=>%f\n", v.y, nv)

                    v.y = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec2), &v))

                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        return true
    }
    bool inspVec3(Node*o, Object *obj, OrcMetaField *mf){
        if mf.metaStruct != metaStructOf(Vec3) { return false } 

        layoutLinear(o, (long long)mf).{
            Vec3 v = *((Vec3*)OrcMetaField_getPtr(mf, obj))

            mkEditText(o, 0).{
                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.x))
                o.border.setAll(1, 0x99ff0000)

                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)

                    printf("set x:%f=>%f\n", v.x, nv)
                    v.x = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec3), &v))
                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            mkEditText(o, 0).{
                o.border.setAll(1, 0x9900ff00)

                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4

                o.setValue_notInFocus(str("").addf(v.y))
                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)
                    printf("set y:%f=>%f\n", v.y, nv)

                    v.y = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec3), &v))

                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            mkEditText(o, 0).{
                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.z))
                o.border.setAll(1, 0xbb0000ff)

                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)

                    printf("set x:%f=>%f\n", v.z, nv)
                    v.z = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec3), &v))
                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        return true
    }
    bool inspVec4(Node*o, Object *obj, OrcMetaField *mf){
        if mf.metaStruct != metaStructOf(Vec4) { return false } 

        layoutLinear(o, (long long)mf).{
            Vec4 v = *((Vec4*)OrcMetaField_getPtr(mf, obj))

            mkEditText(o, 0).{
                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.x))
                o.border.setAll(1, 0xffff0000)

                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)

                    printf("set x:%f=>%f\n", v.x, nv)
                    v.x = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec4), &v))
                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            mkEditText(o, 0).{
                o.border.setAll(1, 0xff00ff00)

                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.y))
                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)
                    printf("set y:%f=>%f\n", v.y, nv)

                    v.y = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec4), &v))

                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            mkEditText(o, 0).{
                o.padding.left = 4
                o.margin.right = 8
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.z))
                o.border.setAll(1, 0xff0000ff)

                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)

                    printf("set x:%f=>%f\n", v.x, nv)
                    v.z = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec4), &v))
                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            mkEditText(o, 0).{
                o.padding.left = 4
                o.margin.bottom = 4
                o.setValue_notInFocus(str("").addf(v.w))
                o.border.setAll(1, 0xffff00ff)

                o.onValueChanged = ^void (EditText* et){
                    double nv = atof(et.value.str)

                    printf("set x:%f=>%f\n", v.x, nv)
                    v.w = nv;

                    self.setAttr(mf, mkStructObj(metaStructOf(Vec4), &v))
                }
                layoutLinearCell(o, 0).{ o.grow = 1}
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        return true
    }
    //int类型且以color结尾,不区分大小写
    bool inspIntColor(Node*o, Object *obj, OrcMetaField *mf){
        if !(
            OrcMetaField_isPrimitive(mf) 
            && ( OrcMetaField_getType(mf) == OrcMetaType_int)
            && (String_endsWithIgnoreCase(mf.name, "color")
            || String_endsWithIgnoreCase(mf.name, "Bg"))
        )  
        {
            return false;
        }

        int * pv = OrcMetaField_getPtr(mf, obj)

        mkColorPicker(o, 0).{
            o.backgroundColor = *pv;
            o.onChanged = ^void (int newcolor){
                self.setAttr(mf, mkInteger(newcolor))
            }
        }
        return true
    }
    bool inspRgbaf(Node*o, Object *obj, OrcMetaField *mf){
        if mf.metaStruct != metaStructOf(Rgbaf) { return false } 

        Rgbaf v = *((Rgbaf*)OrcMetaField_getPtr(mf, obj))

        mkColorPicker(o, 0).{
            o.backgroundColor = v.toInt()
            o.onChanged = ^void (int newcolor){
                Rgbaf nv = mkRgbafByInt(newcolor)
                self.setAttr(mf, mkStructObj(metaStructOf(Rgbaf), &nv))
            }
        }
        return true
    }
    bool inspRgba(Node*o, Object *obj, OrcMetaField *mf){
        if mf.metaStruct != metaStructOf(Rgba) { return false } 

        Rgba v = *((Rgba*)OrcMetaField_getPtr(mf, obj))

        mkColorPicker(o, 0).{
            o.backgroundColor = v.toInt()
            o.onChanged = ^void (int newcolor){
                Rgba nv = mkRgbaByInt(newcolor)
                self.setAttr(mf, mkStructObj(metaStructOf(Rgba), &nv))
            }
        }
        return true
    }
    bool inspBezier(Node*o, Object *obj, OrcMetaField *mf){
        if mf.metaStruct != metaStructOf(Bezier) { return false } 

        Bezier v = *((Bezier*)OrcMetaField_getPtr(mf, obj))
        mkBezierEditView(o, 0).{
            o.setBezier(v)

            o.margin.setHor(10)
            o.margin.setVer(10)
            o.height = 60
            o.onChanged = ^void (BezierEditView*view){
                Bezier nv = view.getBezier()
                self.setAttr(mf, mkStructObj(metaStructOf(Bezier), &nv))
            }

            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        return true
    }
    void mkFieldName(Node*o, const char *name){
        Theme* t = themeIns()
        mkTextView(o, 0).{
            // String@ s = str(name)
            o.setText(str(name))
            o.width = 100
            o.padding.setHor(8)
            // o.padding.left = 8
            o.color = t.insp_color
            o.setFont_size(t.insp_fontSize)
        }
    }

    ^void (Object* obj, OrcMetaField*mf, Object* inspValue) cbSetAttr

    void setAttrDefault(OrcMetaField*mf, Object* inspValue){
        Orc_setField(self.obj, mf, inspValue)
    }
    void setAttr(OrcMetaField*mf, Object* inspValue){
        // String@ tmp = keyPath.trimChars(".", true, true)
        // List@ segs = tmp.splitByRe("\\.")
        InspAttr* attr = self.getAttr(mf.name)
        if attr {

        }
        else {
        }

        if self.cbSetAttr {
            self.cbSetAttr(self.obj, mf, inspValue)
        }
        else {
            self.setAttrDefault(mf, inspValue)
        }


        EventInspAttrChanged@ evt = new EventInspAttrChanged()
        // evt.key = str(mf.name)
        evt.inspAttr = attr
        evt.mf = mf
        evt.obj = self.obj
        evt.newValue = inspValue
        useEbus().emit(evt)
    }

    // void buildInspItemTree(Object *obj){
    //     InspNode@ root = new InspNode()
    //     InspNode* cur = root

    //     Vtable_Object *vt = orc_getVtableByObject(self.obj)
    //     //遍历继承链
    //     while vt{
    //         OrcMetaField *mf = orc_getOrInitMeta(vt)

    //         //遍历 属性
    //         OrcMetaField *mf = orc_getOrInitMeta(vt)
    //         while mf {
    //             bool skip = false
    //             if String_startsWith(mf.name, "_") {//以下划线开头的，不构建表单
    //                 skip = true
    //             }

    //             //不跳过
    //             if !skip {
    //                 InspAttr* attr = self.getAttr(mf.name)
    //                 if attr {
    //                     //构建父子关系
    //                     if attr._panelName {
    //                         InspItem* panelItem = new InspItem()
    //                         cur.appendChild(panelItem)

    //                         cur = panelItem
    //                     }
    //                 }
    //                 else {
    //                     InspItem* item = new InspItem()
    //                 }
    //             }

    //             mf = OrcMetaField_getNext(mf)
    //         }


    //         vt = Vtable_getSuper(vt);
    //     }


    //     return items
    // }
}

class InspLibItem {
    String@ name = str("")
    void inspValue(Node* o, Object *obj, OrcMetaField *mf, Insp* insp){
    }
}
class InspLib {
    // className => InspLibItem
    Map@ nameMap = new Map()

    void bind(InspLibItem* item){
        self.nameMap.put(item.name.str, item)
    }
    InspLibItem* getByObject(Object *obj){
        Vtable_Object* vt = orc_getVtableByObject(obj)
        return self.getByVtable(vt)
    }
    InspLibItem* getByVtable(Vtable_Object *vt){
        InspLibItem* item = (InspLibItem*)self.nameMap.get(vt.className)
        return item
    }
}
InspLib* useInspLib(){
    static InspLib@ lib = null
    if lib == null {
        lib = new InspLib()
    }
    return lib
}

class TestObjSuper{
    int xx = 29
    int yy = 29
    int cc = 29
    int kk = 29
    void insp(Insp* insp){
        new InspAttr().{o.bind(insp, "xx", "group")}
        new InspAttr().{o.bind(insp, "yy", "group")}
    }
}
class TestObj extends TestObjSuper{
    int age = 10
    String@ name = str("hi there")

    float value = 3.4
    bool isMale = true
    Vec2 pos;
    Vec3 rotation
    Vec4 quat

    void insp(Insp* insp){
        super.insp(insp)
        new InspAttr().{o.bind(insp, "age", "group")}
        new InspAttr().{o.bind(insp, "name", "group")}

        new InspAttr().{o.bind(insp, "isMale", null)}

        new InspAttr().{o.bind(insp, "pos", "变换")}
        new InspAttr().{o.bind(insp, "rotation", "变换")}
        new InspAttr().{o.bind(insp, "quat", "变换")}

        insp.excludes("age pos name quat ")

        insp.beforeInsp = ^void(Insp*insp, Node* o){
            mkDrawButton(o, 0).{
                o.text = str("前置按钮")
            }
        }
        insp.afterInsp = ^void(Insp*insp, Node* o){
            layoutLinear(o, 0).{
                o.row().jcse().aic()
                o.padding.setVer(6)

                mkDrawButton(o, 0).{
                    o.width = 100
                    o.text = str("提交")
                    o.onClick = ^void(MouseEvent *me){
                        Toast_make("提交")
                    }
                }
                mkDrawButton(o, 0).{
                    o.width = 100
                    o.text = str("取消")
                }
                mkDrawButton(o, 0).{
                    o.width = 100
                    o.text = str("上传")
                }
                mkDrawButton(o, 0).{
                    o.width = 100
                    o.text = str("控制")
                }
            }
        }
    }

    void insp1_say(){
        Toast_make("hi")
        printf("say hi\n")
    }
    void insp1_say2(){
        Toast_make("hi2")
        printf("say hi\n")
    }
    void insp0_say2(){
        printf("say hi\n")
        Toast_make(str("hi3:").add(self.name.str).str)
    }
}

//构建Float3控件
void Insp_mkVec2(Node*o, long long key, Vec2 v, ^void (Vec2 nv) set){
    layoutLinear(o, (long long)key).{
        // Vec3 v = *((Vec3*)OrcMetaField_getPtr(mf, obj))

        mkEditText(o, 0).{
            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4
            o.setValue_notInFocus(str("").addf(v.x))
            o.border.setAll(1, 0x99ff0000)

            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)

                printf("set x:%f=>%f\n", v.x, nv)
                v.x = nv;

                set(v)
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        mkEditText(o, 0).{
            o.border.setAll(1, 0xbb00ff00)

            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4

            o.setValue_notInFocus(str("").addf(v.y))
            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)
                printf("set y:%f=>%f\n", v.y, nv)

                v.y = nv;
                set(v)

            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }

        layoutLinearCell(o, 0).{ o.grow = 1}
    }
}
void Insp_mkVec3(Node*o, long long key, Vec3 v, ^void (Vec3 nv) set){
    layoutLinear(o, (long long)key).{
        // Vec3 v = *((Vec3*)OrcMetaField_getPtr(mf, obj))

        mkEditText(o, 0).{
            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4
            o.setValue_notInFocus(str("").addf(v.x))
            o.border.setAll(1, 0x99ff0000)

            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)

                printf("set x:%f=>%f\n", v.x, nv)
                v.x = nv;

                set(v)
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        mkEditText(o, 0).{
            o.border.setAll(1, 0xbb00ff00)

            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4

            o.setValue_notInFocus(str("").addf(v.y))
            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)
                printf("set y:%f=>%f\n", v.y, nv)

                v.y = nv;
                set(v)

            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        mkEditText(o, 0).{
            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4
            o.setValue_notInFocus(str("").addf(v.z))
            o.border.setAll(1, 0xff0000ff)

            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)

                printf("set x:%f=>%f\n", v.z, nv)
                v.z = nv;
                set(v)
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        layoutLinearCell(o, 0).{ o.grow = 1}
    }
}
void Insp_mkVec4(Node*o, long long key, Vec4 v, ^void (Vec4 nv) set){
    layoutLinear(o, (long long)key).{
        // Vec3 v = *((Vec3*)OrcMetaField_getPtr(mf, obj))

        mkEditText(o, 0).{
            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4
            o.setValue_notInFocus(str("").addf(v.x))
            o.border.setAll(1, 0xffff0000)

            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)

                printf("set x:%f=>%f\n", v.x, nv)
                v.x = nv;

                set(v)
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        mkEditText(o, 0).{
            o.border.setAll(1, 0xff00ff00)

            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4

            o.setValue_notInFocus(str("").addf(v.y))
            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)
                printf("set y:%f=>%f\n", v.y, nv)

                v.y = nv;
                set(v)

            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        mkEditText(o, 0).{
            o.padding.left = 4
            o.margin.right = 8
            o.margin.bottom = 4
            o.setValue_notInFocus(str("").addf(v.z))
            o.border.setAll(1, 0xff0000ff)

            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)

                printf("set x:%f=>%f\n", v.z, nv)
                v.z = nv;
                set(v)
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        mkEditText(o, 0).{
            o.padding.left = 4
            o.margin.bottom = 4
            o.setValue_notInFocus(str("").addf(v.w))
            o.border.setAll(1, 0xffff00ff)

            o.onValueChanged = ^void (EditText* et){
                double nv = atof(et.value.str)

                printf("set w:%f=>%f\n", v.x, nv)
                v.w = nv;
                set(v)
            }
            layoutLinearCell(o, 0).{ o.grow = 1}
        }
        layoutLinearCell(o, 0).{ o.grow = 1}
    }
}
void testInsp(){
    printf("hi insp\n")
    new Window().{ 
        Window* win = o
        // o.borderless = true
        // o.setTransparent()

        new ScrollArea().{
            o.backgroundColor = 0
            win.setRootView(o)
            o.aiStretch()

            layoutLinear(o, 0).{

                o.column().jcs().aiStretch()
                o.backgroundColor = 0x99efefff

                // mkTextView(o, 0).{
                //     o.backgroundColor = 0x99ff0000
                //     o.padding.setAll(8)
                //     o.radius.setAll(4)
                //     o.color = 0xffffffff
                //     o.setText(str("你好"))
                // }
                TestObj@ obj = new TestObj()

                Insp@ insp = new Insp()
                insp.insp(o, obj)


                useEbus().cbOnEvent = ^void(Event*e){
                    printf("收到事件:%s\n", orc_getVtableByObject(e).className)
                    printf("TestObj:%d %s. value:%f, isMale:%d\n", obj.age, obj.name.str, obj.value, obj.isMale)
                    printf("pos:%f,%f\n", obj.pos.x, obj.pos.y)
                    printf("rotation:%f,%f,%f\n", obj.rotation.x, obj.rotation.y, obj.rotation.z)
                    printf("quat:%f,%f,%f,%f\n", obj.quat.x, obj.quat.y, obj.quat.z, obj.quat.w)
                }
            }
        }

        // new LayoutLinear().{
        // }



        // ((View*)o.rootView).{
        //     o.backgroundColor = 0x99efefff
        // }
        // o.setTransparent()
        o.setTitle("检视器")
        o.setSize(640, 480)
        o.moveToCenter()
        o.show()
    }
}