package SuiCore


//组件库
#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../../Orc/List.orc"
import * from "../../Orc/Map.orc"

class NodeRegisterInfo{
    const char *className = "";
    Vtable_Object* vtable = null;

    void init(Vtable_Object* vt){
        self.className = vt.className
        self.vtable = vt;
    }
    Object@ mk(){
        Object@ obj = null;
        self.vtable.make(&obj)
        return obj
    }
}

class NodeLib {
    Map@ map = new Map()
    List@ list = new List()

    NodeRegisterInfo@ findByClassName(const char *className){
        NodeRegisterInfo@ info = (NodeRegisterInfo@)self.map.get(className)
        return info
    }
    void registerClass(Vtable_Object* vt){
        NodeRegisterInfo@ info = new NodeRegisterInfo()
        info.init(vt)
        self.map.put(vt.className, info)
        self.list.add(info)
    }
}
NodeLib* NodeLib_use(){
    static NodeLib@ lib = null
    if !lib {
        lib = new NodeLib()
    }
    return lib
}