
#include "Color_orc.h" 

#include <stdio.h>
#include <math.h>
#include "../../nanovg/nanovg.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Vec3_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Rgbaf_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Rgbaf", sizeof( SuiCore$Rgbaf ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "r", OrcMetaType_float, offsetof(SuiCore$Rgbaf, r), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "g", OrcMetaType_float, offsetof(SuiCore$Rgbaf, g), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "b", OrcMetaType_float, offsetof(SuiCore$Rgbaf, b), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "a", OrcMetaType_float, offsetof(SuiCore$Rgbaf, a), 0, 0, 0, 0);//float
    }
	return meta;
}
Orc$String*  SuiCore$Rgbaf$toString(Orc$String **  __outRef__, SuiCore$Rgbaf *  self){
	char  buf[256];
	sprintf(buf, "Rgbaf(%f,%f,%f,%f)", self->r, self->g, self->b, self->a) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), buf) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, s) ; 
}

SuiCore$Vec3 SuiCore$Rgbaf$toVec3(SuiCore$Rgbaf *  self){
	return SuiCore$mkVec3(self->r, self->g, self->b) ; 
}

SuiCore$Rgba SuiCore$Rgbaf$toRgba(SuiCore$Rgbaf *  self){
	SuiCore$Rgba ret;
	ret.r = (unsigned char )(self->r * 255.0);
	ret.g = (unsigned char )(self->g * 255.0);
	ret.b = (unsigned char )(self->b * 255.0);
	ret.a = (unsigned char )(self->a * 255.0);
	return ret; 
}

int  SuiCore$Rgbaf$toInt(SuiCore$Rgbaf *  self){
	SuiCore$Rgba tmpStructThis1;
	int  ret = SuiCore$Rgba$toInt((tmpStructThis1 = SuiCore$Rgbaf$toRgba(self) ,&tmpStructThis1)) ;
	return ret; 
}


// get or init meta 
MetaStruct* SuiCore$Rgba_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Rgba", sizeof( SuiCore$Rgba ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "r", OrcMetaType_char, offsetof(SuiCore$Rgba, r), 1, 0, 0, 0);//unsignedchar
		orc_metaField_primitive(&pNext, "g", OrcMetaType_char, offsetof(SuiCore$Rgba, g), 1, 0, 0, 0);//unsignedchar
		orc_metaField_primitive(&pNext, "b", OrcMetaType_char, offsetof(SuiCore$Rgba, b), 1, 0, 0, 0);//unsignedchar
		orc_metaField_primitive(&pNext, "a", OrcMetaType_char, offsetof(SuiCore$Rgba, a), 1, 0, 0, 0);//unsignedchar
    }
	return meta;
}

// get or init meta 
MetaStruct* SuiCore$Hsla_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Hsla", sizeof( SuiCore$Hsla ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "h", OrcMetaType_float, offsetof(SuiCore$Hsla, h), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "s", OrcMetaType_float, offsetof(SuiCore$Hsla, s), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "l", OrcMetaType_float, offsetof(SuiCore$Hsla, l), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "a", OrcMetaType_char, offsetof(SuiCore$Hsla, a), 1, 0, 0, 0);//unsignedchar
    }
	return meta;
}

// get or init meta 
MetaStruct* SuiCore$Hsva_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Hsva", sizeof( SuiCore$Hsva ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "h", OrcMetaType_float, offsetof(SuiCore$Hsva, h), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "s", OrcMetaType_float, offsetof(SuiCore$Hsva, s), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "v", OrcMetaType_float, offsetof(SuiCore$Hsva, v), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "a", OrcMetaType_char, offsetof(SuiCore$Hsva, a), 1, 0, 0, 0);//unsignedchar
    }
	return meta;
}
SuiCore$Rgbaf SuiCore$mkRgbafByFloat4(float *  f4){
	return SuiCore$mkRgbaf(f4[0], f4[1], f4[2], f4[3]) ; 
}

SuiCore$Rgbaf SuiCore$mkRgbaf(float  r, float  g, float  b, float  a){
	SuiCore$Rgbaf ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.a = a;
	return ret; 
}

SuiCore$Rgbaf SuiCore$mkRgbafByInt(int  color){
	SuiCore$Rgbaf v;
	v.a = (((color) >> 24) & 0xFF) / 255.0;
	v.r = (((color) >> 16) & 0xFF) / 255.0;
	v.g = (((color) >> 8) & 0xFF) / 255.0;
	v.b = (((color) >> 0) & 0xFF) / 255.0;
	return v; 
}

SuiCore$Rgba SuiCore$mkRgbaByFloat(float  r, float  g, float  b, float  a){
	SuiCore$Rgba ret;
	ret.r = (unsigned char )(r * 255.0);
	ret.g = (unsigned char )(g * 255.0);
	ret.b = (unsigned char )(b * 255.0);
	ret.a = (unsigned char )(a * 255.0);
	return ret; 
}

