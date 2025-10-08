package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


import * from "./Vec2.orc"
import * from "../../Orc/String.orc"

/// 布局上下文
struct Bezier {
    Vec2 start
    Vec2 c0 
    Vec2 c1 
    Vec2 end 
}
Bezier mkBezier(){
    Vec2 start = mkVec2(0.0, 0.0)
    Vec2 c0 = mkVec2(0.25, 0.5)
    Vec2 c1 = mkVec2(0.75, 0.5)
    Vec2 end = mkVec2(1.0, 1.0)

	Bezier b
	b.start = start
	b.c0 = c0
	b.c1 = c1
	b.end = end
	return b
}
extension Bezier {
    String@ toString(){
        char tmp[256];
        sprintf(tmp, "Bezier(%s,%s,%s,%s)", 
            self.start.toString().str,
            self.c0.toString().str,
            self.c1.toString().str,
            self.end.toString().str,
        )
        return str(tmp)
    }
}
