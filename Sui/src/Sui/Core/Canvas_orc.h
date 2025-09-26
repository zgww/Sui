
typedef struct tagSuiCore$Canvas SuiCore$Canvas;
typedef struct tagVtable_SuiCore$Canvas Vtable_SuiCore$Canvas;


#ifndef define_struct___SuiCore__Canvas_orc_h__
#define define_struct___SuiCore__Canvas_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Canvas_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiCore__Canvas_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Canvas_orc_h__
#define __SuiCore__Canvas_orc_h__

//include  importHeadCode
#include "./Mat2d_orc.h"
#include "./Image_orc.h"
#include "./Color_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Canvas {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Canvas _vtable_SuiCore$Canvas;

// class refc:1
struct tagSuiCore$Canvas {
	Object super; 
	void *  data ;
	void  (*init) (SuiCore$Canvas *  self);
};
Vtable_SuiCore$Canvas* Vtable_SuiCore$Canvas_init(Vtable_SuiCore$Canvas* pvt);
void SuiCore$Canvas_init_fields(SuiCore$Canvas *self);
void SuiCore$Canvas_init(SuiCore$Canvas *self, void *pOwner);
SuiCore$Canvas * SuiCore$Canvas_new(void *pOwner);
void SuiCore$Canvas_fini(SuiCore$Canvas *self);

