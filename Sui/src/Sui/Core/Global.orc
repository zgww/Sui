package SuiCore
#include <stdlib.h>
#include <stdio.h>

#include "../../nanovg/nanovg.h"
import * from "./Canvas.orc"


static Canvas @canvas;

NVGcontext *Global_getVg(){
    if canvas {
        return (NVGcontext*)canvas.data;
    }
    return null
}

Canvas * Global_getCanvas(){
    return canvas;
}
void Global_setCanvas(Canvas *c){
    canvas = c
} 



void testGlobal(){
    printf("getVg:%p\n", Global_getVg());
}
