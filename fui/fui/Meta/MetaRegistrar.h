#pragma once

#include "MetaRegistry.h"
#include <type_traits>

template<typename T> class Ref;

// ===== Ref type traits =====
template<typename T>
struct is_ref : std::false_type {};

template<typename T>
struct is_ref<Ref<T>> : std::true_type {};

template<typename T>
inline constexpr bool is_ref_v = is_ref<T>::value;

template<typename T>
struct ref_inner { using type = void; };

template<typename T>
struct ref_inner<Ref<T>> { using type = T; };

template<typename T>
using ref_inner_t = typename ref_inner<T>::type;

// ===== Class name from typeid =====
template<typename T>
std::string metaClassName() {
	std::string s = typeid(T).name();
	if (s.compare(0, 6, "class ") == 0) return s.substr(6);
	if (s.compare(0, 7, "struct ") == 0) return s.substr(7);
	return s;
}

// ===== Object serialization (key=val, nested with {}) =====
inline std::string metaSerializeObject(MetaClass* mc, void* obj) {
	std::string result;
	bool first = true;
	for (auto& p : mc->properties) {
		if (!p.toString) continue;
		if (!first) result += ",";
		first = false;
		result += p.name + "=";
		std::string val = p.toString(obj);
		if (val.find(',') != std::string::npos) {
			result += "{" + val + "}";
		} else {
			result += val;
		}
	}
	return result;
}

inline bool metaDeserializeObject(MetaClass* mc, void* obj, const std::string& str) {
	if (str.empty()) return false;
	size_t pos = 0;
	while (pos < str.size()) {
		size_t eq = str.find('=', pos);
		if (eq == std::string::npos) break;
		std::string key = str.substr(pos, eq - pos);
		pos = eq + 1;
		std::string val;
		if (pos < str.size() && str[pos] == '{') {
			int depth = 1;
			size_t start = ++pos;
			while (pos < str.size() && depth > 0) {
				if (str[pos] == '{') depth++;
				else if (str[pos] == '}') depth--;
				if (depth > 0) pos++;
			}
			val = str.substr(start, pos - start);
			if (pos < str.size()) pos++;
		} else {
			size_t comma = str.find(',', pos);
			if (comma == std::string::npos) {
				val = str.substr(pos);
				pos = str.size();
			} else {
				val = str.substr(pos, comma - pos);
				pos = comma + 1;
			}
		}
		MetaProperty* p = mc->findProperty(key);
		if (p && p->fromString) {
			p->fromString(obj, val);
		}
	}
	return true;
}

// ===== Type name =====
template<typename M>
std::string metaTypeName() {
	if constexpr (std::is_same_v<M, bool>) return "bool";
	else if constexpr (std::is_same_v<M, int>) return "int";
	else if constexpr (std::is_same_v<M, float>) return "float";
	else if constexpr (std::is_same_v<M, double>) return "double";
	else if constexpr (std::is_same_v<M, std::string>) return "string";
	else if constexpr (std::is_pointer_v<M>) return metaClassName<std::remove_pointer_t<M>>() + "*";
	else if constexpr (is_ref_v<M>) return "Ref<" + metaClassName<ref_inner_t<M>>() + ">";
	else return metaClassName<M>();
}

// ===== Value to string =====
template<typename M>
std::string metaValueToString(const M& val) {
	if constexpr (std::is_same_v<M, bool>) {
		return val ? "true" : "false";
	} else if constexpr (std::is_same_v<M, std::string>) {
		return val;
	} else if constexpr (std::is_floating_point_v<M>) {
		return std::to_string(val);
	} else if constexpr (std::is_integral_v<M>) {
		return std::to_string(val);
	} else if constexpr (std::is_pointer_v<M>) {
		using Pointee = std::remove_pointer_t<M>;
		if (!val) return "null";
		MetaClass* mc = MetaRegistry::instance()->findClass(metaClassName<Pointee>());
		if (mc) return metaSerializeObject(mc, (void*)val);
		return "null";
	} else if constexpr (is_ref_v<M>) {
		using Inner = ref_inner_t<M>;
		if (!val.get()) return "null";
		MetaClass* mc = MetaRegistry::instance()->findClass(metaClassName<Inner>());
		if (mc) return metaSerializeObject(mc, (void*)val.get());
		return "null";
	} else {
		MetaClass* mc = MetaRegistry::instance()->findClass(metaClassName<M>());
		if (mc) return metaSerializeObject(mc, (void*)&val);
		return "";
	}
}

