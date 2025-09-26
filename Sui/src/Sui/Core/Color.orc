package SuiCore

#include <stdio.h>
#include <math.h>
#include "../../nanovg/nanovg.h"
import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "./Vec3.orc"

struct Rgbaf {
    float r
    float g
    float b
    float a
}
extension Rgbaf {
    String@ toString(){
        char buf[256];
        sprintf(buf, "Rgbaf(%f,%f,%f,%f)", self.r, self.g, self.b, self.a)
        String@ s = str(buf)
        return s 
    }
    Vec3 toVec3(){
        return mkVec3(self.r, self.g, self.b)
    }
    Rgba toRgba(){
        Rgba ret;
        ret.r = (unsigned char )(self.r * 255.0)
        ret.g = (unsigned char )(self.g * 255.0)
        ret.b = (unsigned char )(self.b * 255.0)
        ret.a = (unsigned char )(self.a * 255.0)
        return ret;
    }
    int toInt(){
        int ret =  self.toRgba().toInt()
        return ret;
    }
}
struct Rgba {
    unsigned char  r
    unsigned char  g
    unsigned char  b
    unsigned char  a
}
struct Hsla {
    float h; // 0-360
    float s;
    float l;
    unsigned char a;
}
//颜色选择器使用hsv
struct Hsva {
    float h; // 0-360
    float s;
    float v;
    unsigned char a;
}
Rgbaf mkRgbafByFloat4(float *f4){
    return mkRgbaf(
        f4[0],
        f4[1],
        f4[2],
        f4[3],
        )
}
Rgbaf mkRgbaf(float r, float g, float b, float a){
    Rgbaf ret
    ret.r = r;
    ret.g = g;
    ret.b = b;
    ret.a = a;
    return ret
}
Rgbaf mkRgbafByInt(int color){
    Rgbaf v;
    v.a = (((color) >> 24) & 0xFF) / 255.0
    v.r = (((color) >> 16) & 0xFF) / 255.0
    v.g = (((color) >>  8) & 0xFF) / 255.0
    v.b = (((color) >>  0) & 0xFF) / 255.0
    return v
}

Rgba mkRgbaByFloat(
    float r,
    float g,
    float b,
    float a
    ){
    Rgba ret;
    ret.r = (unsigned char )(r * 255.0)
    ret.g = (unsigned char )(g * 255.0)
    ret.b = (unsigned char )(b * 255.0)
    ret.a = (unsigned char )(a * 255.0)
    return ret;
}
Rgba mkRgba(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a
    ){
    Rgba ret;
    ret.r = r
    ret.g = g
    ret.b = b
    ret.a = a
    return ret;
}
Hsla mkHsla(float h, float s, float l, unsigned char a){
    Hsla ret;
    ret.h = h
    ret.s = s
    ret.l = l
    ret.a = a
    return ret;
}
Hsva mkHsva(float h, float s, float v, unsigned char a){
    Hsva ret;
    ret.h = h
    ret.s = s
    ret.v = v
    ret.a = a
    return ret;
}
Rgba mkRgbaByInt(int color){
    Rgba rgba;
    rgba.a = (((color) >> 24) & 0xFF)
    rgba.r = (((color) >> 16) & 0xFF)
    rgba.g = (((color) >>  8) & 0xFF)
    rgba.b = (((color) >>  0) & 0xFF)
    return rgba
}
int mkIntByRgba(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a
){
    int c = (
        (a << 24) |
        (r << 16) |
        (g << 8) |
        (b << 0)
    )
    return c
}

Hsva mkHsva_byInt(int color){
    Rgba r = mkRgbaByInt(color)
    Hsva ret = rgbaToHsva(r)
    return ret
}

