#include "MetaClass.h"
#include "MetaRegistry.h"
#include "../Urgc/Urgc.h"

MetaProperty* MetaClass::findProperty(const std::string& propName) {
	for (auto& p : properties) {
		if (p.name == propName) {
			return &p;
		}
	}
	return nullptr;
}

const MetaProperty* MetaClass::findProperty(const std::string& propName) const {
	for (auto& p : properties) {
		if (p.name == propName) {
			return &p;
		}
	}
	return nullptr;
}

std::vector<MetaProperty*> MetaClass::getAllProperties(MetaRegistry* reg) {
	std::vector<MetaProperty*> result;
	std::vector<std::string> chain;
	std::string cur = name;
	while (!cur.empty()) {
		chain.push_back(cur);
		MetaClass* mc = reg->findClass(cur);
		if (!mc) break;
		cur = mc->parent;
	}
	for (auto it = chain.rbegin(); it != chain.rend(); ++it) {
		MetaClass* mc = reg->findClass(*it);
		if (!mc) continue;
		for (auto& p : mc->properties) {
			result.push_back(&p);
		}
	}
	return result;
}

void* MetaClass::getValue(void* obj, std::string propertyName) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->getter) {
		return p->getter(obj);
	}
	return nullptr;
}

void MetaClass::setValue(void* obj, std::string propertyName, void* propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->setter) {
		p->setter(obj, propertyValue);
	}
}

void MetaClass::setValueRefGcObj(void* obj, std::string propertyName, Ref<GcObj> propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->refSetter) {
		p->refSetter(obj, propertyValue.get());
	}
}

void MetaClass::setValueBool(void* obj, std::string propertyName, bool propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->setter) {
		p->setter(obj, &propertyValue);
	}
}

void MetaClass::setValueInt(void* obj, std::string propertyName, int propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->setter) {
		p->setter(obj, &propertyValue);
	}
}

void MetaClass::setValueFloat(void* obj, std::string propertyName, float propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->setter) {
		p->setter(obj, &propertyValue);
	}
}

void MetaClass::setValueDouble(void* obj, std::string propertyName, double propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->setter) {
		p->setter(obj, &propertyValue);
	}
}

void MetaClass::setValueString(void* obj, std::string propertyName, std::string propertyValue) {
	MetaProperty* p = findProperty(propertyName);
	if (p && p->setter) {
		p->setter(obj, &propertyValue);
	}
}
