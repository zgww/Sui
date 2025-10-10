package SuiDesigner

#include "../Orc/Orc.h"
#include <stdio.h>
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



// 思路：
// 有vnode, 有node, 
// 从Node的元数据里提取
// 参考godot
// 从类、父类、...一层层的属性渲染出表单,每层都是单独的Panel
// 暂不考虑对齐？
// 不同类型的属性、数值，采用不同的表单控件,如输入框、switch、select、颜色选择、路径选择、图片渲染与选择、曲线、数组、动态对象、表格
// 对于自定义的支持：允许类有自定义面板的功能呗

// 为追求灵活性, inspector需要能
// [o] 整体被覆盖
// [ ] 特定类 被 覆盖
// [o] 个别属性被覆盖

// [o] 也可以单独调用去渲染一个类的直接属性，
// [o] 可以单独调用去渲染一个类及继承链的属性
// [o] 也可以单独调用去渲染一个属性

// [] 也可以单独定制某个类型值的的渲染.类型指定指定函数onInspect
// [] 也可以单独定制某个属性的渲染

// [] 支持给类型提供inspect
// [] 支持给如int之类的相同类型提供不同的inspect

// [] 需要有共同的Label?


// target指代目标对象, insp的调用链:
// 入口：target.inspect(ctx)
// 默认target.inspect调用ctx.inspectExtendsChain(obj, Orc_getVtableObject(obj))
// 如果想完全覆盖（完全定制渲染逻辑）, 那target内部不要调用ctx.inspectExtendsChain即可


class InspectorOption {
    int value;
    String@ label;
}
//由属性附加更多信息
class InspectorAttrInfo {
    String@ key = str("")
    bool bColor = false
    //图片路径
    bool bImageSrc = false
    // 文件路径
    bool bFileSrc = false
    // 下拉
    bool bSelect = false

    // slider
    bool bSlider = false
    float fromValue = 0.0
    float toValue = 0.0

    List@ options = null

    List@ gocOptions(){
        if !self.options {
            self.options = new List()
        }
        return self.options
    }
    void setOption(int value, const char* label){
        List@ opts = self.gocOptions()
        for int i = 0; i < opts.size(); i++{
            InspectorOption* opt = (InspectorOption*)opts.get(i)
            if opt.value == value{
                opt.label = str(label);
                return
            }
        }

        InspectorOption@ opt = new InspectorOption()
        opt.value = value
        opt.label = str(label)
        opts.add(opt)
    }
    List@ getOptionLabels(){
        List@ labels = new List()
        if self.options {
            for int i = 0; i < self.options.size(); i++{
                InspectorOption* opt = (InspectorOption*)self.options.get(i)
                labels.add(opt.label)
            }
        }
        return labels
    }
}

//检视器
class Inspector{
    //目标对象
    Object@ obj
    //设值回调
    ^void (Object *obj, const char *key, Object* value) cbSetField;

    //生成Inspector面板的父结点
    Node@ parentNode

    Map@ attrInfoMap = new Map()


    //启用默认的渲染逻辑
    //如果用户类想完全自定义，就可以在inspect
    bool useDefaultInspect = true


    void reset(){
        self.obj = null
        self.parentNode = null
        self.useDefaultInspect = false
    }

    InspectorAttrInfo* getAttrInfo(const char *key){
        return (InspectorAttrInfo*)self.attrInfoMap.get(key)
    }

    InspectorAttrInfo@ gocAttrInfo(const char *key){
        {
            InspectorAttrInfo* exist = self.getAttrInfo(key)
            if exist {
                return exist
            }
        }
        InspectorAttrInfo@ info = new InspectorAttrInfo()
        info.key.set(key)
        self.attrInfoMap.put(key, info)
        return info
    }
    void markAttrAsColor(const char *key){
        InspectorAttrInfo@ info  = self.gocAttrInfo(key)
        info.bColor = true
    }
    void markAttrAsImageSrc(const char *key){
        InspectorAttrInfo@ info  = self.gocAttrInfo(key)
        info.bImageSrc = true
    }
    void markAttrAsFileSrc(const char *key){
        InspectorAttrInfo@ info  = self.gocAttrInfo(key)
        info.bFileSrc = true
    }
    void markAttrAsSlider(const char *key, float fromValue, float toValue){
        InspectorAttrInfo@ info  = self.gocAttrInfo(key)
        info.bSlider = true
        info.fromValue = fromValue
        info.toValue = toValue
    }
    //标记为select
    InspectorAttrInfo@ markAttrAsSelect(const char *key){
        InspectorAttrInfo@ info  = self.gocAttrInfo(key)
        info.bSelect = true
        // info.setOption(value, label)
        return info
    }
    void clearAttrInfoMap(){
        self.attrInfoMap.clear()
    }