extern void  SuiCore$Canvas$dtor(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$init(SuiCore$Canvas *  self);

extern void  SuiCore$Canvas$beginFrame(SuiCore$Canvas *  self, float  w, float  h, float  devicePixelRatio);
extern void  SuiCore$Canvas$endFrame(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$cancelFrame(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$globalAlpha(SuiCore$Canvas *  self, float  alpha);
extern void  SuiCore$Canvas$stroke(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$fill(SuiCore$Canvas *  self);
void  SuiCore$Canvas$strokeColorByInt32(SuiCore$Canvas *  self, int  c);
void  SuiCore$Canvas$fillColorByInt32(SuiCore$Canvas *  self, int  c);
extern void  SuiCore$Canvas$fillColor(SuiCore$Canvas *  self, int  r, int  g, int  b, int  a);
extern void  SuiCore$Canvas$strokeColor(SuiCore$Canvas *  self, int  r, int  g, int  b, int  a);
extern void  SuiCore$Canvas$strokeWidth(SuiCore$Canvas *  self, float  width);
extern void  SuiCore$Canvas$shapeAntiAlias(SuiCore$Canvas *  self, int  enabled);
extern void  SuiCore$Canvas$lineJoin(SuiCore$Canvas *  self, int  join);
extern void  SuiCore$Canvas$lineCap(SuiCore$Canvas *  self, int  cap);
extern void  SuiCore$Canvas$translate(SuiCore$Canvas *  self, float  x, float  y);
extern void  SuiCore$Canvas$scale(SuiCore$Canvas *  self, float  x, float  y);
extern void  SuiCore$Canvas$rotate(SuiCore$Canvas *  self, float  rad);
extern void  SuiCore$Canvas$skewX(SuiCore$Canvas *  self, float  rad);
extern void  SuiCore$Canvas$skewY(SuiCore$Canvas *  self, float  rad);
extern void  SuiCore$Canvas$transform(SuiCore$Canvas *  self, SuiCore$Mat2d mat);
extern void  SuiCore$Canvas$setTransform(SuiCore$Canvas *  self, SuiCore$Mat2d mat);
extern void  SuiCore$Canvas$resetTransform(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$currentTransform(SuiCore$Canvas *  self, SuiCore$Mat2d *  mat);
extern void  SuiCore$Canvas$save(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$restore(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$reset(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$scissor(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h);
extern void  SuiCore$Canvas$intersectScissor(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h);
extern void  SuiCore$Canvas$resetScissor(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$beginPath(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$closePath(SuiCore$Canvas *  self);
extern void  SuiCore$Canvas$moveTo(SuiCore$Canvas *  self, float  x, float  y);
extern void  SuiCore$Canvas$lineTo(SuiCore$Canvas *  self, float  x, float  y);
extern void  SuiCore$Canvas$bezierTo(SuiCore$Canvas *  self, float  c1x, float  c1y, float  c2x, float  c2y, float  x, float  y);
extern void  SuiCore$Canvas$quadTo(SuiCore$Canvas *  self, float  cx, float  cy, float  x, float  y);
extern void  SuiCore$Canvas$arcTo(SuiCore$Canvas *  self, float  x1, float  y1, float  x2, float  y2, float  radius);
extern void  SuiCore$Canvas$pathWinding(SuiCore$Canvas *  self, int  dir);
extern void  SuiCore$Canvas$arc(SuiCore$Canvas *  self, float  cx, float  cy, float  r, float  a0, float  a1, int  dir);
extern void  SuiCore$Canvas$rect(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h);
extern void  SuiCore$Canvas$roundRect(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h, float  r);
extern void  SuiCore$Canvas$roundRectVarying(SuiCore$Canvas *  self, float  x, float  y, float  w, float  h, float  rtl, float  rtr, float  rbr, float  rbl);
extern void  SuiCore$Canvas$ellipse(SuiCore$Canvas *  self, float  cx, float  cy, float  rx, float  ry);
extern void  SuiCore$Canvas$circle(SuiCore$Canvas *  self, float  cx, float  cy, float  r);
extern void  SuiCore$Canvas$fontBlur(SuiCore$Canvas *  self, float  blur);
extern void  SuiCore$Canvas$fontFace(SuiCore$Canvas *  self, const char *  name);
extern void  SuiCore$Canvas$fontSize(SuiCore$Canvas *  self, float  size);
extern void  SuiCore$Canvas$textLetterSpacing(SuiCore$Canvas *  self, float  spacing);
extern void  SuiCore$Canvas$texLineHeight(SuiCore$Canvas *  self, float  lineHeight);
extern void  SuiCore$Canvas$textAlign(SuiCore$Canvas *  self, int  align);
extern void  SuiCore$Canvas$text(SuiCore$Canvas *  self, float  x, float  y, const char *  string);
extern float  SuiCore$Canvas$textBounds(SuiCore$Canvas *  self, float  x, float  y, const char *  string, const char *  end, float *  bounds);
extern void  SuiCore$Canvas$drawImage(SuiCore$Canvas *  self, SuiCore$Image *  img, float  x, float  y, float  alpha);
extern void  SuiCore$Canvas$drawImageAtRect(SuiCore$Canvas *  self, SuiCore$Image *  img, float  sx, float  sy, float  sw, float  sh, float  dx, float  dy, float  dw, float  dh, float  alpha);
extern void  SuiCore$Canvas$linearGradient(SuiCore$Canvas *  self, bool  fill, float  sx, float  sy, float  ex, float  ey, int  icolor, int  ocol);
extern void  SuiCore$Canvas$boxGradient(SuiCore$Canvas *  self, bool  fill, float  x, float  y, float  w, float  h, float  r, float  f, int  icol, int  ocol);
extern void  SuiCore$Canvas$radialGradient(SuiCore$Canvas *  self, bool  fill, float  cx, float  cy, float  inr, float  outr, int  icol, int  ocol);
extern void  SuiCore$Canvas$imagePattern(SuiCore$Canvas *  self, bool  fill, float  ox, float  oy, float  ex, float  ey, float  angle, SuiCore$Image *  image, float  alpha);
extern int  SuiCore$Canvas$_createImageRGBA(SuiCore$Canvas *  self, int  w, int  h, int  imgFlags, const unsigned char *  imgData);
SuiCore$Image*  SuiCore$Canvas$createImageRGBA(SuiCore$Image **  __outRef__, SuiCore$Canvas *  self, int  w, int  h, const unsigned char *  imgData);
extern int  SuiCore$Canvas$_createImage(SuiCore$Canvas *  self, const char *  path);
SuiCore$Image*  SuiCore$Canvas$createImage(SuiCore$Image **  __outRef__, SuiCore$Canvas *  self, const char *  path);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
