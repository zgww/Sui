#pragma once

#include <string>
#include <functional>

class GcObj;

struct MetaProperty {
	std::string name;
	std::string typeName;

	std::function<void*(void*)> getter;
	std::function<void(void*, void*)> setter;
	std::function<std::string(void*)> toString;
	std::function<void(void*, const std::string&)> fromString;
	std::function<void(void*, GcObj*)> refSetter;

	MetaProperty() = default;

	MetaProperty(const std::string& name, const std::string& typeName = "")
		: name(name), typeName(typeName) {}

	bool hasGetter() const { return getter != nullptr; }
	bool hasSetter() const { return setter != nullptr; }
};
