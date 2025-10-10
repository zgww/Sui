package SuiCore
#include <stdio.h>
#include "../../nanovg/nanovg.h"
#include "../../nanovg/stb_image_write.h"

import * from "./Global.orc"
import * from "./Vec2.orc"
import * from "./Canvas.orc"
import * from "../../Orc/Map.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Buffer.orc"

class Image {
	int _img = 0

	Vec2 size(){
		return mkVec2(self.width(), self.height())
	}

	float width(){
		if (self._img == 0){
			return 0;
		}
		int w = 0;
		int h = 0
		nvgImageSize(Global_getVg(), self._img, &w, & h);
		return (float)w;
	}
	float height(){
		if (self._img == 0){
			return 0;
		} 
		int w = 0;
		int h = 0
		nvgImageSize(Global_getVg(), self._img, &w, & h);
		return (float)h;
	}
}


//将floats转为0-255写到png中
void Image_writeFloatsAsGrey_toPng(const char *topath, int w, int h, float *vs){
	Buffer@ b = new Buffer()
	Image_convertFloatsToGreyBuffer(
		b, w, h, vs
	)
	// int cnt = w * h
	// b.initSize(cnt)
	// for int i = 0; i < cnt; i++{
	// 	unsigned char c = vs[i] * 255
	// 	b.data[i] = c
	// }
	stbi_write_png(topath, w, h, 1, b.data, 0)
}
void Image_writeRgbas_toPng(const char *topath, int w, int h, unsigned char *rgbas){
	stbi_write_png(topath, w, h, 4, rgbas, 0)
}
//将floats转为0-255写到png中
void Image_writeFloatsAsRgba_toPng(const char *topath, int w, int h, float *vs){
	Buffer@ b = new Buffer()
	Image_convertFloatsToRgbaBuffer(
		b, w, h, vs
	)
	// int cnt = w * h
	// b.initSize(cnt)
	// for int i = 0; i < cnt; i++{
	// 	unsigned char c = vs[i] * 255
	// 	b.data[i] = c
	// }
	stbi_write_png(topath, w, h, 4, b.data, 0)
}
//将floats转为0-255的数据，放到buffer中
void Image_convertFloatsToGreyBuffer(Buffer*b,  int w, int h, float *vs){
	int cnt = w * h
	b.initSize(cnt)
	for int i = 0; i < cnt; i++{
		unsigned char c = vs[i] * 255
		b.data[i] = c
	}
}
void Image_convertFloatsToRgbaBuffer(Buffer*b,  int w, int h, float *vs){
	int cnt = w * h
	b.initSize(cnt * 4)
	for int i = 0; i < cnt; i++{
		int idx = i * 4
		unsigned char c = vs[i] * 255
		b.data[idx] = c
		b.data[idx+1] = c
		b.data[idx+2] = c
		b.data[idx+3] = 255
	}
}
 
Map@ getImageMap(){
    static Map@ imageMap = null
	if (!imageMap){
		imageMap = new Map()
	}
	return imageMap
}


//加载图片
Image@ loadImage(const char *path){
	Map@ cache = getImageMap()
	{
		int size = cache.size();
		Image@ ret = (Image@)cache.get(path)
		if (ret){
			return ret
		}
	}

	Canvas *canvas = Global_getCanvas();

	String@ acpPath = String_toActiveCodePage(path)

	Image@ ret = canvas.createImage(acpPath.str)

	// int id = nvgCreateImage(vg, acpPath.str, NVG_IMAGE_REPEATX|NVG_IMAGE_REPEATY);
	// Image@ ret = new Image()
	// ret._img = id

	cache.put(path, ret);

	return ret
}