#include "MathEx.h"
#include <string>
#include <cmath>

char * MathEx_objkey(void* obj, const char * subfix) {
	auto ret = std::to_string((size_t)obj) + subfix;
	return _strdup(ret.c_str());
}

bool MathEx_floatIsEqual(const float a, const float b) {

	//if (isUndefined(a)) {
	//  return isUndefined(b);
	//}
	//if (isUndefined(b)) {
	//  return isUndefined(a);
	//}
	return std::fabs(a - b) < 0.0001f;
}

float MathEx_floorMod(float x, float y) {
	float n = std::floor(x / y);
	auto ret = x - n * y;
	return ret;
}
float MathEx_quadBezier(float p0, float p1, float p2, float t) {
	auto pt = 1 - t;
	float ret = pt * pt * p0 + 2 * pt * t * p1 + t * t * p2;
	return ret;
}
float MathEx_cubicBezier(float p0, float p1, float p2, float p3, float t) {
	auto pt = 1 - t;
	float ret = pt * pt * pt * p0 + 3 * pt * pt * t * p1 + 3 * pt * t * t * p2 + t * t * t * p3;
	return ret;
}

bool MathEx_floatNearlyZero(const float a) {
	return MathEx_floatIsEqual(a, 0.f);
}

double MathEx_lerpd(double f, double t, double r) {
	return (t - f) * r + f;
}
float MathEx_lerpf(float f, float t, float r) {
	return (t - f) * r + f;
}
int MathEx_lerpi(int f, int t, float r) {
	return (int)((t - f) * r + f);
}	
float MathEx_rad(float deg) { return deg / 180.f * (float)MATHEX_PI; };
float MathEx_deg(float rad) { return rad / (float)MATHEX_PI * 180.f; };

int MathEx_maxi(int a, int b) {
	return a >= b ? a : b;
}
int MathEx_mini(int a, int b) {
	return a >= b ? b : a;
}
int MathEx_maxf(float a, float b) {
	return a >= b ? a : b;
}
int MathEx_minf(float a, float b) {
	return a >= b ? b : a;
}
