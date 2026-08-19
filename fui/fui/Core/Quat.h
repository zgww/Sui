#pragma once

#include "Quaternion.h"

struct Quat : public Quaternion {
	Quat() = default;
	Quat(const Quaternion& q) : Quaternion(q) {}
};
