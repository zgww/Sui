#include "Inset.h"
#include "../Meta/MetaRegistry.h"

void Inset::registerMeta() {
	auto reg = MetaRegistry::instance()->registerClass<Inset>();

	reg.property("left", &Inset::left);
	reg.property("top", &Inset::top);
	reg.property("right", &Inset::right);
	reg.property("bottom", &Inset::bottom);
}
