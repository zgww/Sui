#include "Inset.h"
#include "../Meta/MetaRegistry.h"

//#include <rttr/registration>

void Inset::registerMeta() {
	auto reg = MetaRegistry::instance()->registerClass<Inset>();

	reg.property("left", &Inset::left);
	reg.property("top", &Inset::top);
	reg.property("right", &Inset::right);
	reg.property("bottom", &Inset::bottom);
}
//
//RTTR_REGISTRATION
//{
//	using namespace rttr;
//
//	registration::class_<Inset>("Inset")
//		.constructor<>()(policy::ctor::as_object)
//		.constructor(static_cast<Inset(*)(float, float, float, float)>(&mkInset))
//		.property("left", &Inset::left)
//		.property("top", &Inset::top)
//		.property("right", &Inset::right)
//		.property("bottom", &Inset::bottom)
//		.method("setAll", &Inset::setAll)
//		.method("setAxis", &Inset::setAxis)
//		.method("setHor", &Inset::setHor)
//		.method("setVer", &Inset::setVer)
//		.method("hor", &Inset::hor)
//		.method("ver", &Inset::ver)
//		.method("invert", &Inset::invert);
//}
