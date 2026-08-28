#pragma once
#include "NagaPredef.h"
//#include "UrgcIndex.h"
//#include "ColorUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <math.h>

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
NAGA_DLLAPI float MathEx_maxf(float a, float b);
NAGA_DLLAPI float MathEx_minf(float a, float b);




inline int absInt(int a) {
    if (a < 0) {
        return -a;
    }
    return a;
}
//归一化. 等于是保留方向，长度置为1

inline float normalFloat(float a) {
    if (a < 0.0) {
        return -1;
    }
    return 1;
}
inline float absFloat(float a) {
    if (a < 0.0) {
        return -a;
    }
    return a;
}
inline int minInt(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

inline int maxInt(int a, int b) {
    if (a < b) {
        return b;
    }
    return a;
}


inline float calcRatio(float value, float left, float right) {
    float range = right - left;
    if (range == 0.0) {
        return 1.0;
    }
    return (value - left) / range;
}

inline float lerpFloat(float f, float t, float r) {
    return (t - f) * r + f;
}


inline float minFloat(float a, float b) {
    if (a < b) {
        return a;
    }
    return b;
}

inline float maxFloat3(float a, float b, float c) {
    float t = a > b ? a : b;
        return t > c ? t : c;
}
inline float maxFloat(float a, float b) {
    if (a < b) {
        return b;
    }
    return a;
}
inline double minDouble(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

inline double maxDouble(double a, double b) {
    if (a < b) {
        return b;
    }
    return a;
}

inline float clampInt(int x, int min, int max) {
    if (min >= max) {
        return (float)min;
    }
    if (x > max) {
        return (float)max;
    }
    if (x < min) {
        return (float)min;
    }
    return (float)x;
}
inline float clampFloat(float x, float min, float max) {
    if (min >= max) {
        return min;
        /*T tmp = min;
        min = max;
        max = tmp;*/
    }
    if (x > max) {
        return max;
    }
    if (x < min) {
        return min;
    }
    return x;
}

inline bool isNaN(float v) {
    return isnan(v);
}
inline float floorFloat(float v) {
    return floor(v);
}

inline float ceilFloat(float v) { return ceilf(v); }
inline float roundFloat(float v) { return roundf(v); }


inline void Math_test() {
    //printf("max float:%f\n", maxFloat(10.f, 12.f));
}


#define EPSILON  0.000000001

inline bool eqFloat(float a, float b) {
    float d = a - b;
    if (d < 0) {
        d = -d;
    }
    return d < EPSILON;

}

#define  LN2  0.6931471805599453
#define  PI  3.141592653589793
#define  PIf  3.141592653589793f

inline double toRad(double degree) {
    return degree / 180.0 * PI;
}
inline double toDeg(double rad) {
    return rad / PI * 180.0;
}




inline int floatSize() {
    return sizeof(float);
}
inline int doubleSize() {
    return sizeof(double);
}
inline int shortSize() {
    return sizeof(short);
}
inline int intSize() {
    return sizeof(int);
}
inline int longSize() {
    return sizeof(long);
}
inline int longLongSize() {
    return sizeof(long long);
}
inline int pointerSize() {
    return sizeof(void*);
}
inline float rand01f() {
    float b = (float)(rand() / (RAND_MAX + 1.0));
    return b;
}

inline int randRange(int fromV, int toV) {
    int v = rand() % (toV - fromV) + fromV;
    return v;
}
inline float random() {
    return rand01f();
}
inline float randRangef(float fromV, float toV) {
    float ratio = rand01f();
        // printf("randRangef ratio:%f\n", ratio)

    float v = ratio * (toV - fromV) + fromV;
    return v;
}
inline float randRadiusf(float radius) {
    float v = randRangef(-radius, radius);
        return v;
}


// compute euclidean modulo of m % n
// https://en.wikipedia.org/wiki/Modulo_operation
inline float euclideanModulo(float n, float m) {

    return fmodf((fmodf(n, m) + m), m);

}

// Linear mapping from range <a1, a2> to range <b1, b2>
inline float mapLinear(float x, float a1, float a2, float b1, float b2) {

    return b1 + (x - a1) * (b2 - b1) / (a2 - a1);

}

// https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/inverse-lerp-a-super-useful-yet-often-overlooked-function-r5230/
inline float inverseLerp(float x, float y, float value) {

    if (x != y) {
        return (value - x) / (y - x);

    }
    else {
        return 0;
    }

}

// http://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/
inline float damp(float x, float y, float lambda, float dt) {

    return lerpFloat(x, y, 1 - exp(-lambda * dt));

}

// https://www.desmos.com/calculator/vcsjnyz7x4
inline float pingpong(float x, float length) {
    //length defualt = 1

    return length - absFloat(euclideanModulo(x, length * 2) - length);

}

// http://en.wikipedia.org/wiki/Smoothstep
inline float smoothstep(float x, float min, float max) {

    if (x <= min) { return 0; }
    if (x >= max) { return 1; }

    x = (x - min) / (max - min);

    return x * x * (3 - 2 * x);

}

inline float smootherstep(float x, float min, float max) {

    if (x <= min) { return 0; }
    if (x >= max) { return 1; }

    x = (x - min) / (max - min);

    return x * x * x * (x * (x * 6 - 15) + 10);

}


inline bool isPowerOfTwo(int value) {

    return (value & (value - 1)) == 0 && value != 0;

}

inline float ceilPowerOfTwo(float value) {

    return (float)pow(2, ceil(log(value) / LN2));

}

inline float floorPowerOfTwo(float value) {

    return (float)pow(2, floor(log(value) / LN2));

}



#ifdef __cplusplus
}
#endif