    //统一入口，进入设值
    void setField(Object *obj, const char *key, Object *value){
        if (self.cbSetField){
            self.cbSetField(obj, key, value)
            return;
        }
        // Vtable_Object *vt = orc_getVtableByObject(obj)
        OrcMetaField *mf = orc_getMetaFieldByObject(obj, key)
        if (mf){
            int addr = OrcMetaField_getAddress(mf)
            int type = OrcMetaField_getType(mf)
            void * p = ((char*)obj)+addr
            if (value instanceof Number){
                Number *num = (Number*)value
                if (type == OrcMetaType_bool){
                    bool *pv = (bool*)p;
                    *pv = num.toInt() != 0
                }
                else if (type == OrcMetaType_int){
                    int *pv = (int*)p;
                    *pv = num.toInt()
                }
                else if (type == OrcMetaType_float){
                    float *pv = (float*)p;
                    *pv = num.toDouble()
                }
            }
            if (obj instanceof Node){
                Node *node = (Node*)obj;
                node.invalidReact()
            }
        }

        //通用的设值逻辑
    }


    //检视继承链
    void reactObject_withExtendsChain(Node* parentNode, Object* obj, Vtable_Object *vt){
        if obj == null {
            return
        }

        int idx = 0

        while (vt){
            self.reactObject_byVtable(parentNode, self.obj, vt, idx)
            idx ++
            //取父类
            vt = Vtable_getSuper(vt);
        }
    }

    void reactObject(Node* parentNode){
        self.parentNode = parentNode


        //取得自定义的检视函数
        //void onInspect(Node *parent)
        // self.callCustom_onInspect()
        // self._call_onInspect()

        Vtable_Object *vt = orc_getVtableByObject(self.obj)

        //逐继承类检视
        self.reactObject_withExtendsChain(parentNode, self.obj, vt)
    }


    // 入口函数
    void inspect(Node *parentNode, Object *obj){
        self.reset()

        self.obj = obj
        self.parentNode = parentNode

        self.clearAttrInfoMap()


        self.callOnInspect()

        //默认的检视逻辑
        if self.useDefaultInspect {
            self.reactObject(parentNode)
        }
    }


    void callOnInspect(){
        void **ptr = orc_getFieldPtr(self.obj, "onInspect")
        if (ptr != null){ //有此属性
            void (*onInspect)(Object* _self, Inspector* insp);
            onInspect = *ptr;
            if (onInspect){
                onInspect(self.obj, self)
            }
        }
    }

    // extern void callCustom_onInspect()
    // void _call_onInspect(){
    //     OrcMetaField *mf = orc_getMetaFieldByObject(self.obj, "onInspect");
    //     if (mf){
    //         int addr = OrcMetaField_getAddress(mf);
    //         void (**onInspect)(Object *self, void *parent) = (void*)  (((char*)self->obj) + addr);
    //         (*onInspect)(self->obj, self);
    //     }
    // }

    int countFieldsOfVtable(Vtable_Object *vt){
        int cnt = 0
        OrcMetaField *mf = orc_getOrInitMeta(vt)
        while (mf){
            const char *name = OrcMetaField_getName(mf)
            if (String_startsWith(name, "_")){//以下划线开头的，不构建表单
            }
            else{
                cnt ++

            }
            mf = OrcMetaField_getNext(mf);
        }
        return cnt
    }
    
