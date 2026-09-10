#include "Menu.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Menu>("Menu")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("getClassName", &Menu::getClassName);
}
