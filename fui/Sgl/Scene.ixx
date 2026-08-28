module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:Scene;

import :Obj3d;


//场景全局变量
export struct SceneGlobal {
    //场景树中  相机有变化, 需要重新遍历加载
    bool cameraDirty;
    //场景树中， 灯光有变化，需要重新遍历加载
    // bool lightDirty;
};

export SceneGlobal sceneGlobal;


export class Scene : public Obj3d {
public:
    Scene() {
        // scene必然于mounted状态
        // 这样，子树节点才会跟着更新为mounted
        mounted = true;
    }
};