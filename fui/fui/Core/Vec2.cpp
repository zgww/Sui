#include "Vec2.h"

//#include <rttr/registration>
//
//RTTR_REGISTRATION
//{
//	using namespace rttr;
//
//	registration::class_<Vec2>("Vec2")
//		.constructor<>()(policy::ctor::as_object)
//		.constructor(static_cast<Vec2(*)(float, float)>(&mkVec2))
//		.property("x", &Vec2::x)
//		.property("y", &Vec2::y)
//		.method("toString", &Vec2::toString)
//		.method("width", &Vec2::width)
//		.method("height", &Vec2::height)
//		.method("set", &Vec2::set)
//		.method("setScalar", &Vec2::setScalar)
//		.method("setX", &Vec2::setX)
//		.method("setY", &Vec2::setY)
//		.method("clone", &Vec2::clone)
//		.method("copy", &Vec2::copy)
//		.method("dot", &Vec2::dot)
//		.method("cross", &Vec2::cross)
//		.method("length", &Vec2::length)
//		.method("lengthSq", &Vec2::lengthSq)
//		.method("manhattanLength", &Vec2::manhattanLength)
//		.method("normalizeLocal", &Vec2::normalizeLocal)
//		.method("angle", &Vec2::angle)
//		.method("angleTo", &Vec2::angleTo)
//		.method("distanceTo", &Vec2::distanceTo)
//		.method("distanceToSquared", &Vec2::distanceToSquared)
//		.method("manhattanDistanceTo", &Vec2::manhattanDistanceTo)
//		.method("lerpLocal", &Vec2::lerpLocal)
//		.method("add", &Vec2::add)
//		.method("sub", &Vec2::sub)
//		.method("scale", &Vec2::scale)
//		.method("equals", &Vec2::equals);
//}
