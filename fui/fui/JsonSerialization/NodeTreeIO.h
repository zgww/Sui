#pragma once
// NodeTreeIO.h — fui 节点树 <-> JSON（RTTR_ENABLE 继承注册版）
//
// 依赖：节点类已通过 RTTR_ENABLE(直接基类) 声明继承链，并完成 rttr 注册
//   （构造函数 policy::ctor::as_raw_ptr + public 成员属性，参见 Core/View.cpp 等）。
//
// 关键机制（相对旧版 registerNodeClass 适配表方案的简化）：
//   - rttr 的 type::get_properties() 自动包含继承层属性，且 RTTR_ENABLE 提供的
//     apply_offset 支持跨层级实例读写 —— 无需任何适配登记表；
//   - 导出：n->get_type() 取动态类型（RTTR_ENABLE 注入的虚函数），instance(*n) 读取；
//   - 导入：按 "type" 注册名 create()，用 create() 返回的指针 variant 构造 instance 回填
//     （静态中间基类实例写更深基类属性会失败，指针实例无此限制）。
//
// JSON 格式（与 io 示例的扁平风格一致）：
//   {
//     "type": "Button",            // 节点 rttr 注册名（get_type().get_name()）
//     ...其余成员为继承链上的注册属性...,
//     "children": [ { ... }, ... ] // 子树
//   }
//
// 约定：
//   - children 是 Ref<GcList<Node>>，按约定不注册属性，这里手动递归序列化；
//   - Ref / GcList / GcMap / std::function / 指针成员不注册，自然被跳过；
//   - 值类型属性（Vec2/Frame/Inset...）按对象递归；枚举按名称字符串；
//   - NaN/Inf 的 float/double 属性不导出（默认值本身是 NaN，导入后保持默认）。
//
// 典型用法：
//   std::string json = io::nodeTreeToJson(rootNode);
//   Ref<Node> root = io::nodeTreeFromJson(json, &err);
//   someParent->appendChild(root.get());   // 接入现有树，由 GcList 持有
//
#include <string>
#include "../Core/Node.h"

namespace io
{

// 把以 root 为根的节点树导出为 JSON；root 为空时返回 "{}"
std::string nodeTreeToJson(Node* root);

// 从 JSON 生成节点树，返回根节点（未挂载，调用方负责接入现有树或持有返回的 Ref）；
// 失败返回空 Ref，err（可选）接收错误信息
Ref<Node> nodeTreeFromJson(const std::string& json, std::string* err = nullptr);

} // namespace io
