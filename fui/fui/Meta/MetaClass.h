#pragma once

#include "MetaProperty.h"
#include <vector>
#include <string>

class MetaRegistry;
class GcObj;
template<typename T> class Ref;

struct MetaClass {
	std::string name;
	std::string parent;
	std::vector<MetaProperty> properties;

	MetaProperty* findProperty(const std::string& propName);
	const MetaProperty* findProperty(const std::string& propName) const;

	std::vector<MetaProperty*> getAllProperties(MetaRegistry* reg);

	void* getValue(void* obj, std::string propertyName);
	void setValue(void* obj, std::string propertyName, void* propertyValue);

	void setValueRefGcObj(void* obj, std::string propertyName, Ref<GcObj> propertyValue);
	void setValueBool(void* obj, std::string propertyName, bool propertyValue);
	void setValueInt(void* obj, std::string propertyName, int propertyValue);
	void setValueFloat(void* obj, std::string propertyName, float propertyValue);
	void setValueDouble(void* obj, std::string propertyName, double propertyValue);
	void setValueString(void* obj, std::string propertyName, std::string propertyValue);
};
