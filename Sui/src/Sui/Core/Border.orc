package SuiCore

#include <stdio.h>
import * from "./Edge.orc"

/// 布局上下文
class Border {

    Edge@ t = new Edge()
    Edge@ r = new Edge()
    Edge@ b = new Edge()
    Edge@ l = new Edge()

    bool isAllHasWidth(){
        return self.t.w> 0
        && self.r.w > 0
        && self.b.w > 0
        && self.l.w > 0
    }

    void copyFrom(Border *b){
        self.t.copyFrom(b.t)
        self.r.copyFrom(b.r)
        self.b.copyFrom(b.b)
        self.l.copyFrom(b.l)
    }

    void setAll(float w, int color){
        self.t.w = w
        self.t.color = color

        self.r.w = w
        self.r.color = color

        self.b.w = w
        self.b.color = color

        self.l.w = w
        self.l.color = color
    }
    float hor(){
	    return self.l.w + self.r.w;
    }
    float ver(){
	    return self.t.w + self.b.w;
    }
}
Border@ mkBorder(float w, int color){
    Border@ b = new Border()
    b.setAll(w, color)
    return b
}

void testBorder(){
    Border@ ent = mkBorder(10, 0xff0000ff)
    printf("testBorder\n")
}