    // 按vtable 构建insp视图
    void reactObject_byVtable(Node* o, Object *_obj, Vtable_Object *vt, int vtIdx){
        Object@ obj = _obj;
        Vtable_Object *vtable = vt;
        OrcMetaField *headmf = orc_getOrInitMeta(vt)

        // int fieldsCount = self.countFieldsOfVtable(vt)
        // if fieldsCount <= 0 {
        //     return
        // }

        mkPanel(o, ((long long) _obj) + vtIdx).{
            o.cbRenderTitle = ^void(Node *o){
                mkTextView(o, 0).{
                    o.setText(str(Vtable_getClassName(vtable)))
                }
            }
            o.cbRenderContent = ^void(Node *parent){
                // Node@ o = parent
                // mkTextView(parent, 0).{
                //     o.setText(str("content"))
                // }

                OrcMetaField *mf = headmf
                while (mf){
                    self.reactObjectField(parent, obj, vtable, mf)
                    mf = OrcMetaField_getNext(mf);
                }
            }
        }

    }

    // 属性 行
    void reactObjectField(Node* o, Object *obj, Vtable_Object *vt, OrcMetaField *mf){
        const char *name = OrcMetaField_getName(mf)
        Object *tmpObj = obj
        if (String_startsWith(name, "_")){//以下划线开头的，不构建表单
            return;
        }
        self.reactObjectField_do(o, obj, vt, mf)
    }
    void reactObjectFieldName(Node* o, Object *obj, Vtable_Object *vt, OrcMetaField *mf){
        const char *name = OrcMetaField_getName(mf)
        mkTextView(o, 0).{
            // String@ s = str(name)
            o.setText(str(name))
            o.width = 120
            o.margin.right = 10
        }
    }
    void reactObjectFieldRow(Node* o, Object *obj, Vtable_Object *vt, OrcMetaField *mf, ^void (Node* o) renderBody){
        layoutLinear(o, (long long)mf).{
            self.reactObjectFieldName(o, obj, vt, mf)

            renderBody(o)
        }
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

    void reactObjectField_do(Node* o, Object *obj, Vtable_Object *vt, OrcMetaField *mf){
        Object *tmpObj = obj
        const char *name = OrcMetaField_getName(mf)
        InspectorAttrInfo* info = self.getAttrInfo(name)

        if info{
            // sizeof(Vec2)
            if info.bSlider {
                // self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                layoutLinear(o, (long long)mf).{
                    self.reactObjectFieldName(o, obj, vt, mf)

                    mkSlider(o,0).{
                        // o.margin.right = 40
                        // o.margin.left = 20
                        o.fromValue = info.fromValue
                        o.toValue = info.toValue
                        o.onChanged = ^void(int i, String@ label){
                            // Toast_make(str("on select:").addString(label).str)
                            setAttr(name, Json_mkString(label))
                        }
                        layoutLinearCell(o, 0)
                    }
                    // mkView(o, 0).{
                    //     o.backgroundColor = 0xff00ffff
                    //     o.height = 10
                    //     layoutLinearCell(o, 0)
                    // }
                }
                return
            }
            if info.bSelect {
                // self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                layoutLinear(o, (long long)mf).{
                    self.reactObjectFieldName(o, obj, vt, mf)

                    mkSelect(o,0).{
                        o.options = info.getOptionLabels()
                        o.onChanged = ^void(int i, String@ label){
                            // Toast_make(str("on select:").addString(label).str)
                            setAttr(name, Json_mkString(label))
                        }
                    }

                }
                return
            }
            if info.bImageSrc {
                if 0{
                    return
                }
                // self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                layoutLinear(o, (long long)mf).{
                    self.reactObjectFieldName(o, obj, vt, mf)

                    layoutLinear(o, (long long)mf).{
                        o.direction.set("column")
                        o.alignItems.set("start")

                        String* src = *((String**)OrcMetaField_getPtr(mf, obj))
                        mkImageView(o, 0).{
                            o.width = 100
                            o.height = 100
                            o.setImageMode ( WrapContent )
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
                                            setAttr(name, Json_mkString(newpath))
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
                // })
                return
            }

            if info.bFileSrc {
                // self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                layoutLinear(o, (long long)mf).{
                    self.reactObjectFieldName(o, obj, vt, mf)

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
                                    setAttr(name, Json_mkString(newpath))
                                }
                                fc.showWindow()
                            }
                        }
                        // mkImageView(o, 0).{
                        //     o.width = 100
                        //     o.height = 100
                        //     o.setImageMode = WrapContent
                        //     o.border.setAll(1, 0xff999999)
                        //     o.setSrc(src)
                        //     o.cursor.set("pointer")
                        //     o.cbOnEvent = ^ void(Event *e){
                        //         if e instanceof MouseEvent {
                        //             MouseEvent *me = (MouseEvent*)e;
                        //             if me.button == 1 && me.isClickInBubble(){
                        //                 // Toast_make(str("click image").addString(src).str)
                        //                 FileChooser@ fc = new FileChooser()
                        //                 fc.use_filterImage()
                        //                 fc.loadPaths()
                        //                 fc.onChoose = ^ void(String@ newpath){
                        //                     setAttr(name, Json_mkString(newpath))
                        //                 }
                        //                 fc.showWindow()
                        //             }
                        //         }

                        //     }
                        // }
                        // mkTextView(o, 0).{
                        //     o.setText(src)
                        // }
                    }
                }
                // })
                return
            }
            if info.bColor {
                self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                    // mkView(o, 0).{
                    //     o.width = 14
                    //     o.height = 14
                    //     o.border.setAll(2, 0xffffffff)
                    //     // o.border.setAll(1, 0xff000000)
                    //     o.backgroundColor = 0xffff0000
                    // }
                    mkColorPicker(o, 0).{
                        int* pColor = OrcMetaField_getIntPtr(mf, obj)

                        o.backgroundColor = *pColor;
                        o.onChanged = ^void (int newcolor){
                            EditCtx@ ctx = EditCtx_ins()
                            ANode* sel = (ANode*)ctx.state.getFirstSelected()
                            if sel {
                                sel.setAttr(name, Json_mkNumber(newcolor))
                                
                                new EventANodeAttrChanged().{
                                    o.anode = sel
                                    o.emitToEbus()
                                }
                            }

                        }

                    }
                })
                // layoutLinear(o, (long long)mf).{
                //     self.reactObjectFieldName(o, obj, vt, mf)
                //     mkView(o, 0).{
                //         o.width = 14
                //         o.height = 14
                //         o.border.setAll(2, 0xffffffff)
                //         // o.border.setAll(1, 0xff000000)
                //         o.backgroundColor = 0xffff0000
                //     }
                // }
                return
            }
        }

        //字符串引用
        if (OrcMetaField_isStringRef(mf)){
            self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                int addr = OrcMetaField_getAddress(mf)
                void * p = ((char*)obj)+addr
                String * s = *(String**)p;


                mkEditText(o, 0).{
                    o.padding.left = 4
                    o.setValue(s == null ? str(""):s)
                    o.onValueChanged = ^void (EditText* et){


                        EditCtx@ ctx = EditCtx_ins()
                        ANode* sel = (ANode*)ctx.state.getFirstSelected()
                        if sel {
                            sel.setAttr(name, Json_mkString(et.value))
                            
                            new EventANodeAttrChanged().{
                                o.anode = sel
                                o.emitToEbus()
                            }
                        }

                    }

                    layoutLinearCell(o, 0).{ o.grow = 1}
                }
            })
        }
        else if (OrcMetaField_isPrimitive(mf)){
            self.reactObjectFieldRow(o,  obj, vt, mf, ^void (Node *o){
                int type = OrcMetaField_getType(mf)
                int addr = OrcMetaField_getAddress(mf)
                void * p = ((char*)obj)+addr
                if (type == OrcMetaType_bool){
                    bool *pv = (bool*)p;
                    mkSwitch(o, 0).{
                        o.setChecked(*pv)
                        o.onCheckedChanged = ^void(Switch *v){
                            //设值
                            self.setField(tmpObj, name, mkBoolean(v.checked))
                        }
                    }
                }
                else if (type == OrcMetaType_int){
                    int *pv = (int*)p;
                    mkEditText(o, 0).{
                        o.padding.left = 4
                        String@ val = str("")
                        val.addi(*pv)
                        o.setValue(val)
                        o.onValueChanged = ^void(EditText *et){
                            printf("onValueChanged:%s\n", et.value.str)
                            double nv = atoi(et.value.str)
                            printf("\t  int value:%f\n", nv);
                            //设值
                            self.setField(tmpObj, name, mkInteger(nv))
                        }

                        layoutLinearCell(o, 0).{ o.grow = 1}
                    }
                }
                else if (type == OrcMetaType_float){
                    float *pv = (float*)p;
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
                            self.setField(tmpObj, name, mkDouble(nv))
                        }

                        layoutLinearCell(o, 0).{ o.grow = 1}
                    }
                }
                else {
                    mkEditText(o, 0).{
                        o.padding.left = 4
                        layoutLinearCell(o, 0).{ o.grow = 1}
                    }
                }
            })
        }
    

        if mf.metaStruct == metaStructOf(Vec2) {
            layoutLinear(o, (long long)mf).{
                self.reactObjectFieldName(o, obj, vt, mf)

                Vec2 v = *((Vec2*)OrcMetaField_getPtr(mf, obj))
                
                mkEditText(o, 0).{
                    o.padding.left = 4
                    o.setValue_notInFocus(str("").addf(v.x))
                    o.onValueChanged = ^void (EditText* et){
                        double nv = atof(et.value.str)
                        printf("set x:%f=>%f\n", v.x, nv)
                        Json@ jo = Json_mkObject()
                        jo.putNumber("x", nv)
                        jo.putNumber("y", v.y)
                        setAttr(name, jo)
                    }
                    layoutLinearCell(o, 0).{ o.grow = 1}
                }
                mkEditText(o, 0).{
                    o.padding.left = 4
                    o.setValue_notInFocus(str("").addf(v.y))
                    o.onValueChanged = ^void (EditText* et){
                        double nv = atof(et.value.str)
                        printf("set y:%f=>%f\n", v.y, nv)

                        Json@ jo = Json_mkObject()
                        jo.putNumber("x", v.x)
                        jo.putNumber("y", nv)
                        setAttr(name, jo)
                    }
                    layoutLinearCell(o, 0).{ o.grow = 1}
                }
            }

            return
        }

        if mf.metaStruct == metaStructOf(Bezier) {
            layoutLinear(o, (long long)mf).{
                // o.direction.set("column")
                self.reactObjectFieldName(o, obj, vt, mf)

                Bezier v = *((Bezier*)OrcMetaField_getPtr(mf, obj))
                
                mkBezierEditView(o, 0).{
                    if !o.drag.isDragging {
                        o.start = v.start
                        o.c0 = v.c0
                        o.c1 = v.c1
                        o.end = v.end
                    }
                    o.margin.setHor(10)
                    o.margin.setVer(10)
                    o.height = 60
                    o.onChanged = ^void (BezierEditView*view){
                        Json@ start = Json_mkObject()
                        start.putNumber("x", view.start.x)
                        start.putNumber("y", view.start.y)

                        Json@ c0 = Json_mkObject()
                        c0.putNumber("x", view.c0.x)
                        c0.putNumber("y", view.c0.y)

                        Json@ c1 = Json_mkObject()
                        c1.putNumber("x", view.c1.x)
                        c1.putNumber("y", view.c1.y)

                        Json@ end = Json_mkObject()
                        end.putNumber("x", view.end.x)
                        end.putNumber("y", view.end.y)


                        Json@ jo = Json_mkObject()
                        jo.put("start", start)
                        jo.put("c0", c0)
                        jo.put("c1", c1)
                        jo.put("end", end)

                        setAttr(name, jo)
                    }

                    layoutLinearCell(o, 0).{ o.grow = 1}
                }
            }

            return
        }
    }


    ^void (const char *name, Json@ jv) setAttr
}

static void setAttr(const char *name, Json@ jv){
    EditCtx@ ctx = EditCtx_ins()
    ANode* sel = (ANode*)ctx.state.getFirstSelected()
    if sel {
        sel.setAttr(name, jv)
        
        new EventANodeAttrChanged().{
            o.anode = sel
            o.emitToEbus()
        }
    }
}