package Sgl
#include <stdio.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"

//读取DEPTH_COMPONENT float类型的深度纹理
class DepthFloatPixlesReader {
    Buffer@ buffer = new Buffer()

    int x = 0
    int y = 0
    int w = 0
    int h = 0


    float* read(int x, int y, int w, int h){
        self.buffer.initSize(w * h * 4)

        self.x = x
        self.y = y
        self.w = w
        self.h = h

        glReadPixels(x, y, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, 
            self.buffer.data)
        return (float*)self.buffer.data
    }
}
class RgbaPixelsReader {
    Buffer@ buffer = new Buffer()

    int x = 0
    int y = 0
    int w = 0
    int h = 0

    unsigned char * readFromColorAttachment(int attachmentIndex, int x, int y, int w, int h){
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        return self.read(x, y, w, h)
    }
    unsigned char* read(int x, int y, int w, int h){
        self.buffer.initSize(w * h * 4)

        self.x = x
        self.y = y
        self.w = w
        self.h = h

        //一定要注意格式要和源匹配。  
        // 此行之前会失败崩溃.因为纹理的格式不是GL_FLOAT
        // glReadPixels(x, y, w, h, GL_RGBA, GL_FLOAT, 
        //     self.buffer.data)
        glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, 
            self.buffer.data)
        return (unsigned char *)self.buffer.data
    }
}