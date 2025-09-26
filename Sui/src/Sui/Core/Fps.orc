
package SuiCore

#include <stdio.h>
#include "../../nanovg/nanovg.h"


import * from "../../Orc/Time.orc"
import * from "../Core/Canvas.orc"


// Fps统计
struct Fps {
    float fps 
    float layoutFps 
    float drawFps 


    long long costMs 
    long long layoutCostMs 
    long long drawCostMs 

    long long startMs 
    long long endMs 

    long long layoutStartMs
    long long layoutEndMs 
    long long drawStartMs 
    long long drawEndMs
}


extension Fps {
    void startFrame(){
        self.startMs = Time_unixMs()
    }
    void endFrame(){
        self.endMs = Time_unixMs()

        self.drawCostMs = self.drawEndMs - self.drawStartMs
        self.layoutCostMs = self.layoutEndMs - self.layoutStartMs
        self.costMs = self.endMs - self.startMs

        self.fps = self.costMs > 0 ? 1000.f / self.costMs: 1000
        self.layoutFps = self.layoutCostMs > 0 ? 1000.f / self.layoutCostMs: 1000
        self.drawFps  = self.drawCostMs > 0 ? 1000.f / self.drawCostMs: 1000
    }
    void startLayout(){
        self.layoutStartMs = Time_unixMs()
    }
    void endLayout(){
        self.layoutEndMs = Time_unixMs()
    }
    void startDraw(){
        self.drawStartMs = Time_unixMs()
    }
    void endDraw(){
        self.drawEndMs = Time_unixMs()
    }
    void draw(Canvas *canvas, int h){
        // printf("%lld,%lld,%lld\n", 
        //     self.costMs,
        //     self.layoutCostMs,
        //     self.drawCostMs,
        // );
        // if 1 {
        //     return;
        // }
        canvas.save();
        canvas.translate( 0, h - 30);

        char text[60];
        sprintf(text, "fps:%.1f/%.1f/%.1f", 
            self.fps,
            self.layoutFps,
            self.drawFps,
        );

        canvas.fillColor(0, 0, 0, 64);

        canvas.beginPath();
        canvas.rect( 0, 0, 200, 30)

        canvas.fill()

        canvas.fillColor(255, 255, 255, 255)
        canvas.text(6, 12, text)

        sprintf(text, "ms:%lld/%lld/%lld", 
            self.costMs,
            self.layoutCostMs,
            self.drawCostMs,
        );
        canvas.text( 6, 26, text)
        canvas.restore();
    }
}