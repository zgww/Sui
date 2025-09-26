package SuiCore

// #include <stdlib.h>

import * from "./Mat2d.orc"
import * from "./Image.orc"
import * from "./Color.orc"
// import type * from "./Window.orc"

// class refc Paint {
//     void *data;
//     void dtor(){}
// }


class refc Canvas {
    void *data;
    extern void dtor()
    extern void init()
    // void initByWindowId(long long windowId)
}

extension Canvas {
    extern void beginFrame(float w, float h, float devicePixelRatio)
    extern void endFrame()
    extern void cancelFrame()


    extern void globalAlpha(float alpha)
    extern void stroke()
    extern void fill()
    void strokeColorByInt32(int c){
        self.strokeColor(
            colorGetR(c),
            colorGetG(c),
            colorGetB(c),
            colorGetA(c),
        )
    }
    void fillColorByInt32(int c){
        self.fillColor(
            colorGetR(c),
            colorGetG(c),
            colorGetB(c),
            colorGetA(c),
        )
    }
    extern void fillColor(int r, int g, int b, int a)
    extern void strokeColor(int r, int g, int b, int a)
    extern void strokeWidth(float width)

    extern void shapeAntiAlias(int enabled)

    extern void lineJoin(int join)
    extern void lineCap(int cap)


    extern void translate(float x, float y)
    extern void scale(float x, float y)
    extern void rotate(float rad)

    extern void skewX(float rad)
    extern void skewY(float rad)

    extern void transform(Mat2d mat)
    extern void setTransform(Mat2d mat)
    extern void resetTransform()
    extern void currentTransform(Mat2d *mat)//float *outXForm)

    extern void save()
    extern void restore()
    extern void reset()

    extern void scissor(float x, float y, float w, float h)
    extern void intersectScissor(float x, float y, float w, float h)
    extern void resetScissor()

    extern void beginPath()
    extern void closePath()
    extern void moveTo(float x, float y)
    extern void lineTo(float x, float y)
    extern void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y)
    extern void quadTo(float cx, float cy, float x, float y)
    extern void arcTo(float x1, float y1, float x2, float y2, float radius)

    extern void pathWinding(int dir)

    extern void arc(float cx, float cy, float r, float a0, float a1, int dir)
    extern void rect(float x, float y, float w, float h)
    extern void roundRect(float x, float y, float w, float h, float r)
    extern void roundRectVarying(
        float x, float y, float w, float h, float rtl, float rtr, float rbr, float rbl)
    extern void ellipse(float cx, float cy, float rx, float ry)
    extern void circle(float cx, float cy, float r)
        

    // font 
    extern void fontBlur(float blur)
    extern void fontFace(const char *name)
    extern void fontSize(float size)
    extern void textLetterSpacing(float spacing)
    extern void texLineHeight(float lineHeight)
    extern void textAlign(int align)
    extern void text( float x, float y, const char *string)
    extern float textBounds( float x, float y, const char *string, const char *end, float *bounds)

    // draw image

    extern void drawImage(Image* img, float x, float y, float alpha)
    extern void drawImageAtRect(Image* img, 
        float sx, float sy, 
        float sw, float sh, 
        float dx, float dy, 
        float dw, float dh, 
        float alpha)


    extern void linearGradient(bool fill,
        float sx, 
        float sy, 
        float ex, 
        float ey, 
        int icolor, 
        int ocol
    )
    extern void boxGradient(bool fill,
        float x, float y, float w, float h,
        float r, float f, int icol, int ocol);

    extern void radialGradient(bool fill,
        float cx, float cy, float inr, float outr,
        int icol, int ocol);

    extern void imagePattern(bool fill, 
        float ox, float oy, float ex, float ey,
        float angle, Image* image, float alpha);


    
    extern int _createImageRGBA(int w, int h, int imgFlags, const unsigned char *imgData);

    Image@ createImageRGBA(int w, int h, const unsigned char *imgData){
        Image@ img = new Image()
        img._img = self._createImageRGBA(w, h, 0, imgData)
        return img
    }

    extern int _createImage(const char *path)

    Image@ createImage(const char *path){
        Image@ img = new Image()
        img._img = self._createImage(path)
        return img
    }

}