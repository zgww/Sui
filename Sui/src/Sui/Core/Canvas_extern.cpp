#include "./Canvas_orc.h"
#include "../../nanovg/nanovg.h"

#include "../../nanovg/stb_image.h"

#include <Windows.h>
#include "GL/GL.h"
#define NANOVG_GL3
#include "../../nanovg/nanovg_gl.h"
#include "./Color_orc.h"


void  SuiCore$Canvas$dtor(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;

    if (vg){
        nvgDeleteGL3(vg);
    }

    self->data = NULL;
}
void  SuiCore$Canvas$init(SuiCore$Canvas *  self){
    // auto vg = (NVGcontext*)self->data;
    // auto vg = nvgCreateGL2();
    NVGcontext *vg = nvgCreateGL3(NVG_ANTIALIAS |NVG_STENCIL_STROKES);
    self->data = vg;
}

void  SuiCore$Canvas$beginFrame(SuiCore$Canvas *  self, float  w, float  h, float  devicePixelRatio){
    auto vg = (NVGcontext*)self->data;
    nvgBeginFrame(vg, w, h, devicePixelRatio);
}
void  SuiCore$Canvas$endFrame(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgEndFrame(vg);
}
void  SuiCore$Canvas$cancelFrame(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgCancelFrame(vg);
}
void  SuiCore$Canvas$globalAlpha(SuiCore$Canvas *  self, float  alpha){
    auto vg = (NVGcontext*)self->data;
    nvgGlobalAlpha(vg, alpha);
}
void  SuiCore$Canvas$stroke(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgStroke(vg);
}
void  SuiCore$Canvas$fill(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgFill(vg);
}
void  SuiCore$Canvas$fillColor(SuiCore$Canvas *  self, int  r, int  g, int  b, int  a){
    auto vg = (NVGcontext*)self->data;
    nvgFillColor(vg, nvgRGBA(r, g, b, a));

}
void  SuiCore$Canvas$strokeColor(SuiCore$Canvas *  self, int  r, int  g, int  b, int  a){
    auto vg = (NVGcontext*)self->data;
    nvgStrokeColor(vg, nvgRGBA(r, g, b, a));

}
void  SuiCore$Canvas$strokeWidth(SuiCore$Canvas *  self, float  width){
    auto vg = (NVGcontext*)self->data;
    nvgStrokeWidth(vg, width);

}
void  SuiCore$Canvas$shapeAntiAlias(SuiCore$Canvas *  self, int  enabled){
    auto vg = (NVGcontext*)self->data;
    nvgShapeAntiAlias(vg, enabled);
}
void  SuiCore$Canvas$lineJoin(SuiCore$Canvas *  self, int  join){
    auto vg = (NVGcontext*)self->data;
    nvgLineJoin(vg, join);
}
void  SuiCore$Canvas$lineCap(SuiCore$Canvas *  self, int  cap){
    auto vg = (NVGcontext*)self->data;
    nvgLineCap(vg, cap);
}
void  SuiCore$Canvas$translate(SuiCore$Canvas *  self, float  x, float  y){
    auto vg = (NVGcontext*)self->data;
    nvgTranslate(vg, x, y);
}
void  SuiCore$Canvas$scale(SuiCore$Canvas *  self, float  x, float  y){
    auto vg = (NVGcontext*)self->data;
    nvgScale(vg, x, y);
}
void  SuiCore$Canvas$rotate(SuiCore$Canvas *  self, float  rad){
    auto vg = (NVGcontext*)self->data;
    nvgRotate(vg, rad);
}
void  SuiCore$Canvas$skewX(SuiCore$Canvas *  self, float  rad){
    auto vg = (NVGcontext*)self->data;
    nvgSkewX(vg, rad);
}
void  SuiCore$Canvas$skewY(SuiCore$Canvas *  self, float  rad){
    auto vg = (NVGcontext*)self->data;
    nvgSkewY(vg, rad);
}
void  SuiCore$Canvas$transform(SuiCore$Canvas *  self, SuiCore$Mat2d mat){
    auto vg = (NVGcontext*)self->data;
    nvgTransform(vg
    , mat.data[0]
    , mat.data[1]
    , mat.data[2]
    , mat.data[3]
    , mat.data[4]
    , mat.data[5]
    );
}
void  SuiCore$Canvas$setTransform(SuiCore$Canvas *  self, SuiCore$Mat2d mat){
    auto vg = (NVGcontext*)self->data;
    nvgResetTransform(vg);
    nvgTransform(vg
    , mat.data[0]
    , mat.data[1]
    , mat.data[2]
    , mat.data[3]
    , mat.data[4]
    , mat.data[5]
    );
}
void  SuiCore$Canvas$resetTransform(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgResetTransform(vg);
}
void  SuiCore$Canvas$currentTransform(SuiCore$Canvas *  self, SuiCore$Mat2d *mat){ //float *  outXForm){
    auto vg = (NVGcontext*)self->data;
    nvgCurrentTransform(vg, mat->data);
}
void  SuiCore$Canvas$save(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgSave(vg);
}
void  SuiCore$Canvas$restore(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgRestore(vg);
}
void  SuiCore$Canvas$reset(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgReset(vg);
}
void  SuiCore$Canvas$scissor(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h){
    auto vg = (NVGcontext*)self->data;
    nvgScissor(vg, x, y, w, h);
}
void  SuiCore$Canvas$intersectScissor(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h){
    auto vg = (NVGcontext*)self->data;
    nvgIntersectScissor(vg, x, y, w, h);
}
void  SuiCore$Canvas$resetScissor(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgResetScissor(vg);
}
void  SuiCore$Canvas$beginPath(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgBeginPath(vg);
}
void  SuiCore$Canvas$closePath(SuiCore$Canvas *  self){
    auto vg = (NVGcontext*)self->data;
    nvgClosePath(vg);
}
void  SuiCore$Canvas$moveTo(SuiCore$Canvas *  self, float  x, float  y){
    auto vg = (NVGcontext*)self->data;
    nvgMoveTo(vg, x, y);
}
void  SuiCore$Canvas$lineTo(SuiCore$Canvas *  self, float  x, float  y){
    auto vg = (NVGcontext*)self->data;
    nvgLineTo(vg, x, y);
}
void  SuiCore$Canvas$bezierTo(SuiCore$Canvas *  self, float  c1x, float  c1y, float  c2x, float  c2y, float  x, float  y){
    auto vg = (NVGcontext*)self->data;
    nvgBezierTo(vg, c1x, c1y, c2x, c2y, x, y);
}
void  SuiCore$Canvas$quadTo(SuiCore$Canvas *  self, float  cx, float  cy, float  x, float  y){
    auto vg = (NVGcontext*)self->data;
    nvgQuadTo(vg, cx, cy, x, y);
}
void  SuiCore$Canvas$arcTo(SuiCore$Canvas *  self, float  x1, float  y1, float  x2, float  y2, float  radius){
    auto vg = (NVGcontext*)self->data;
    nvgArcTo(vg, x1, y1, x2, y2, radius);
}
void  SuiCore$Canvas$pathWinding(SuiCore$Canvas *  self, int  dir){
    auto vg = (NVGcontext*)self->data;
    nvgPathWinding(vg, dir);
}
void  SuiCore$Canvas$arc(SuiCore$Canvas *  self, float  cx, float  cy, float  r, float  a0, float  a1, int  dir){
    auto vg = (NVGcontext*)self->data;
    nvgArc(vg, cx, cy, r, a0, a1, dir);
}
void  SuiCore$Canvas$rect(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h){
    auto vg = (NVGcontext*)self->data;
    nvgRect(vg, x, y, w, h);
}
void  SuiCore$Canvas$roundRect(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h, float  r){
    auto vg = (NVGcontext*)self->data;
    nvgRoundedRect(vg, x, y, w, h, r);
}
void  SuiCore$Canvas$roundRectVarying(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h, float  rtl, float  rtr, float  rbr, float  rbl){
    auto vg = (NVGcontext*)self->data;
    nvgRoundedRectVarying(vg, x, y, w, h, rtl, rtr, rbr, rbl);
}
void  SuiCore$Canvas$ellipse(SuiCore$Canvas *  self, float  cx, float  cy, float  rx, float  ry){
    auto vg = (NVGcontext*)self->data;
    nvgEllipse(vg, cx, cy, rx, ry);
}
void  SuiCore$Canvas$circle(SuiCore$Canvas *  self, float  cx, float  cy, float  r){
    auto vg = (NVGcontext*)self->data;
    nvgCircle(vg, cx, cy, r);
}
void  SuiCore$Canvas$fontBlur(SuiCore$Canvas *  self, float  blur){
    auto vg = (NVGcontext*)self->data;
    nvgFontBlur(vg, blur);
}
void  SuiCore$Canvas$fontFace(SuiCore$Canvas *  self, const char *  name){
    auto vg = (NVGcontext*)self->data;
    nvgFontFace(vg, name);
}
void  SuiCore$Canvas$fontSize(SuiCore$Canvas *  self, float  size){
    auto vg = (NVGcontext*)self->data;
    nvgFontSize(vg, size);
}
void  SuiCore$Canvas$textLetterSpacing(SuiCore$Canvas *  self, float  spacing){
    auto vg = (NVGcontext*)self->data;
    nvgTextLetterSpacing(vg, spacing);
}
void  SuiCore$Canvas$texLineHeight(SuiCore$Canvas *  self, float  lineHeight){
    auto vg = (NVGcontext*)self->data;
    nvgTextLineHeight(vg, lineHeight);
}
void  SuiCore$Canvas$textAlign(SuiCore$Canvas *  self, int  align){
    auto vg = (NVGcontext*)self->data;
    nvgTextAlign(vg, align);
}
void  SuiCore$Canvas$text(SuiCore$Canvas *  self, float  x, float  y, const char *  string){
    auto vg = (NVGcontext*)self->data;
    nvgText(vg, x, y, string, NULL);
}
float  SuiCore$Canvas$textBounds(SuiCore$Canvas *  self, 
    float  x, float  y, const char *  string, const char *end, float *  bounds){
    auto vg = (NVGcontext*)self->data;
    float w = nvgTextBounds(vg, x, y, string, end, bounds);
    return w;
}
void  SuiCore$Canvas$drawImage(SuiCore$Canvas *  self, SuiCore$Image *  img,
 float  x, float y, float alpha){
    auto vg = (NVGcontext*)self->data;
    //todo draw image.

    int imgId = img->_img;
    int imgW = 0;
	int  imgH = 0;
    nvgImageSize(vg, imgId, &imgW, &imgH);
    float sw = imgW;
    float sh = imgH;
    float dw = imgW;
    float dh = imgH;
    float sx = 0.f;
    float sy = 0.f;
    float dx = x;
    float dy = y;
    

    float wscale = dw / sw;
    float hscale = dh / sh;
    float imgScaleW = imgW * wscale   ;
    float imgScaleH = imgH * hscale;

    float ox = -sx * wscale + dx;
    float oy = -sy * hscale + dy;

    //创建图片笔刷。  ex,ey表示图片缩放到目标宽高
    NVGpaint paint = nvgImagePattern(vg, 
        0, 0, imgW, imgH, 
        // ox, oy, 
        // imgScaleW, imgScaleH, 
        0.f, imgId, alpha);
    nvgFillPaint(vg, paint);

    nvgBeginPath(vg);
    nvgRect(vg, x, y, imgW, imgH);
    nvgFill(vg);
}
void  SuiCore$Canvas$drawImageAtRect(SuiCore$Canvas *  self, SuiCore$Image *  img, float  sx, float  sy, float  sw, float  sh, float  dx, float  dy, float  dw, float  dh, float  alpha){
    auto vg = (NVGcontext*)self->data;
    int imgId = img->_img;

    int imgW = 0;
	int imgH = 0;
    nvgImageSize(vg, imgId, &imgW, &imgH);
    float wscale = dw / sw;
    float hscale = dh / sh;
    float imgScaleW = imgW * wscale   ;
    float imgScaleH = imgH * hscale;

    float ox = -sx * wscale + dx;
    float oy = -sy * hscale + dy;

    //创建图片笔刷。  ex,ey表示图片缩放到目标宽高
    NVGpaint paint = nvgImagePattern(vg, ox, oy, imgScaleW, imgScaleH, 0.f, imgId, alpha);
    nvgFillPaint(vg, paint);

    nvgBeginPath(vg);
    nvgRect(vg, dx, dy, dw, dh);
    nvgFill(vg);
}

