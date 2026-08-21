#include "Emitter.h"

Emitter* useEbus() {
	static Ref<Emitter> ins{new Emitter()};
	if (ins == nullptr) {
		ins = new Emitter();
	}
	return ins;
}

