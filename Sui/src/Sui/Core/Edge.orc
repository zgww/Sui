package SuiCore

#include <stdio.h>
//import * from "./Node.orc"

// struct Tmp2{
//     int xx;
// }


// struct Tmp {
//     int a 
//     float fv;
//     Tmp2 tmp2;
//     Tmp2 *ptmp2;
//     Tmp2 @rtmp2;
// }

/// 边框
class Edge {

    // Tmp tmp;
    // Tmp *ptmp;
    // Tmp @rtmp;

    // char c0 = 0
    // unsigned char u8 = 0
    // short s = 0
    // unsigned short us = 0

    // int i0 = 0
    // unsigned  int ui = 0

    // double doubleValue = 0.0
    // long lv = 0
    // long long llv = 0


    float w = 0.f
    int color = 0x00000000

    void copyFrom(Edge *v){
        self.w = v.w
        self.color = v.color
    }
    void set(float w, int color){
        self.w = w
        self.color = color
    }

}

void testEdge(){
    Edge@ e = new Edge()
    e.w = 12.f
    e.color = 0x234
    printf("edge:%f, %x\n", e.w, e.color)
}