// ===== String to value =====
template<typename M>
M metaStringToValue(const std::string& str) {
	if constexpr (std::is_same_v<M, bool>) {
		return str == "true" || str == "1";
	} else if constexpr (std::is_same_v<M, std::string>) {
		return str;
	} else if constexpr (std::is_same_v<M, float>) {
		return std::stof(str);
	} else if constexpr (std::is_same_v<M, double>) {
		return std::stod(str);
	} else if constexpr (std::is_same_v<M, int>) {
		return std::stoi(str);
	} else if constexpr (std::is_same_v<M, long long>) {
		return std::stoll(str);
	} else if constexpr (std::is_pointer_v<M>) {
		using Pointee = std::remove_pointer_t<M>;
		if (str == "null" || str.empty()) return nullptr;
		MetaClass* mc = MetaRegistry::instance()->findClass(metaClassName<Pointee>());
		if (mc) {
			Pointee* obj = new Pointee();
			metaDeserializeObject(mc, obj, str);
			return obj;
		}
		return nullptr;
	} else if constexpr (is_ref_v<M>) {
		using Inner = ref_inner_t<M>;
		if (str == "null" || str.empty()) return M(nullptr);
		MetaClass* mc = MetaRegistry::instance()->findClass(metaClassName<Inner>());
		if (mc) {
			Inner* obj = new Inner();
			metaDeserializeObject(mc, obj, str);
			return M(obj);
		}
		return M(nullptr);
	} else {
		M result{};
		MetaClass* mc = MetaRegistry::instance()->findClass(metaClassName<M>());
		if (mc) metaDeserializeObject(mc, &result, str);
		return result;
	}
}

// ===== Class registrar =====
template<typename T>
class MetaClassRegistrar {
public:
	using ClassType = T;

	std::string className;
	MetaRegistry* registry;

	MetaClassRegistrar(const std::string& name, MetaRegistry* reg)
		: className(name), registry(reg) {}

	template<typename M, typename C>
	MetaClassRegistrar& property(const std::string& name, M C::* memberPtr) {
		static_assert(std::is_base_of_v<C, T>, "C must be T or a base of T");
		auto getter = [memberPtr](void* obj) -> void* {
			return &(static_cast<T*>(obj)->*memberPtr);
		};
		auto setter = [memberPtr](void* obj, void* val) {
			static_cast<T*>(obj)->*memberPtr = *static_cast<M*>(val);
		};
		auto toStr = [memberPtr](void* obj) -> std::string {
			return metaValueToString(static_cast<T*>(obj)->*memberPtr);
		};
		auto fromStr = [memberPtr](void* obj, const std::string& str) {
			static_cast<T*>(obj)->*memberPtr = metaStringToValue<M>(str);
		};
		registry->registerProperty(className, name, metaTypeName<M>(), getter, setter);
		auto& mc = *registry->findClass(className);
		auto* p = mc.findProperty(name);
		if (p) {
			p->toString = toStr;
			p->fromString = fromStr;
			if constexpr (is_ref_v<M>) {
				using Inner = ref_inner_t<M>;
				p->refSetter = [memberPtr](void* obj, GcObj* val) {
					static_cast<T*>(obj)->*memberPtr.set_target(static_cast<Inner*>(val));
				};
			}
		}
		return *this;
	}

	MetaClassRegistrar& property(const std::string& name,
		std::function<void*(T*)> getterFn,
		std::function<void(T*, void*)> setterFn,
		const std::string& typeName = "") {
		auto getter = [getterFn](void* obj) -> void* {
			return getterFn((T*)obj);
		};
		auto setter = [setterFn](void* obj, void* val) {
			setterFn((T*)obj, val);
		};
		registry->registerProperty(className, name, typeName, getter, setter);
		return *this;
	}

	MetaClassRegistrar& getter(const std::string& name,
		std::function<void*(T*)> getterFn) {
		auto g = [getterFn](void* obj) -> void* {
			return getterFn((T*)obj);
		};
		registry->registerGetter(className, name, g);
		return *this;
	}

	MetaClassRegistrar& setter(const std::string& name,
		std::function<void(T*, void*)> setterFn) {
		auto s = [setterFn](void* obj, void* val) {
			setterFn((T*)obj, val);
		};
		registry->registerSetter(className, name, s);
		return *this;
	}
};
