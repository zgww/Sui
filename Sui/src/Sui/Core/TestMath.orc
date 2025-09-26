package SuiCore

#include <stdio.h>
import * from "./Vec2.orc"
import * from "./Vec3.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "./Mat3.orc"
import * from "../../Sgl/Mat.orc"

void testMath(){
    testVec2()

    testOk(eqFloat(mkVec2(3, 4).length(), 5), "length 3, 4 == 5");

    {
        Vec2 t = mkVec2(0, 0)
        t.setX(10)
        testOk(eqFloat(t.x, 10), "Vec2.setX")
    }

    {
        Vec2 t = mkVec2(0, 0)
        t.setY(10)
        testOk(eqFloat(t.y, 10), "Vec2.setY")
    }
    {
        Vec2 t = mkVec2(0, 0)
        t.setComponent(1, 11)
        testOk(eqFloat(t.y, 11), "Vec2.setComponent")
        testOk(eqFloat(t.getComponent(1), 11), "Vec2.getComponent")
    }
    {
        Vec2 t = mkVec2(0, 0)
        t.setComponent(0, 11)
        testOk(eqFloat(t.x, 11), "Vec2.setComponent")
        testOk(eqFloat(t.getComponent(0), 11), "Vec2.getComponent")
    }
    {
        Vec2 t = mkVec2(1, 2).clone()
        testOk(eqFloat(t.x, 1), "Vec2.clone")
        testOk(eqFloat(t.getComponent(1), 2), "Vec2.clone")
    }
    {
        Vec2 t = mkVec2(0, 0)
        t.addLocal(mkVec2(10, 10))
        testOk(eqFloat(t.x, 10), "Vec2.addLocal")
        testOk(eqFloat(t.getComponent(1), 10), "Vec2.addLocal")
    }
    {
        Vec2 t = mkVec2(0, 0)
        t.addScalarLocal(20)
        testOk(eqFloat(t.x, 20), "Vec2.addScalarLocal")
        testOk(eqFloat(t.getComponent(1), 20), "Vec2.addScalarLocal")
    }
    {
        Mat3 m3
        m3.identity().translateLocal(10, 10)

        Vec2 t = mkVec2(0, 0)
        t.applyMatrix3Local(m3)
        testOk(eqFloat(t.x, 10), "Vec2.applyMatrix3Local")
        testOk(eqFloat(t.getComponent(1), 10), "Vec2.applyMatrix3Local")
    }
    {
        Vec2 t = mkVec2(100, 200)
        t.minLocal(mkVec2(10, 150))
        testOk(eqFloat(t.x, 10), "Vec2.minLocal")
        testOk(eqFloat(t.getComponent(1), 150), "Vec2.minLocal")
    }
    {
        Vec2 t = mkVec2(10.123, -1.3)
        t.floorLocal()
        testOk(eqFloat(t.x, 10), "Vec2.floorLocal")
        testOk(eqFloat(t.getComponent(1), -2), "Vec2.floorLocal y")
    }
    {
        Vec2 t = mkVec2(10.123, -1.3)
        t.ceilLocal()
        testOk(eqFloat(t.x, 11), "Vec2.ceilLocal")
        testOk(eqFloat(t.getComponent(1), -1), "Vec2.ceilLocal y")
    }

    {
        Vec2 t = mkVec2(10.123, -1.6)
        t.roundLocal()
        testOk(eqFloat(t.x, 10), "Vec2.roundLocal")
        testOk(eqFloat(t.getComponent(1), -2), "Vec2.roundLocal y")
    }
    {
        Vec2 t = mkVec2(10, -1)
        t.negateLocal()
        testOk(eqFloat(t.x, -10), "Vec2.negateLocal")
        testOk(eqFloat(t.getComponent(1), 1), "Vec2.negateLocal y")
    }
    {
        Vec2 t = mkVec2(1, 1)
        float v = t.angle()
        // printf("v:%f, %f\n", v, 45 / 180.0 * PI)
        testOk(eqFloat(v,  45/ 180.0 * PI), "Vec2.angle")
    }
    {
        float v = mkVec2(1, 1).distanceTo(mkVec2(4, 5))
        // printf("v:%f, \n", v)
        testOk(eqFloat(v,  5), "Vec2.distanceTo")
    }
    {
        Vec3 target = mkVec3(-500, -500, 0)
        Vec3 up = mkVec3(0, 1, 0)
        Vec3 eye = mkVec3(0, 0, 0)

        Mat m;
        m.lookAtFake(eye, target, up);
        Mat m2;
        m2.lookAtLocal(eye, target, up)
        printf("m")
    }


    mkPrintStyle().blue().{
        printf("hi blue");
    }
    mkPrintStyle().red().bgwhite().{
        printf("hi red");
    }
    mkPrintStyle().green().{
        printf("hi this is green");
    }
    mkPrintStyle().cyan().{
        printf("hi this is cyan");
    }
    printf("reset color\n");
}