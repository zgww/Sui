module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Naga/Path.h"

export module Sgl:SpotLight;

import :Obj3d;
import :Light;

export class SpotLight : public Light {
public:
    float distance = 100;
        // 张开的角的一半
    float angle = PI / 3.0;
   
};