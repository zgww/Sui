module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Naga/Path.h"

export module Sgl:PointLight;

import :Obj3d;
import :Light;

export class PointLight : public Light {
public:


    int color = 0xffffffff;
    float intensity;
    float distance = 300;
    float decay = 2;
};