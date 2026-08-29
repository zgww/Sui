#pragma once

#include "MetaClass.h"
#include <unordered_map>
#include <string>
#include <functional>

template<typename T>
class MetaClassRegistrar;

class MetaRegistry {
public:
	static MetaRegistry* instance();

	void registerClass(const std::string& name, const std::string& parent = "");

	void registerProperty(const std::string& className, const std::string& propName,
		const std::string& typeName = "");

	void registerGetter(const std::string& className, const std::string& propName,
		std::function<void*(void*)> getter);

	void registerSetter(const std::string& className, const std::string& propName,
		std::function<void(void*, void*)> setter);

	void registerProperty(const std::string& className, const std::string& propName,
		const std::string& typeName,
		std::function<void*(void*)> getter,
		std::function<void(void*, void*)> setter);

	MetaClass* findClass(const std::string& name);
	MetaProperty* findProperty(const std::string& className, const std::string& propName);

	void* getPropertyPtr(void* obj, const std::string& className, const std::string& propName);
	bool setPropertyPtr(void* obj, const std::string& className, const std::string& propName, void* val);

	std::string getPropertyValue(void* obj, const std::string& className, const std::string& propName);
	bool setPropertyValue(void* obj, const std::string& className, const std::string& propName, const std::string& value);

private:
	MetaRegistry() = default;
	std::unordered_map<std::string, MetaClass> classes;

public:
	template<typename T, typename Parent = void>
	MetaClassRegistrar<T> registerClass() {
		std::string name = metaClassName<T>();
		std::string parentName;
		if constexpr (!std::is_void_v<Parent>) {
			parentName = metaClassName<Parent>();
		}
		registerClass(name, parentName);
		return MetaClassRegistrar<T>(name, this);
	}
};

#include "MetaRegistrar.h"
