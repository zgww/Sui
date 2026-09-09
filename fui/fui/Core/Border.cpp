#include "Border.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Border>("Border")
		.constructor<>()(policy::ctor::as_object)
		.property("t", &Border::t)
		.property("r", &Border::r)
		.property("b", &Border::b)
		.property("l", &Border::l)
		.method("isAllHasWidth", &Border::isAllHasWidth)
		.method("setAll", &Border::setAll)
		.method("copyFrom", &Border::copyFrom)
		.method("hor", &Border::hor)
		.method("ver", &Border::ver);
}
