#pragma once
#include "NagaPredef.h"
//#include "UrgcIndex.h"
//#include "ColorUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MATHEX_PI 3.14159265358979323846


//
//class NAGA_DLLAPI MathEx {
//public:
//	template<typename T>
//	static T min(T a, T b) {
//		return a < b ? a : b;
//	}
//	template<typename T>
//	static T max(T a, T b) {
//		return a > b ? a : b;
//	}
//
//	//如果min > max,直接返回min
//	template<class T>
//	static T clamp(T x, T min, T max) {
//		if (min >= max) {
//			return min;
//			/*T tmp = min;
//			min = max;
//			max = tmp;*/
//		}
//		if (x > max) return max;
//		if (x < min) return min;
//		return x;
//	}
//	template<typename T>
//	static inline T ku_max(T a, T b) {
//		return (a > b ? a : b);
//	}
//
//
//	
//	/*static int lerpColorByARGB(int f, int t, float r) {
//
//		auto fa = NgColorGetA(f);
//		auto fr = NgColorGetR(f);
//		auto fg = NgColorGetG(f);
//		auto fb = NgColorGetB(f);
//
//		auto tr = NgColorGetR(t);
//		auto tg = NgColorGetG(t);
//		auto tb = NgColorGetB(t);
//		auto ta = NgColorGetA(t); 
//
//		auto red = lerp(fr, tr, r);
//		auto g = lerp(fg, tg, r);
//		auto b = lerp(fb, tb, r);
//		auto a = lerp(fa, ta, r);
//		auto ret = NgColorSetARGB(a, red, g, b);
//		return ret;
//	}*/
//	//static int lerpColorByHsv(int f, int t, float r) {
//	//	auto fa = NgColorGetA(f);
//	//	auto ta = NgColorGetA(t);
//	//	float fhsv[3];
//	//	float thsv[3];
//	//	NgColorToHSV(f, fhsv);
//	//	NgColorToHSV(t, thsv);
//	//	float ohsv[3];
//	//	ohsv[0] = lerp(fhsv[0], thsv[0], r);
//	//	ohsv[1] = lerp(fhsv[1], thsv[1], r);
//	//	ohsv[2] = lerp(fhsv[2], thsv[2], r);
//	//	auto oa = lerp(fa, ta, r);
//	//	auto ret = NgHSVToColor(ohsv);
//	//	ret = NgColorSetA(ret, oa);
//	//	return ret;
//	//}
//	
//	
//};
NAGA_DLLAPI float MathEx_rad(float deg);
NAGA_DLLAPI float MathEx_deg(float rad);
NAGA_DLLAPI char* MathEx_objkey(void* obj, char* subfix);
NAGA_DLLAPI double MathEx_lerpd(double f, double t, double r);
NAGA_DLLAPI float MathEx_lerpf(float f, float t, float r);
NAGA_DLLAPI int MathEx_lerpi(int f, int t, float r);

NAGA_DLLAPI bool MathEx_floatNearlyZero(const float a);
NAGA_DLLAPI bool MathEx_floatIsEqual(const float a, const float b);
NAGA_DLLAPI float MathEx_floorMod(float x, float y);
NAGA_DLLAPI float MathEx_quadBezier(float p0, float p1, float p2, float t);
NAGA_DLLAPI float MathEx_cubicBezier(float p0, float p1, float p2, float p3, float t);


NAGA_DLLAPI int MathEx_maxi(int a, int b);
NAGA_DLLAPI int MathEx_mini(int a, int b);
NAGA_DLLAPI int MathEx_maxf(float a, float b);
NAGA_DLLAPI int MathEx_minf(float a, float b);

#ifdef __cplusplus
}
#endif