void  SuiCore$Canvas$linearGradient(
    SuiCore$Canvas *  self,
    bool fill,
        float sx, 
        float sy, 
        float ex, 
        float ey, 
        int icolor, 
        int ocolor
    ){

    auto vg = (NVGcontext*)self->data;
    NVGpaint lg = nvgLinearGradient(vg, 
        sx, sy, 
        ex, ey,
        SuiCore$mkNVGColorByInt(icolor),
        SuiCore$mkNVGColorByInt(ocolor)
    );
    if (fill){
        nvgFillPaint(vg, lg);
    }
    else {
        nvgStrokePaint(vg, lg);
    }
}
void  SuiCore$Canvas$boxGradient(
    SuiCore$Canvas *  self,
        bool fill,
        float x, float y, float w, float h,
        float r, float f, int icol, int ocol){

    auto vg = (NVGcontext*)self->data;
    NVGpaint lg = nvgBoxGradient(vg, 
        x, y, w, h, r, f,
        SuiCore$mkNVGColorByInt(icol),
        SuiCore$mkNVGColorByInt(ocol)
    );
    if (fill){
        nvgFillPaint(vg, lg);
    }
    else {
        nvgStrokePaint(vg, lg);
    }
}
void  SuiCore$Canvas$radialGradient(
    SuiCore$Canvas *  self,
    bool fill,
        float cx, float cy, float inr, float outr,
        int icol, int ocol){

    auto vg = (NVGcontext*)self->data;
    NVGpaint lg = nvgRadialGradient(vg, 
        cx, cy, inr, outr, 
        SuiCore$mkNVGColorByInt(icol),
        SuiCore$mkNVGColorByInt(ocol)
    );
    if (fill){
        nvgFillPaint(vg, lg);
    }
    else {
        nvgStrokePaint(vg, lg);
    }
}
void  SuiCore$Canvas$imagePattern(
    SuiCore$Canvas *  self,
    bool fill,
        float ox, float oy, float ex, float ey,
        float angle, SuiCore$Image* image, float alpha){

    auto vg = (NVGcontext*)self->data;
    NVGpaint lg = nvgImagePattern(vg, 
        ox, oy, ex, ey, angle, image->_img, alpha
    );
    if (fill){
        nvgFillPaint(vg, lg);
    }
    else {
        nvgStrokePaint(vg, lg);
    }
}
int  SuiCore$Canvas$_createImageRGBA(
    SuiCore$Canvas *  self,
    int w, int h, int imgFlags, const unsigned char *imgData){
    auto vg = (NVGcontext*)self->data;

    int id = nvgCreateImageRGBA(
        vg, w, h, NVG_IMAGE_REPEATX|NVG_IMAGE_REPEATY, (const unsigned char *)imgData);
    return id;
}

int  SuiCore$Canvas$_createImage(
    SuiCore$Canvas *  self,
    const char *path){
    auto vg = (NVGcontext*)self->data;

    stbi_set_flip_vertically_on_load(false);
	int id = nvgCreateImage(vg, path, NVG_IMAGE_REPEATX|NVG_IMAGE_REPEATY);
    return id;
}