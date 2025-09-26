package SuiCore
#include "../../Orc/Orc.h"
#include <stdio.h>

import * from "./Emitter.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Map.orc"
import * from "../../Orc/Time.orc"
import * from "../../Orc/ScopeData.orc"
import * from "../../Orc/String.orc"
import type * from "./Window.orc"
import * from "./Timer.orc"
 


// typedef struct Window Window

//节点react脏标识
int Node_gReactDirty = true


//内部react时，有自己的unusedMap
class InnerReact {
    Map@ old_unusedMap
    Map@ old_map
    Map@ unusedMap = new Map()
    Map@ map = new Map()
    int _appendIndexForReact = 0
}

 
class Node extends Emitter {
    char key[32]

    List@ children = new List()

    Node@ parent = null
    //react需要记录哪些节点是未使用的
    Map@ _mapForReact = null
    //react时，会从unusedMapForReact搬到_mapForReact, 最后clean时，再交换
    Map@ _unusedMapForReact = null
    //react时，记录当前节点应该附加的位置
    int _appendIndexForReact = 0
    bool isNewForReact = true //是不是react新建的

    String@ name = str("")

    InnerReact@ innerReact = null
    //用户数据
    Object@ userdata

    // 是否有内部的react
    // 如果有内部的react,那么外部react时，会先将children暂放到临时列表中，最后由内部的react放到最终位置
    bool hasInnerReact = false

    // outReact使用的临时的children
    List@ outKids


    void startInnerReact(){
        if (!self.innerReact) {
            self.innerReact = new InnerReact()
        }
        InnerReact *ir = self.innerReact
        self.innerReact.old_unusedMap = self._unusedMapForReact
        self.innerReact.old_map = self._mapForReact
        
        self._unusedMapForReact = self.innerReact.unusedMap
        self._mapForReact = self.innerReact.map
        
        self._appendIndexForReact = 0;
    }

    void endInnerReact(){
        int idx = self._appendIndexForReact;
        self.clearUnusedKids()
        self._appendIndexForReact = idx;

        self.innerReact.unusedMap = self._unusedMapForReact
        self.innerReact.map = self._mapForReact

        self._unusedMapForReact = self.innerReact.old_unusedMap
        self._mapForReact = self.innerReact.old_map
    }


    //是否已挂载
    bool mounted = false

    void setMounted(bool mounted) {
        if (self->mounted == mounted) {
            return;
        }

        self->mounted = mounted;
        int l = self.getChildrenCount()
        for (int i = 0 ; i < l; i++) {
            Node *n = self.getChild(i);
            n->setMounted(mounted);
        }

        //后根
        if (self.mounted) {
            self.baseOnMounted();
        }
        else {
            self.baseOnUnmounting();
        }
    }
    void baseOnMounted() {
        if (self.parent != null) { //window本身没有parent
            self.setOwnerWindow(self.parent->ownerWindow);
            if (self.ownerWindow != null) {
                // self.invalidLayout()
            }
        }

        // if (_lifecycle) {
        //     LifecycleMountedEvent().emitTo(_lifecycle);
        // }

        // ViewUniteCallback::handleNodeMounted(this);
        // Node::g_onMounted(this);

        self.onMounted();
    }
    void baseOnUnmounting() {
        self.setOwnerWindow(null)
        //setOwnerWindow(nullptr);

        //printf("unmounting\n");
        // if (_lifecycle) {
            // LifecycleUnmountingEvent().emitTo(_lifecycle);
        // }


        // ViewUniteCallback::handleNodeUnmounting(this);
        // Node::g_onUnmounting(this);

        self.onUnmounting();
    }

    void onMounted(){}
    void onUnmounting(){
        // printf("onUnmounting:%s\n", self.name.str)
    }


    //所属的窗口
    Window@ ownerWindow = null
    // Object@ ownerWindow = null
    void setOwnerWindow(Window* win){
        if (self.ownerWindow == win){ // 没变化
            return
        } 
        self.ownerWindow = win
        //级联更新
        int l = self.getChildrenCount()
        for (int i = 0; i < l; i++){
            Node* kid = self.getChild(i);
            kid.setOwnerWindow(win);
        } 
    }
    Node * getChild(int i){
        return (Node*)self.children.get(i);
    }
    Window* getWindow(){
        return self.ownerWindow
    }

