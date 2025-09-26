package Sgl

#include <stdio.h>


import * from "../Orc/Math.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Light.orc"


class SpotLight extends Light {
    float distance = 100
    // 张开的角的一半
    float angle = PI / 3.0
}