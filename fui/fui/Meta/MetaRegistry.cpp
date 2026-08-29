#include "MetaRegistry.h"

MetaRegistry* MetaRegistry::instance() {
	static MetaRegistry reg;
	return &reg;
}

void MetaRegistry::registerClass(const std::string& name, const std::string& parent) {
	if (classes.find(name) != classes.end()) {
		return;
	}
	MetaClass mc;
	mc.name = name;
	mc.parent = parent;
	classes[name] = mc;
}

void MetaRegistry::registerProperty(const std::string& className, const std::string& propName,
	const std::string& typeName) {
	registerClass(className);
	auto& mc = classes[className];
	for (auto& p : mc.properties) {
		if (p.name == propName) {
			if (p.typeName.empty()) p.typeName = typeName;
			return;
		}
	}
	mc.properties.push_back(MetaProperty(propName, typeName));
}

void MetaRegistry::registerGetter(const std::string& className, const std::string& propName,
	std::function<void*(void*)> getter) {
	registerClass(className);
	auto& mc = classes[className];
	for (auto& p : mc.properties) {
		if (p.name == propName) {
			p.getter = getter;
			return;
		}
	}
	MetaProperty prop(propName);
	prop.getter = getter;
	mc.properties.push_back(prop);
}

void MetaRegistry::registerSetter(const std::string& className, const std::string& propName,
	std::function<void(void*, void*)> setter) {
	registerClass(className);
	auto& mc = classes[className];
	for (auto& p : mc.properties) {
		if (p.name == propName) {
			p.setter = setter;
			return;
		}
	}
	MetaProperty prop(propName);
	prop.setter = setter;
	mc.properties.push_back(prop);
}

void MetaRegistry::registerProperty(const std::string& className, const std::string& propName,
	const std::string& typeName,
	std::function<void*(void*)> getter,
	std::function<void(void*, void*)> setter) {
	registerClass(className);
	auto& mc = classes[className];
	for (auto& p : mc.properties) {
		if (p.name == propName) {
			p.typeName = typeName;
			p.getter = getter;
			p.setter = setter;
			return;
		}
	}
	mc.properties.push_back(MetaProperty(propName, typeName));
	mc.properties.back().getter = getter;
	mc.properties.back().setter = setter;
}

MetaClass* MetaRegistry::findClass(const std::string& name) {
	auto it = classes.find(name);
	if (it != classes.end()) {
		return &it->second;
	}
	return nullptr;
}

MetaProperty* MetaRegistry::findProperty(const std::string& className, const std::string& propName) {
	MetaClass* mc = findClass(className);
	if (!mc) return nullptr;
	return mc->findProperty(propName);
}

void* MetaRegistry::getPropertyPtr(void* obj, const std::string& className, const std::string& propName) {
	MetaProperty* prop = findProperty(className, propName);
	if (prop && prop->getter) {
		return prop->getter(obj);
	}
	return nullptr;
}

bool MetaRegistry::setPropertyPtr(void* obj, const std::string& className, const std::string& propName, void* val) {
	MetaProperty* prop = findProperty(className, propName);
	if (prop && prop->setter) {
		prop->setter(obj, val);
		return true;
	}
	return false;
}

std::string MetaRegistry::getPropertyValue(void* obj, const std::string& className, const std::string& propName) {
	MetaProperty* prop = findProperty(className, propName);
	if (prop && prop->toString) {
		return prop->toString(obj);
	}
	return "";
}

bool MetaRegistry::setPropertyValue(void* obj, const std::string& className, const std::string& propName, const std::string& value) {
	MetaProperty* prop = findProperty(className, propName);
	if (prop && prop->fromString) {
		prop->fromString(obj, value);
		return true;
	}
	return false;
}