extension Hsva {
    Rgba toRgba(){
        Rgba ret = hsvaToRgba(*self)
        return ret;
    }
    int toRgbaInt(){
        Rgba r = self.toRgba()
        int c = r.toInt()
        return c
    }
    String@ toString(){
        char tmp[200];
        snprintf(tmp, sizeof(tmp), "hsva(%.4f,%.4f,%.4f,%d)", self.h, self.s, self.v, self.a)
        return str(tmp)
    }
}
extension Hsla {
    Rgba toRgba(){
        NVGcolor c = nvgHSLA(self.h, self.s, self.l, self.a)
        return mkRgbaByFloat(c.r, c.g, c.b, c.a)
    }
    int toRgbaInt(){
        Rgba r = self.toRgba()
        int c = r.toInt()
        return c
    }
    String@ toString(){
        char tmp[200];
        snprintf(tmp, sizeof(tmp), "hsla(%.4f,%.4f,%.4f,%d)", self.h, self.s, self.l, self.a)
        return str(tmp)
    }
}
extension Rgba {
    int toInt(){
        int c = (
            (self.a << 24) |
            (self.r << 16) |
            (self.g << 8) |
            (self.b << 0)
        )
        return c
    }
    String@ toString(){
        char tmp[200];
        snprintf(tmp, sizeof(tmp), "rgba(%d,%d,%d,%d)", self.r, self.g, self.b, self.a)
        return str(tmp)
    }
}


unsigned char colorGetA(int color){
    return (((color) >> 24) & 0xFF)
}
unsigned char colorGetR(int color){
    return (((color) >> 16) & 0xFF)
}
unsigned char colorGetG(int color){
    return (((color) >>  8) & 0xFF)
}
unsigned char colorGetB(int color){
    return (((color) >>  0) & 0xFF)
}

NVGcolor mkNVGColorByInt(int color){

    unsigned char a = (((color) >> 24) & 0xFF)
    unsigned char r = (((color) >> 16) & 0xFF)
    unsigned char g = (((color) >>  8) & 0xFF)
    unsigned char b = (((color) >>  0) & 0xFF)

    return nvgRGBA(r, g, b, a);
}

Hsla rgbaToHsla(
    Rgba rgba
    ) {
    unsigned char red = rgba.r;
    unsigned char green = rgba.g
    unsigned char blue = rgba.b
    unsigned char alpha = rgba.a

    double r = red / 255.0;
    double g = green / 255.0;
    double b = blue / 255.0;

    double maxVal = maxDouble(maxDouble(r, g), b);
    double minVal = minDouble(minDouble(r, g), b);

    double h = 0.0;
    double s = 0.0
    double l = 0.0;
    l = (maxVal + minVal) / 2.0;

    if (maxVal == minVal) {
        h = 0.0; // 灰度色
        s = 0.0;
    } else {
        double d = maxVal - minVal;
        s = l > 0.5 ? d / (2.0 - maxVal - minVal) : d / (maxVal + minVal);

        if (maxVal == r) {
            h = (g - b) / d + (g < b ? 6.0 : 0.0);
        } else if (maxVal == g) {
            h = (b - r) / d + 2.0;
        } else {
            h = (r - g) / d + 4.0;
        }

        h *= 60.0;
    }

    Hsla ret;
    ret.h = h
    ret.s = s
    ret.l = l
    ret.a = alpha
    return ret;
}

