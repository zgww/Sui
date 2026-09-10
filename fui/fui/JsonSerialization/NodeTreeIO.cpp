#include "NodeTreeIO.h"

#include "../Core/ViewBase.h"
#include "../Core/View.h"

#include <rttr/type>
#include <rttr/instance.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <map>
#include <vector>
#include <functional>

namespace io
{
namespace
{

constexpr int kMaxDepth = 256;

/////////////////////////////////////////////////////////////////////////////////////////
// 属性收集：直接使用动态类型（RTTR_ENABLE），get_properties() 自动含继承层属性
/////////////////////////////////////////////////////////////////////////////////////////

// 取节点 n 的动态 rttr 类型；宏未展开时回退到 getClassName()
rttr::type dynamicTypeOf(Node* n)
{
    rttr::type t = n->get_type();
    if (t.is_valid())
        return t;
    return rttr::type::get_by_name(n->getClassName());
}

// 收集节点 n 的全部可序列化属性（继承链合并；重名属性派生层优先）
std::vector<std::pair<std::string, rttr::property>> collectProps(Node* n)
{
    std::map<std::string, rttr::property> m;
    const rttr::type t = dynamicTypeOf(n);
    for (const rttr::property& p : t.get_properties())
    {
        if (p.get_metadata("NO_SERIALIZE"))
            continue;
        std::string pn = p.get_name();
        if (pn == "type" || pn == "children")
            continue; // 保留键
        if (m.find(pn) == m.end())
            m.emplace(pn, p);
    }
    return { m.begin(), m.end() };
}

/////////////////////////////////////////////////////////////////////////////////////////
// 导出：variant -> JSON 值
/////////////////////////////////////////////////////////////////////////////////////////

using JsonWriter = rapidjson::PrettyWriter<rapidjson::StringBuffer>;

// 预检：该 variant 是否可完整写出（递归检查对象属性）
bool canWrite(const rttr::variant& var, int depth)
{
    if (!var.is_valid() || depth > kMaxDepth)
        return false;
    const rttr::type t = var.get_type();
    if (t.is_pointer())
        return false; // void* / T* 无法序列化
    if (t == rttr::type::get<std::string>())
        return true;
    if (t.is_arithmetic())
    {
        if (t == rttr::type::get<float>() || t == rttr::type::get<double>())
            return std::isfinite(var.to_double());
        return true;
    }
    if (t.is_enumeration())
        return true;

    // 其余按“对象”处理：需要注册属性，且每个属性都可写
    const auto props = t.get_properties();
    if (props.empty())
        return false;
    rttr::variant tmp = var;
    rttr::instance inst(tmp);
    for (const rttr::property& p : props)
    {
        rttr::variant pv = p.get_value(inst);
        if (pv && !canWrite(pv, depth + 1))
            return false;
    }
    return true;
}

bool writeVariant(const rttr::variant& var, JsonWriter& w);

// 写对象属性：{ "k1": v1, "k2": v2, ... }
bool writeObjectProps(const rttr::instance& obj, JsonWriter& w)
{
    w.StartObject();
    for (const rttr::property& p : obj.get_type().get_properties())
    {
        if (p.get_metadata("NO_SERIALIZE"))
            continue;
        std::string pn = p.get_name();
        if (pn == "type" || pn == "children")
            continue;
        rttr::variant pv = p.get_value(obj);
        if (!pv || !canWrite(pv, 0))
            continue;
        w.Key(pn.c_str());
        writeVariant(pv, w);
    }
    w.EndObject();
    return true;
}

bool writeVariant(const rttr::variant& var, JsonWriter& w)
{
    if (!var.is_valid())
        return false;
    const rttr::type t = var.get_type();

    if (t.is_pointer())
        return false;

    if (t == rttr::type::get<std::string>())
    {
        w.String(var.to_string());
        return true;
    }

    if (t.is_arithmetic())
    {
        if (t == rttr::type::get<bool>())
            w.Bool(var.to_bool());
        else if (t == rttr::type::get<char>())
            w.Int(var.to_int8());
        else if (t == rttr::type::get<int8_t>())
            w.Int(var.to_int8());
        else if (t == rttr::type::get<int16_t>())
            w.Int(var.to_int16());
        else if (t == rttr::type::get<int32_t>())
            w.Int(var.to_int32());
        else if (t == rttr::type::get<int64_t>())
            w.Int64(var.to_int64());
        else if (t == rttr::type::get<uint8_t>())
            w.Uint(var.to_uint8());
        else if (t == rttr::type::get<uint16_t>())
            w.Uint(var.to_uint16());
        else if (t == rttr::type::get<uint32_t>())
            w.Uint(var.to_uint32());
        else if (t == rttr::type::get<uint64_t>())
            w.Uint64(var.to_uint64());
        else if (t == rttr::type::get<float>() || t == rttr::type::get<double>())
        {
            double d = var.to_double();
            if (!std::isfinite(d))
                return false; // NaN/Inf 不导出（默认值本身是 NaN）
            w.Double(d);
        }
        else
            return false;
        return true;
    }

    if (t.is_enumeration())
    {
        // 优先按枚举注册表输出名字（如 "Center"），失败再退回数值
        bool ok = false;
        uint64_t u = var.to_uint64(&ok);
        if (!ok)
            return false;
        rttr::enumeration e = t.get_enumeration();
        if (e.is_valid())
        {
            std::string name = e.value_to_name(rttr::argument(var));
            if (!name.empty())
            {
                w.String(name);
                return true;
            }
        }
        w.Uint64(u); // 兜底：名字映射不到时写数值
        return true;
    }

    // 其余按“对象”递归
    const auto props = t.get_properties();
    if (props.empty())
        return false;
    rttr::variant tmp = var;
    rttr::instance inst(tmp);
    return writeObjectProps(inst, w);
}

void writeNode(Node* n, JsonWriter& w, int depth)
{
    if (!n || depth > kMaxDepth)
        return;

    w.StartObject();
    w.Key("type");

    std::string typeName;
    const rttr::type dyn = dynamicTypeOf(n);
    if (dyn.is_valid())
        typeName = dyn.get_name();
    else
        typeName = n->getClassName();
    w.String(typeName.c_str());

    rttr::instance obj(*n);
    for (const auto& kv : collectProps(n))
    {
        rttr::variant pv = kv.second.get_value(obj);
        if (!pv || !canWrite(pv, 0))
            continue;
        w.Key(kv.first.c_str());
        writeVariant(pv, w);
    }

    const int cc = n->getOutChildrenCount();
    if (cc > 0)
    {
        w.Key("children");
        w.StartArray();
        for (int i = 0; i < cc; i++)
        {
            Node* kid = n->getOutChild(i);
            if (kid)
                writeNode(kid, w, depth + 1);
        }
        w.EndArray();
    }
    w.EndObject();
}

/////////////////////////////////////////////////////////////////////////////////////////
// 导入：JSON 值 -> 属性
/////////////////////////////////////////////////////////////////////////////////////////

void setErr(std::string* err, const std::string& msg)
{
    if (err)
    {
        if (!err->empty())
            *err += "; ";
        *err += msg;
    }
}

bool fromJsonIntoInstance(rttr::instance obj, const rapidjson::Value& json, std::string* err, int depth);

// 目标类型是否可以从 JSON 导入（指针/Ref/容器等一律跳过）
bool isImportableType(const rttr::type& t)
{
    if (!t.is_valid())
        return false;
    if (t.is_pointer() || t.is_wrapper())
        return false; // void* / T* / Ref<T> 等无法从 JSON 构建
    if (t.is_arithmetic() || t == rttr::type::get<std::string>() || t.is_enumeration())
        return true;
    // 其余按对象处理：需要默认构造器（无构造器 → 不可导入，如 std::vector / std::function）
    return t.get_constructor().is_valid();
}


// 32/64 位整数目标按位模式写入（避免 rttr 溢出转换的未定义行为，颜色等位语义保留）
bool setIntByBits(const rttr::property& prop, const rttr::instance& obj,
                  const rttr::type& vt, unsigned long long hv)
{
    if (vt == rttr::type::get<int>()) {
        auto intVal = static_cast<int>(static_cast<uint32_t>(hv));
        return prop.set_value(obj, rttr::variant(intVal));
    }
    if (vt == rttr::type::get<unsigned>())
        return prop.set_value(obj, rttr::variant(static_cast<unsigned>(static_cast<uint32_t>(hv))));
    if (vt == rttr::type::get<int32_t>())
        return prop.set_value(obj, rttr::variant(static_cast<int32_t>(static_cast<uint32_t>(hv))));
    if (vt == rttr::type::get<uint32_t>())
        return prop.set_value(obj, rttr::variant(static_cast<uint32_t>(hv)));
    if (vt == rttr::type::get<long long>())
        return prop.set_value(obj, rttr::variant(static_cast<long long>(hv)));
    if (vt == rttr::type::get<unsigned long long>())
        return prop.set_value(obj, rttr::variant(hv));
    return false;
}

// 把 JSON 值写入 prop（value 对象递归处理）
bool setPropValue(const rttr::property& prop, const rttr::instance& obj,
                  const rapidjson::Value& jv, std::string* err, int depth)
{
    const rttr::type vt = prop.get_type();
    if (!isImportableType(vt))
        return false;

    // 枚举：字符串按名字、数值按值查找名字后转换（不依赖 convert）
    if (vt.is_enumeration())
    {
        rttr::enumeration e = vt.get_enumeration();
        if (!e.is_valid())
            return false;
        rttr::variant enumVar;
        if (jv.IsString())
            enumVar = e.name_to_value(jv.GetString());
        else if (jv.IsNumber())
        {
            std::string name = e.value_to_name(rttr::argument(jv.GetUint64()));
            if (!name.empty())
                enumVar = e.name_to_value(name);
        }
        if (enumVar.is_valid())
        {
            prop.set_value(obj, enumVar);
            return true;
        }
        return false;
    }

    switch (jv.GetType())
    {
        case rapidjson::kStringType:
        {
            const char* s = jv.GetString();
            // 十六进制容错：数值属性接受 "0x1F" / "#1F2F3F"（CSS 风格）字符串
            if (vt.is_arithmetic() && s && s[0] != '\0')
            {
                const char* hex = nullptr;
                if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
                    hex = s + 2;
                else if (s[0] == '#')
                    hex = s + 1;
                if (hex && *hex != '\0')
                {
                    char* end = nullptr;
                    unsigned long long hv = std::strtoull(hex, &end, 16);
                    if (end && *end == '\0' && end != hex)
                    {
                        // 整数目标按位模式写入（0xff0000ff -> int 场景）
                        if (setIntByBits(prop, obj, vt, hv))
                            return true;
                        rttr::variant v{hv};
                        if (v.convert(vt))
                        {
                            prop.set_value(obj, v);
                            return true;
                        }
                    }
                    return false; // 带 0x/# 前缀但无法解析为整数
                }
            }
            rttr::variant v{std::string(s)};
            if (v.convert(vt))
            {
                prop.set_value(obj, v);
                return true;
            }
            return false;
        }
        case rapidjson::kTrueType:
        case rapidjson::kFalseType:
        {
            rttr::variant v(jv.GetBool());
            if (v.convert(vt))
            {
                prop.set_value(obj, v);
                return true;
            }
            return false;
        }
        case rapidjson::kNumberType:
        {
            rttr::variant v;
            if (jv.IsInt())
                v = jv.GetInt();
            else if (jv.IsUint())
                v = jv.GetUint();
            else if (jv.IsInt64())
                v = jv.GetInt64();
            else if (jv.IsUint64())
                v = jv.GetUint64();
            else
                v = jv.GetDouble();
            if (v.convert(vt))
            {
                prop.set_value(obj, v);
                return true;
            }
            // 溢出场景（如十进制 4278190335 -> int）：按位模式写入
            return setIntByBits(prop, obj, vt, jv.GetUint64());
        }
        case rapidjson::kObjectType:
        {
            rttr::constructor ctor = vt.get_constructor();
            if (!ctor.is_valid())
                return false;
            rttr::variant created = ctor.invoke();
            if (!created.is_valid())
                return false;
            if (fromJsonIntoInstance(created, jv, err, depth + 1))
            {
                prop.set_value(obj, created);
                return true;
            }
            return false;
        }
        default:
            return false;
    }
}

// 把 JSON 对象递归写入 obj 自身的注册属性（用于值类型对象，如 Vec2/Frame/Inset）
bool fromJsonIntoInstance(rttr::instance obj, const rapidjson::Value& json, std::string* err, int depth)
{
    if (depth > kMaxDepth)
        return false;
    if (!json.IsObject())
        return false;

    bool any = false;
    for (const rttr::property& p : obj.get_type().get_properties())
    {
        if (p.get_metadata("NO_SERIALIZE"))
            continue;
        std::string pn = p.get_name();
        if (pn == "type" || pn == "children")
            continue;
        auto it = json.FindMember(pn.c_str());
        if (it == json.MemberEnd())
            continue;
        if (setPropValue(p, obj, it->value, err, depth))
            any = true;
    }
    return any;
}

// 递归构建节点（父节点由调用方 appendChild）
Ref<Node> buildNode(const rapidjson::Value& v, std::string* err, int depth)
{
    if (depth > kMaxDepth)
    {
        setErr(err, "节点树过深");
        return Ref<Node>();
    }
    if (!v.IsObject())
    {
        setErr(err, "节点必须是 JSON 对象");
        return Ref<Node>();
    }

    auto itType = v.FindMember("type");
    if (itType == v.MemberEnd() || !itType->value.IsString())
    {
        setErr(err, "节点缺少 type");
        return Ref<Node>();
    }
    const std::string className = itType->value.GetString();

    rttr::type t = rttr::type::get_by_name(className.c_str());
    if (!t.is_valid())
    {
        setErr(err, "未知节点类型: " + className);
        return Ref<Node>();
    }
    // 仅允许 Node 派生类（含 Node 自身），防止把非节点类型当节点创建
    if (t != rttr::type::get<Node>() && !t.is_derived_from(rttr::type::get<Node>()))
    {
        setErr(err, "类型不是 Node 派生类: " + className);
        return Ref<Node>();
    }
    if (!t.get_constructor().is_valid())
    {
        setErr(err, "类型未注册默认构造器: " + className);
        return Ref<Node>();
    }

    rttr::variant created = t.create();
    if (!created.is_valid())
    {
        setErr(err, "创建节点失败: " + className);
        return Ref<Node>();
    }
    // 节点类按规范以 policy::ctor::as_raw_ptr 注册，create() 返回指针型 variant
    if (!created.get_type().is_pointer())
    {
        setErr(err, "节点类需以 policy::ctor::as_raw_ptr 注册: " + className);
        return Ref<Node>();
    }

    Node* node = static_cast<Node*>(created.get_value<void*>());
    if (!node)
    {
        setErr(err, "创建节点为空: " + className);
        return Ref<Node>();
    }
    Ref<Node> guard{ node }; // 挂入父节点前保持存活

    // 属性：动态类型全属性表（get_properties 含继承层）。
    // 回填必须使用 create() 返回的指针 variant 构造的 instance：
    // 静态中间基类实例写更深基类属性会失败，指针实例无此限制。
    rttr::instance obj(created);
    for (const rttr::property& p : t.get_properties())
    {
        if (p.get_metadata("NO_SERIALIZE"))
            continue;
        std::string pn = p.get_name();
        if (pn == "type" || pn == "children")
            continue;
        if (pn == "margin") {
            printf("margin\n");
        }
        auto it = v.FindMember(pn.c_str());
        if (it == v.MemberEnd())
            continue;
        setPropValue(p, obj, it->value, err, depth);
    }

    // 子节点
    auto itKids = v.FindMember("children");
    if (itKids != v.MemberEnd() && itKids->value.IsArray())
    {
        for (const auto& kidVal : itKids->value.GetArray())
        {
            Ref<Node> kid = buildNode(kidVal, err, depth + 1);
            if (kid)
                node->appendChild(kid.get());
        }
    }
    node->react();

    return guard;
}

} // namespace anonymous

/////////////////////////////////////////////////////////////////////////////////////////
// 公开接口
/////////////////////////////////////////////////////////////////////////////////////////

std::string nodeTreeToJson(Node* root)
{
    if (!root)
        return "{}";

    rapidjson::StringBuffer sb;
    JsonWriter writer(sb);
    writeNode(root, writer, 0);
    return sb.GetString();
}

Ref<Node> nodeTreeFromJson(const std::string& json, std::string* err)
{
    rapidjson::Document doc;
    if (doc.Parse(json.c_str()).HasParseError())
    {
        setErr(err, "JSON 解析失败");
        return Ref<Node>();
    }
    if (!doc.IsObject())
    {
        setErr(err, "根节点必须是 JSON 对象");
        return Ref<Node>();
    }
    return buildNode(doc, err, 0);
}

} // namespace io