    Object* getChildByType(Vtable_Object* vt) {
        for (int i = self.getChildrenCount() - 1; i >= 0; i--) {
            Object* child = self.getChild(i);
            if (child instanceof vt) {
                return child;
            }
        }
        return null;
    }

    int getChildrenCount(){
        int size = self.children.size()
        return size
    }

    void appendChild(Node* child){
        if (child){

            child.removeSelf()
            child.parent = self
            self.children.add(child)
            child->setMounted(self.mounted);//传播mounted
        }
    }
    void insertChild(Node* child, int at){
        if (child){
            if (child.parent != self){
                child.removeSelf()
                child.parent = self
                self.children.insert(child, at)
            } else {
                //位置不变
                if (self.children.get(at) == child){
                    return;
                }
                //只要移动就可以
                int nowIndex = self.children.indexOf(child)
                if nowIndex == -1 {
                    self.children.insert(child, at)
                }
                else if (at < nowIndex){ //要前移
                    self.children.removeAt(nowIndex)
                    self.children.insert(child, at)
                } else { //后移
                    self.children.insert(child, at)
                    self.children.removeAt(nowIndex)
                }
            }
            child->setMounted(self.mounted);//传播mounted
        }
    }
    void removeChild(Node *child){
        if (child){
            child.parent = null
            self.children.remove(child)
            child->setMounted(false);//传播mounted
        }
    }
    int indexOf(Node* child){
        int idx = self.children.indexOf(child)
        return idx;
    }

    void removeSelf(){
        if (self.parent){
            // printf("removeSelf:%p className:%s\n", self, Object_getClassName(self));
            self.parent.removeChild(self)
        }
    }
    //整棵子树解散
    void dissolveSubtree(){
        {
            int l = self.getChildrenCount()
            for int i = l - 1; i >= 0; i--{
                Node* n = self.getChild(i)
                n.dissolveSubtree()
            }
            if self._mapForReact {
                self._mapForReact.clear()
            }
            if self._unusedMapForReact {
                self._unusedMapForReact.clear()
            }
            self.removeSelf()
        }

        // Time_sleepMs(3000)

        // printf("report :%p className:%s children:%p %p, %p\n", 
        //     self, Object_getClassName(self), self.children, self._mapForReact, self._unusedMapForReact);
        // urgc_report_sources_of(self);
    }

    List@ getAncients(bool includeSelf){
        List@ ret = new List()
        if (includeSelf){
            ret.add(self)
        }
        Node* cur = self
        while (cur->parent){
            cur = cur->parent
            ret.add(cur)
        }
        return ret
    }

    void react(){
    }
    void invalidReact(){
        self.trigger_react()
    }
    void trigger_react(){
        if (self._reactDirty){
            return
        }
        self._reactDirty = true
        Node_gReactDirty = true
        // printf("\n\n----------------------------------------trigger react\n\n")

        requestAnimationFrame(^bool(){
            // printf("\n\n----------------------------------------trigger react done\n\n");
            self._reactDirty = false
            self.react()
            return true
        })
    }
    bool _reactDirty = false

    String@ toString(){
        const char *className = Object_getClassName(self);
        return str(className)
        .add(":")
        .addString(self.name)
    }


    ScopeData __exit__(){
        return mkScopeData(self, (void*)node_exit)
    }
}
void node_exit(ScopeData  *scopeData){
    Node* n = (Node*)scopeData.data
    n.react();
    n.clearUnusedKids();
}

Map@ get_mapForReact(Node* n){
    if (!n._mapForReact){
        n._mapForReact = new Map()
    }
    return n._mapForReact
}

Map@ get_unusedMapForReact(Node* n){
    if (!n._unusedMapForReact){
        n._unusedMapForReact = new Map()
    }
    return n._unusedMapForReact
}


void clearInnerUnusedKids(Node *n){

}



