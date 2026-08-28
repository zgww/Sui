module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Naga/Path.h"

export module Sgl:DirLight;

import :Obj3d;
import :Light;

export class DirLight : public Light {
public:

    // 环境光颜色
    int ambient = 0xff333333;
    // 漫反射光颜色
    int diffuse = 0xff999999;
    // 镜面光颜色
    int specular = 0xffffffff;
};