SuiCore$Rgba SuiCore$mkRgba(unsigned char  r, unsigned char  g, unsigned char  b, unsigned char  a){
	SuiCore$Rgba ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.a = a;
	return ret; 
}

SuiCore$Hsla SuiCore$mkHsla(float  h, float  s, float  l, unsigned char  a){
	SuiCore$Hsla ret;
	ret.h = h;
	ret.s = s;
	ret.l = l;
	ret.a = a;
	return ret; 
}

SuiCore$Hsva SuiCore$mkHsva(float  h, float  s, float  v, unsigned char  a){
	SuiCore$Hsva ret;
	ret.h = h;
	ret.s = s;
	ret.v = v;
	ret.a = a;
	return ret; 
}

SuiCore$Rgba SuiCore$mkRgbaByInt(int  color){
	SuiCore$Rgba rgba;
	rgba.a = (((color) >> 24) & 0xFF);
	rgba.r = (((color) >> 16) & 0xFF);
	rgba.g = (((color) >> 8) & 0xFF);
	rgba.b = (((color) >> 0) & 0xFF);
	return rgba; 
}

int  SuiCore$mkIntByRgba(unsigned char  r, unsigned char  g, unsigned char  b, unsigned char  a){
	int  c = ((a << 24) | (r << 16) | (g << 8) | (b << 0));
	return c; 
}

SuiCore$Hsva SuiCore$mkHsva_byInt(int  color){
	SuiCore$Rgba r = SuiCore$mkRgbaByInt(color) ;
	SuiCore$Hsva ret = SuiCore$rgbaToHsva(r) ;
	return ret; 
}

SuiCore$Rgba SuiCore$Hsva$toRgba(SuiCore$Hsva *  self){
	SuiCore$Rgba ret = SuiCore$hsvaToRgba(*self) ;
	return ret; 
}

int  SuiCore$Hsva$toRgbaInt(SuiCore$Hsva *  self){
	SuiCore$Rgba r = SuiCore$Hsva$toRgba(self) ;
	int  c = SuiCore$Rgba$toInt(&r) ;
	return c; 
}

Orc$String*  SuiCore$Hsva$toString(Orc$String **  __outRef__, SuiCore$Hsva *  self){
	char  tmp[200];
	snprintf(tmp, sizeof(tmp) , "hsva(%.4f,%.4f,%.4f,%d)", self->h, self->s, self->v, self->a) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}

SuiCore$Rgba SuiCore$Hsla$toRgba(SuiCore$Hsla *  self){
	NVGcolor c = nvgHSLA(self->h, self->s, self->l, self->a) ;
	return SuiCore$mkRgbaByFloat(c.r, c.g, c.b, c.a) ; 
}

int  SuiCore$Hsla$toRgbaInt(SuiCore$Hsla *  self){
	SuiCore$Rgba r = SuiCore$Hsla$toRgba(self) ;
	int  c = SuiCore$Rgba$toInt(&r) ;
	return c; 
}

Orc$String*  SuiCore$Hsla$toString(Orc$String **  __outRef__, SuiCore$Hsla *  self){
	char  tmp[200];
	snprintf(tmp, sizeof(tmp) , "hsla(%.4f,%.4f,%.4f,%d)", self->h, self->s, self->l, self->a) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}

int  SuiCore$Rgba$toInt(SuiCore$Rgba *  self){
	int  c = ((self->a << 24) | (self->r << 16) | (self->g << 8) | (self->b << 0));
	return c; 
}

Orc$String*  SuiCore$Rgba$toString(Orc$String **  __outRef__, SuiCore$Rgba *  self){
	char  tmp[200];
	snprintf(tmp, sizeof(tmp) , "rgba(%d,%d,%d,%d)", self->r, self->g, self->b, self->a) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}

unsigned char  SuiCore$colorGetA(int  color){
	return (((color) >> 24) & 0xFF); 
}

unsigned char  SuiCore$colorGetR(int  color){
	return (((color) >> 16) & 0xFF); 
}

unsigned char  SuiCore$colorGetG(int  color){
	return (((color) >> 8) & 0xFF); 
}

unsigned char  SuiCore$colorGetB(int  color){
	return (((color) >> 0) & 0xFF); 
}

NVGcolor SuiCore$mkNVGColorByInt(int  color){
	unsigned char  a = (((color) >> 24) & 0xFF);
	unsigned char  r = (((color) >> 16) & 0xFF);
	unsigned char  g = (((color) >> 8) & 0xFF);
	unsigned char  b = (((color) >> 0) & 0xFF);
	return nvgRGBA(r, g, b, a) ; 
}