void printNodesTree(List *nodes, int tab){
    for (int i = 0; i < nodes.size(); i++){
        Node* kid = (Node*)nodes.get(i)
        printNodeTree(kid, tab)
    }
}
void printNodeTree(Node *n, int tab){
    const char *className = Object_getClassName(n);
    for (int i = 0; i < tab; i++){
        printf("\t");
    }
    printf("%s. p:%p\n", n.toString().str, n)
    // printf("%s:%s\n", className, n.name.str)
    for (int i = 0; i < n.children.size(); i++){
        Node* kid = (Node*)n.children.get(i)
        printNodeTree(kid, tab + 1);
    }
}

extension Node{
    void walkIf(bool (*fn)(void *data, Node *n), void *ud){
        bool walkChildren = fn(ud, self)
        if walkChildren {
            for (int i = 0; i < self.children.size(); i++){
                Node* kid = (Node*)self.children.get(i)
                kid.walkIf(fn, ud)
            }
        }
    }
    void walk(void (*fn)(void *data, Node *n), void *ud){
        fn(ud, self)

        for (int i = 0; i < self.children.size(); i++){
            Node* kid = (Node*)self.children.get(i)
            kid.walk(fn, ud)
        }
    }
    // 取得根结点
    Node* getTopest(){
        Node* cur = self
        while cur {
            if !cur.parent{
                break;
            }
            cur = cur.parent
        }
        return cur;
    }
    //向上查找匹配类型的节点
    Node* getAncestorByClass(Vtable_Object* o){
        Node* cur = self
        while cur {
            if cur instanceof o {
                break
            }
            cur = cur.parent
        }
        return cur;
    }
    //按类型查找节点
    Node* findNodeByClass(Vtable_Object *o){
        if self instanceof o{
            return self
        }
        int l = self.getChildrenCount()
        for int i = 0; i < l; i++{
            Node* kid = self.getChild(i)
            if kid {
                Node* found = kid.findNodeByClass(o)
                if found{
                    return found;
                }
            }
        }
        return null
    }

    void endReact(){
        self.react()
        self.clearUnusedKids();
    }
    void end(){
        self.clearUnusedKids();
    }
    void clearUnusedKids(){
        Node* n = self
        //遍历 _unusedMapForReact， 删除节点， 清空map
        Map@ unused = get_unusedMapForReact(n)
        Map@ map = get_mapForReact(n)

        List@ keys = unused.keys()
        //删除未使用的节点
        int l = keys.size()
        bool needRmOutKids = self.hasInnerReact 
            && self.outKids 
            && !self.isInInnerReact() // innerReact期间，不需要对outKids做任何操作. outKids的更新只在react(即out react)期间

        for (int i = 0; i < l; i++){
            String@ key = (String@)keys.get(i);
            Node @unusedNode = (Node*)unused.get(key.str)
            unusedNode.removeSelf()

            //外部临时挂载的
            if needRmOutKids{
                self.outKids.remove(unusedNode)
            }
        }

        unused.clear()

        //交换
        n._mapForReact = unused
        n._unusedMapForReact = map
        //重置位置
        n._appendIndexForReact = 0
    }

    //放置临时的外部的outKids到指定节点下面.此函数只适用于innerReact
    void placeKid(Node* n){
        Node* parent = self
        Map* unusedMap = get_unusedMapForReact(parent)
        Map* map = get_mapForReact(parent)

        unusedMap.del(n.key)
        map.put(n.key, n)

        //有内部react
        if parent.hasInnerReact  // 如果目标节点不是自身，那有可能目标节点也是内部react. 如果目标节点是自身。 那就应该走直接插入的逻辑
            && !parent.isInInnerReact()
        {
            if parent.outKids == null {
                parent.outKids = new List()
            }

            parent.outKids.insert(n, parent._appendIndexForReact)
        }
        else {
            //插入到指定位置
            parent.insertChild(n, parent._appendIndexForReact)
        }

        parent._appendIndexForReact++
    }
    void placeKids(List@ kids){
        if kids == null {
            return
        }
        int l = kids.size()

        for int i = 0; i < l; i++{
            Node* n = (Node*)kids.get(i)
            self.placeKid(n)
        }
    }
    // 判断是不是在内部react中
    bool isInInnerReact(){
        return self.innerReact
        && self.innerReact.map == self._mapForReact
    }
}