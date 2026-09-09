#include "Emitter.h"

#include <rttr/registration>

Emitter* useEbus() {
	static Ref<Emitter> ins{new Emitter()};
	if (ins == nullptr) {
		ins = new Emitter();
	}
	return ins;
}

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Emitter>("Emitter")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("getClassName", &Emitter::getClassName)
		.method("addListener", &Emitter::addListener)
		.method("removeListener", &Emitter::removeListener)
		.method("emit", &Emitter::emit);
}

