
package SuiDesigner


#include <stdio.h>
#include <stdlib.h>


import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Canvas.orc"

//回调

class ChessBgViewCallback extends ViewCallback{
    // int chessBgImageId = 0
    int width = 32
    int height = 32
    int color0 = 0xff333333
    int color1 = 0xff000000
    Image@ img = null

    Object@ obj

    void dtor(){
        printf("~Dtor ChessBgViewCallback\n")
    }

    bool cbLayout(View *div, Frame *ctx){
        return false
    }
    bool cbDraw(View *div, Canvas *canvas){
		Image* bg = self.gocChessBgImage(canvas)

        Rect r = div.getViewRect();

        canvas.beginPath();
		canvas.rect( 0, 0, r.w, r.h)
		//绘制背景
		canvas.imagePattern(
            true,
			0, 0, self.width, self.height, 0, bg, 1
		)
		canvas.fill()

        return false //继续原来的绘制
    }

    char *new_createChessBg_inMemory(int w, int h){
        char *data = malloc(w * h * 4)
        int hw = w / 2
        int hh = h / 2


        int a0 = colorGetA(self.color0)
        int r0 = colorGetR(self.color0)
        int g0 = colorGetG(self.color0)
        int b0 = colorGetB(self.color0)

        int a1 = colorGetA(self.color1)
        int r1 = colorGetR(self.color1)
        int g1 = colorGetG(self.color1)
        int b1 = colorGetB(self.color1)


        for (int y = 0; y < h; y++){
            for (int x = 0; x < w; x++){
                int i = (y * w + x) * 4
                bool mode = (x < hw && y < hh) || (x >= hw && y >= hh)
                if (mode){
                    data[i] = r0
                    data[i + 1] = g0
                    data[i + 2] = b0
                    data[i + 3] = a0
                } else {
                    data[i] = r1
                    data[i + 1] = g1
                    data[i + 2] = b1
                    data[i + 3] = a1
                }
            }
        }

        return data
    }
    int gocChessBgImage(Canvas *canvas){
        if (self.img == null){
            int w = self.width
            int h = self.height

            char *imgData = self.new_createChessBg_inMemory(w, h, ) 
            self.img = canvas.createImageRGBA(w, h, (const unsigned char *)imgData)

            free(imgData)
        }
        return self.img
    }
}