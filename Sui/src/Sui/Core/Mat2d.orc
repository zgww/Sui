package SuiCore
#include <stdio.h>

import * from "./Node.orc"
import * from "./Rect.orc"
// import * from "./Frame.orc"
import * from "../../Orc/String.orc"
import * from "./Vec2.orc"
import * from "./Vec3.orc"
   
struct Mat2d {
    //存放a b c d e f。2d变换所需要的最少6个自由变量
    float data[6]
    // void *data
}


extension Mat2d {
    //extern void ctor() 
    //extern void dtor()
    extern void identity() 
    extern void translate(float x, float y, float z) 

    extern void scale(float x, float y, float z) 
    extern void rotate(float x, float y, float z) 
    extern void multiply(Mat2d *b)
    extern void premultiply(Mat2d *b)
    extern void inverse()
    //返回新的
    Mat2d inverseNew(){
        Mat2d m = *self;
        m.inverse();
        return m;
    }

    extern Vec3 transformPoint(float x, float y, float z)

    //局部坐标转到另一个矩阵的局部坐标
    //[invMat2d]是另一个坐标系的 逆矩阵
    Vec3 localToLocal(Mat2d *invMat2d, float x, float y, float z){
        Vec3 worldPos = self.transformPoint(x, y, z)
        Vec3 ret = invMat2d.transformPoint(worldPos.x, worldPos.y, worldPos.z)
        return ret
    }
//    extern Mat2d@ copy()
}
extern Mat2d mkMat2d()


void testMat2d(){
    
	Mat2d m = mkMat2d();
	Vec3 p = m->transformPoint( 10.f, 10.f, 0.f);
	printf("2应用变换:%f, %f\n", p.x, p.y);
	m.translate( 10.f, 1.f, 0.f);
	p = m.transformPoint(10.f, 10.f, 0.f);
	printf("2应用变换:%f, %f\n", p.x, p.y);

	m.scale(3.f, 3.f, 1.f);
	p = m.transformPoint( 10.f, 10.f, 0.f);
	printf("2应用变换:%f, %f\n", p.x, p.y);
}