// /**
//  * @brief   RGB颜色空间 转  HSV颜色空间 
//  * @param   rgb:RGB颜色空间参数
//  * @param   hsv:HSV颜色空间参数
//  * @note    The R,G,B values are divided by 255 to change the range from 0..255 to 0..1:
//  * @return  none
// */
Hsva rgbaToHsva(Rgba rgb)
{
    float max = 0.0
    float min = 0.0
    float delta=0;
    float r = (float)((float)((int)rgb.r)/255);
    float g = (float)((float)((int)rgb.g)/255);
    float b = (float)((float)((int)rgb.b)/255);
    float h = 0.0
    float s = 0.0
    float v = 0.0

    max = maxFloat(maxFloat(r, g), b);
    min = minFloat(minFloat(r, g), b);
    delta = (max - min);

    //printf("r:%f, g:%f, b:%f\n", r, g, b);

    if (delta == 0) {
        h = 0;
    } else {
        if (r == max) {
            h = ((g-b)/delta)*60.0; 
        } else if (g == max) {
            h = 120.0+(((b-r)/delta)*60.0); 
        } else if (b == max) {
            h = 240.0 + (((r-g)/delta)*60.0);
        }

        if (h < 0) {
            h += 360.0;
        }
    }

    if (max == 0) {
        s = 0;
    } else {
        s = (float)(delta/max);
    }

    v = max;

    Hsva ret;
    ret.h = h
    ret.s = s
    ret.v = v
    ret.a = rgb.a
    return ret
}

// /**
//  * @brief   HSV颜色空间 转 RGB颜色空间
//  * @param   hsv:HSV颜色空间参数
//  * @param   rgb:RGB颜色空间参数
//  * @note    When 0 ≤ H < 360, 0 ≤ S ≤ 1 and 0 ≤ V ≤ 1:
//  * @return  none
// */
Rgba hsvaToRgba(Hsva hsv)
{
    int i = 0
    float f = 0.f
    float a = 0.f
    float b = 0.f
    float c = 0.f
    Rgba rgb
    rgb.r = 0.0
    rgb.g = 0.0
    rgb.b = 0.0
    rgb.a = hsv.a

    float h = hsv.h;
    float s = hsv.s;
    float v = hsv.v;
	if (h >= 360.0) {
		h = 0.0;
	}
	
    if (s == 0) {
        rgb.r = (unsigned char)((int)(v*255.0));
        rgb.g = (unsigned char)((int)(v*255.0));
        rgb.b = (unsigned char)((int)(v*255.0));
    } else {
        h /= 60.0;  // sector 0 to 5, h_max=360 360/60=6[0,1,2,3,4,5]
        i = (int)floor(h); // floor(h)
        f = h-i; // factorial path of h
        a = v * (1.0-s);
        b = v * (1.0-s*f);
        c = v * (1.0-s*(1.0-f));
        if (i == 0){
            rgb.r = (unsigned char)((int)(v*255.0)); //v*255
            rgb.g = (unsigned char)((int)(c*255.0)); //c*255;
            rgb.b = (unsigned char)((int)(a*255.0)); //a*255;
        }
        else if (i == 1){
            rgb.r = (unsigned char)((int)(b*255.0)); //b*255;
            rgb.g = (unsigned char)((int)(v*255.0)); //v*255;
            rgb.b = (unsigned char)((int)(a*255.0)); //a*255;
        }
        else if (i == 2){
            rgb.r = (unsigned char)((int)(a*255.0)); //a*255;
            rgb.g = (unsigned char)((int)(v*255.0)); //v*255;
            rgb.b = (unsigned char)((int)(c*255.0)); //c*255;
        }
        else if (i == 3){
            rgb.r = (unsigned char)((int)(a*255.0));//a*255;
            rgb.g = (unsigned char)((int)(b*255.0));//b*255;
            rgb.b = (unsigned char)((int)(v*255.0));//v*255;
        }
        else if (i == 4){
            rgb.r = (unsigned char)((int)(c*255.0)); //c*255;
            rgb.g = (unsigned char)((int)(a*255.0)); //a*255;
            rgb.b = (unsigned char)((int)(v*255.0)); //v*255;
        } 
        else {
            rgb.r = (unsigned char)((int)(v*255.0)); //v*255;
            rgb.g = (unsigned char)((int)(a*255.0)); //a*255;
            rgb.b = (unsigned char)((int)(b*255.0)); //b*255;
        }
    }
    return rgb;
}

void testColor(){
    printf("testColor alpha:%x\n", colorGetA(0x33000000));
}