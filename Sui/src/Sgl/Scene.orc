package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"


//场景全局变量
struct SceneGlobal {
    //场景树中  相机有变化, 需要重新遍历加载
    bool cameraDirty;
    //场景树中， 灯光有变化，需要重新遍历加载
    // bool lightDirty;
}

SceneGlobal sceneGlobal;


class Scene extends Obj3d {
    void ctor(){
        // scene必然于mounted状态
        // 这样，子树节点才会跟着更新为mounted
        self.mounted = true
    }
}