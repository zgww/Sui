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
#include "../Naga/MathEx.h"

// Math constants
//static constexpr float PI = 3.14159265358979323846f;
//static constexpr float EPSILON = 1e-5f;
static constexpr float infinity = std::numeric_limits<float>::infinity();
static constexpr float NAN_F = std::numeric_limits<float>::quiet_NaN();

// Math utility functions
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