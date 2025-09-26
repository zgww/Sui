package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Color.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Light.orc"


class PointLight extends Light {

    int color = 0xffff0000
    float intensity
    float distance = 300
    float decay = 2

}