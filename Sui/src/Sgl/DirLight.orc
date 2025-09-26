package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Light.orc"


class DirLight extends Light {
    // 环境光颜色
    int ambient = 0xff333333;
    // 漫反射光颜色
    int diffuse = 0xff999999;
    // 镜面光颜色
    int specular = 0xffffffff;
}