SuiCore$Hsla SuiCore$rgbaToHsla(SuiCore$Rgba rgba){
	unsigned char  red = rgba.r;
	unsigned char  green = rgba.g;
	unsigned char  blue = rgba.b;
	unsigned char  alpha = rgba.a;
	double  r = red / 255.0;
	double  g = green / 255.0;
	double  b = blue / 255.0;
	double  maxVal = Orc$maxDouble(Orc$maxDouble(r, g) , b) ;
	double  minVal = Orc$minDouble(Orc$minDouble(r, g) , b) ;
	double  h = 0.0;
	double  s = 0.0;
	double  l = 0.0;
	l = (maxVal + minVal) / 2.0;
	if (maxVal == minVal) {
		h = 0.0;
		s = 0.0;
	}
	else {
		double  d = maxVal - minVal;
		s = l > 0.5 ? d / (2.0 - maxVal - minVal) : d / (maxVal + minVal);
		if (maxVal == r) {
			h = (g - b) / d + (g < b ? 6.0 : 0.0);
		}
		else if (maxVal == g) {
			h = (b - r) / d + 2.0;
		}
		else {
			h = (r - g) / d + 4.0;
		}
		h *= 60.0;
	}
	SuiCore$Hsla ret;
	ret.h = h;
	ret.s = s;
	ret.l = l;
	ret.a = alpha;
	return ret; 
}

SuiCore$Hsva SuiCore$rgbaToHsva(SuiCore$Rgba rgb){
	float  max = 0.0;
	float  min = 0.0;
	float  delta = 0;
	float  r = (float )((float )((int )rgb.r) / 255);
	float  g = (float )((float )((int )rgb.g) / 255);
	float  b = (float )((float )((int )rgb.b) / 255);
	float  h = 0.0;
	float  s = 0.0;
	float  v = 0.0;
	max = Orc$maxFloat(Orc$maxFloat(r, g) , b) ;
	min = Orc$minFloat(Orc$minFloat(r, g) , b) ;
	delta = (max - min);
	if (delta == 0) {
		h = 0;
	}
	else {
		if (r == max) {
			h = ((g - b) / delta) * 60.0;
		}
		else if (g == max) {
			h = 120.0 + (((b - r) / delta) * 60.0);
		}
		else if (b == max) {
			h = 240.0 + (((r - g) / delta) * 60.0);
		}
		if (h < 0) {
			h += 360.0;
		}
	}
	if (max == 0) {
		s = 0;
	}
	else {
		s = (float )(delta / max);
	}
	v = max;
	SuiCore$Hsva ret;
	ret.h = h;
	ret.s = s;
	ret.v = v;
	ret.a = rgb.a;
	return ret; 
}

SuiCore$Rgba SuiCore$hsvaToRgba(SuiCore$Hsva hsv){
	int  i = 0;
	float  f = 0.f;
	float  a = 0.f;
	float  b = 0.f;
	float  c = 0.f;
	SuiCore$Rgba rgb;
	rgb.r = 0.0;
	rgb.g = 0.0;
	rgb.b = 0.0;
	rgb.a = hsv.a;
	float  h = hsv.h;
	float  s = hsv.s;
	float  v = hsv.v;
	if (h >= 360.0) {
		h = 0.0;
	}
	if (s == 0) {
		rgb.r = (unsigned char )((int )(v * 255.0));
		rgb.g = (unsigned char )((int )(v * 255.0));
		rgb.b = (unsigned char )((int )(v * 255.0));
	}
	else {
		h /= 60.0;
		i = (int )floor(h) ;
		f = h - i;
		a = v * (1.0 - s);
		b = v * (1.0 - s * f);
		c = v * (1.0 - s * (1.0 - f));
		if (i == 0) {
			rgb.r = (unsigned char )((int )(v * 255.0));
			rgb.g = (unsigned char )((int )(c * 255.0));
			rgb.b = (unsigned char )((int )(a * 255.0));
		}
		else if (i == 1) {
			rgb.r = (unsigned char )((int )(b * 255.0));
			rgb.g = (unsigned char )((int )(v * 255.0));
			rgb.b = (unsigned char )((int )(a * 255.0));
		}
		else if (i == 2) {
			rgb.r = (unsigned char )((int )(a * 255.0));
			rgb.g = (unsigned char )((int )(v * 255.0));
			rgb.b = (unsigned char )((int )(c * 255.0));
		}
		else if (i == 3) {
			rgb.r = (unsigned char )((int )(a * 255.0));
			rgb.g = (unsigned char )((int )(b * 255.0));
			rgb.b = (unsigned char )((int )(v * 255.0));
		}
		else if (i == 4) {
			rgb.r = (unsigned char )((int )(c * 255.0));
			rgb.g = (unsigned char )((int )(a * 255.0));
			rgb.b = (unsigned char )((int )(v * 255.0));
		}
		else {
			rgb.r = (unsigned char )((int )(v * 255.0));
			rgb.g = (unsigned char )((int )(a * 255.0));
			rgb.b = (unsigned char )((int )(b * 255.0));
		}
	}
	return rgb; 
}

void  SuiCore$testColor(){
	printf("testColor alpha:%x\n", SuiCore$colorGetA(0x33000000) ) ;
}



