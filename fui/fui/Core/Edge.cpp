#include "Edge.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Edge>("Edge")
		.constructor<>()(policy::ctor::as_object)
		.property("w", &Edge::w)
		.property("color", &Edge::color)
		.method("set", &Edge::set)
		.method("copyFrom", &Edge::copyFrom);
}
