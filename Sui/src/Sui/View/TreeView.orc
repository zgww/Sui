package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../Core/Node.orc"
// import * from "../Core/View.orc"
import * from "./ViewBuilder.orc"
import * from "./TextView.orc"
import * from "./HoverViewEffect.orc"
import * from "../Core/Event.orc"
import * from "../Core/MouseEvent.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/String.orc"
import * from "../Dialog/MessageDialog.orc"
 

class TreeState {
    List@ roots 
    ^String@ (Object *item) getId
    ^List@ (Object *item) getItemChildren
    ^void (TreeState *state) cbSelectedIdChanged

    //选中状态
    List@ selectedIds = new List()
    //打开状态
    List@ opendIds = new List()

    Object* getById(String@ id){
        Object *obj = self._getById(id, self.roots)
        return obj;
    }

    void _flatTree(List@ items, List* out){
        if !items || !self.getId {
            return
        }
        int l = items.size()
        for int i = 0; i < l; i++{
            Object* item = items.get(i)
            String@ id = self.getId(item)
            out.add(id)

            if self.getItemChildren{
                List@ kids = self.getItemChildren(item)
                self._flatTree(kids, out)
            }
        }
    }
    List@ flatTree(){
        List@ ret = new List()
        self._flatTree(self.roots, ret)
        return ret
    }


    Object* _getById(String@ id, List* list){
        if (!id){
            return null
        }
        if (!list){
            return null;
        }
        int l = list.size()
        for (int i = 0; i < l; i++){
            Object *obj = list.get(i)
            String@ curId = self.getId(obj)
            if (id.equalsString(curId)){
                return obj
            }
            List@ children = self.getItemChildren(obj)
            obj = self._getById(id, children)
            if (obj){
                return obj;
            }
        }
        return null
    }

    //取得第一个选中的对象
    Object* getFirstSelected(){
        String@ id = (String@)self.selectedIds.get(0)
        Object *obj = self.getById(id)
        return obj
    }

    bool isSelected(Object *item){
        return self.selectedIds.has(self.getId(item))
    }
    bool isOpend(Object *item){
        return self.opendIds.has(self.getId(item))
    }

    //支持多选
    void setSelectedWithShiftAndCtrl(Object*item, bool shift, bool ctrl){
        if !shift && !ctrl {
            self.setSelected(item)
            return
        }
        if ctrl {
            if (item != null){
                String@ id = self.getId(item)
                self.selectedIds.add(id)
                self.fire_cbSelectedIdChanged()
            }
            return
        }
        if shift {
            if self.selectedIds.size() == 0 {
                self.setSelected(item)
                return
            }

            //多选
            List@ flatIds = self.flatTree()
            String@ lastId = (String@)self.selectedIds.last()
            self.selectedIds.clear()
            String@ id = self.getId(item)
            int index0 = 0
            int index1 = 0
            int status = 0

            //从第一个加到后个
            for (int i = 0; i < flatIds.size(); i++){
                String@ curId = (String@)flatIds.get(i)
                if curId.equalsString(lastId) || curId.equalsString(id){
                    if status == 0{
                        index0 = i
                        status ++
                    }
                    else {
                        status ++
                        index1 = i
                    }
                }
                if status >= 1 {
                    self.selectedIds.add(curId)
                }


                if status == 2{
                    break;
                }
            }
            self.selectedIds.add(lastId)
            self.fire_cbSelectedIdChanged()
        }
    }
    void fire_cbSelectedIdChanged(){
        if (self.cbSelectedIdChanged){
            self.cbSelectedIdChanged(self)
        }
    }

    void setSelected(Object *item){
        self.selectedIds.clear()
        if (item != null){
            String@ id = self.getId(item)
            self.selectedIds.add(id)

            self.fire_cbSelectedIdChanged()
        }
    }
    void setOpen(Object *item, bool open){
        String@ id = self.getId(item)
        if (open){
            self.opendIds.addOnce(id)
        } else {
            self.opendIds.remove(id)
        }
    }

}
/// 树视图
class TreeView extends LayoutLinear {
    TreeState@ state = new TreeState()
    ^void (Node *o, Object *item, int deep) reactItem
    ^void (Event *e, ViewBase *o, Object*item) cbOnEvent_forItemView

    void ctor(){
        super.ctor()
        // self.backgroundColor = 0x09ff00000
        self.direction.set("column")
        self.alignItems.set("start")
    }

    void react(){

        self.startInnerReact()
        Node *o = self

        self.reactChildren(self, self.state.roots, 0)

        self.endInnerReact()
        self.invalidLayout()
    }

    void reactChildren(Node *parent, List *items, int deep){
        if (items == null){
            return
        }
        // printf("reactChildren %d. open sized:%d\n", 
        //     items.size(), self.state.opendIds.size());

        int l = items.size()

        for (int i = 0; i < l; i++){
            Object *item = items.get( i)
            bool isOpend = self.state.isOpend(item)


            layoutLinear(parent, ((long long)item) + deep * 1000 +i).{
                o.cbOnEvent = ^void (Event *e){
                    if (e instanceof MouseEvent){
                        MouseEvent *me = (MouseEvent*)e 
                        //点击选中
                        if (me.isClickInBubble() && me.button == 1){
                            self.state.setSelectedWithShiftAndCtrl(item, me.shift, me.ctrl)
                            self.invalidReact()
                        }
                        //双击可以展开
                        if (me.isDblClickInBubble()){
                            // MessageDialog_alert("hi", "tip")
                            self.state.setOpen(item, !self.state.isOpend(item))
                            self.invalidReact()
                        }
                    }
                    if self.cbOnEvent_forItemView{
                        self.cbOnEvent_forItemView(e, o, item)
                    }
                }

                o.padding.left = deep * 20
                bool isSelected = self.state.isSelected(item)
                o.backgroundColor = isSelected ? 0x330088ff : 0x00000000//i % 2 == 0 ? 0x0f000000 : 0x00000000
                o.height = 20
                o.alignItems.set("center")
                o.justifyContent.set("start")


                if (self.reactItem != null){
                    self.reactItem(o, item, deep)
                }
                else {
                    mkTextView(o, 0).{
                        o.setText(str("item-").addi(i))
                    }
                }
            }
            if (self.state.isOpend(item)){
                List@ kids = self.state.getItemChildren(item)
                self.reactChildren(parent, kids, deep + 1)
            }
        }
    }
}

TreeView@ mkTreeView(void* parent, long long key){
    return (TreeView@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, TreeView)
}