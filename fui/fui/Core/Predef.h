#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>
#include <limits>

#include "../Urgc/Urgc.h"
#include "../Urgc/GcObj.h"
#include "../Urgc/GcList.h"
#include "../Urgc/GcMap.h"
#include "../nanovg/nanovg.h"

// Math constants
static constexpr float PI = 3.14159265358979323846f;
static constexpr float EPSILON = 1e-5f;
static constexpr float infinity = std::numeric_limits<float>::infinity();
static constexpr float NAN_F = std::numeric_limits<float>::quiet_NaN();

// Math utility functions
inline float minFloat(float a, float b) { return a < b ? a : b; }
inline float maxFloat(float a, float b) { return a > b ? a : b; }
inline float absFloat(float v) { return fabsf(v); }
inline float floorFloat(float v) { return floorf(v); }
inline float ceilFloat(float v) { return ceilf(v); }
inline float roundFloat(float v) { return roundf(v); }
inline bool eqFloat(float a, float b) { return fabsf(a - b) < EPSILON; }
inline float clampFloat(float v, float mn, float mx) { return v < mn ? mn : (v > mx ? mx : v); }
inline int clampInt(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }
inline float lerpFloat(float a, float b, float t) { return a + (b - a) * t; }
inline double minDouble(double a, double b) { return a < b ? a : b; }
inline double maxDouble(double a, double b) { return a > b ? a : b; }

inline int64_t time_unixMs() {
    return (int64_t)std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline int64_t time_unixSec() {
    return (int64_t)std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline void time_sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

class Node;
class View;
class ViewBase;
class Window;
class App;
class Emitter;
class Listener;
class Event;