package SuiCore
#include <stdlib.h>
#include <stdio.h>

import * from "../../Orc/List.orc"


//管理整个应用
struct Inset {
   float left;
   float top ;
   float right;
   float bottom;
}
extension Inset{

   void setAll(float v){
    self.left = v
    self.top = v
    self.right = v
    self.bottom = v
   }
   void setAxis(float v, float h){
        self.left = h
        self.right = h

        self.top = v
        self.bottom = v
   }
   
   void setHor(float v){
    self.left = v
    self.right = v
   }
   void setVer(float v){
    self.top = v
    self.bottom = v
   }
   float hor(){
    return self.left + self.right
   }
   float ver(){
    return self.top + self.bottom
   }
   void invert(){
    self.left = -self.left
    self.top = -self.top
    self.right = -self.right
    self.bottom = -self.bottom
   }
}
Inset mkInset0(){
    Inset ret
    ret.top = 0.0
    ret.right = 0.0
    ret.bottom = 0.0
    ret.left = 0.0
    return ret
}

Inset mkInset(float t, float r, float b, float l){
    Inset ret
    ret.top = t
    ret.right = r
    ret.bottom = b
    ret.left = l
    return ret
}

void testInset(){
    Inset inset = mkInset(1,2,3,4)
    printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left)
    inset.setAll(1)
    printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left)
    inset.setVer(3)
    printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left)
    inset.setHor(4)
    printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left)
}


