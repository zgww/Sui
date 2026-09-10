#include "../fui/Core/Node.h"
#include "../fui/Core/ViewBase.h"
#include "../fui/Core/View.h"
#include "../fui/JsonSerialization/NodeTreeIO.h"
#include <rttr/registration>
#include <cstdio>

// ---- Node.cpp 依赖的 App_use()，测试桩（不会走到 invalidReact 路径） ----
class App;
App* App_use(); // 声明在 App.h；这里只给桩定义
App* App_use() { return nullptr; }

// ---- 测试用值类型 + 枚举 ----
struct TestRect { float x = 0, y = 0, w = 0, h = 0; };
enum class TestAlign { Left, Center, Right };

// ---- 测试用节点类链：TestButton -> TestMid -> Node ----
class TestMid : public Node {
public:
    std::string midName = "mid";
    int midInt = 7;
    virtual const char* getClassName() const override { return "TestMid"; }
};

class TestButton : public TestMid {
public:
    std::string label = "btn";
    float scale = 1.5f;
    int color = 0xff0000ff;
    bool enabled = true;
    void* rawPtr = nullptr;   // 指针成员：不应出现在 JSON
    float nanVal = NAN_F;     // NaN：不应出现在 JSON
    TestRect rect;
    TestAlign align = TestAlign::Center;
    virtual const char* getClassName() const override { return "TestButton"; }
};

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<TestRect>("TestRect")
        .constructor<>()(policy::ctor::as_object)
        .property("x", &TestRect::x)
        .property("y", &TestRect::y)
        .property("w", &TestRect::w)
        .property("h", &TestRect::h);

    registration::class_<TestAlign>("TestAlign")
        .enumeration<TestAlign>("TestAlign")(
            value("Left", TestAlign::Left),
            value("Center", TestAlign::Center),
            value("Right", TestAlign::Right));

    registration::class_<TestMid>("TestMid")
        .constructor<>()(policy::ctor::as_raw_ptr)
        .property("midName", &TestMid::midName)
        .property("midInt", &TestMid::midInt);

    registration::class_<TestButton>("TestButton")
        .constructor<>()(policy::ctor::as_raw_ptr)
        .property("label", &TestButton::label)
        .property("scale", &TestButton::scale)
        .property("color", &TestButton::color)
        .property("enabled", &TestButton::enabled)
        .property("rawPtr", &TestButton::rawPtr)
        .property("nanVal", &TestButton::nanVal)
        .property("rect", &TestButton::rect)
        .property("align", &TestButton::align);

    io::registerNodeClass<TestButton, TestMid>();
    io::registerNodeClass<TestMid, Node>();
}

int failures = 0;
#define CHECK(cond, msg) do { if (!(cond)) { printf("FAIL: %s\n", msg); failures++; } else { printf("ok  : %s\n", msg); } } while (0)

int main()
{
    // 1) 手工构造一棵树
    Ref<TestButton> root{ new TestButton() };
    root->name = "root";
    root->label = "rootBtn";
    root->scale = 2.0f;
    root->color = 0x11223344;
    root->rect = { 1, 2, 3, 4 };
    root->align = TestAlign::Right;
    root->midName = "rootMid";
    root->midInt = 42;

    Ref<TestButton> kid{ new TestButton() };
    kid->name = "kid";
    kid->label = "kidBtn";
    kid->enabled = false;
    root->appendChild(kid.get());

    // 2) 导出
    std::string json = io::nodeTreeToJson(root.get());
    printf("=== EXPORTED ===\n%s\n", json.c_str());

    CHECK(json.find("\"type\": \"TestButton\"") != std::string::npos, "导出包含 type");
    CHECK(json.find("\"label\": \"rootBtn\"") != std::string::npos, "导出包含具体类属性 label");
    CHECK(json.find("\"midName\": \"rootMid\"") != std::string::npos, "导出包含中间基类属性 midName");
    CHECK(json.find("\"name\": \"root\"") != std::string::npos, "导出包含 Node 属性 name");
    CHECK(json.find("\"rect\": {") != std::string::npos, "导出包含值对象属性 rect");
    CHECK(json.find("\"align\": \"Right\"") != std::string::npos, "导出枚举为字符串");
    CHECK(json.find("rawPtr") == std::string::npos, "指针成员被跳过");
    CHECK(json.find("nanVal") == std::string::npos, "NaN 属性被跳过");
    CHECK(json.find("\"children\": [") != std::string::npos, "导出包含子树");

    // 3) 导入 -> 再导出，应一致
    std::string err;
    Ref<Node> root2 = io::nodeTreeFromJson(json, &err);
    CHECK((bool)root2, "导入成功");
    if (!root2) { printf("IMPORT ERR: %s\n", err.c_str()); return 1; }

    std::string json2 = io::nodeTreeToJson(root2.get());
    printf("=== RE-EXPORTED ===\n%s\n", json2.c_str());
    CHECK(json == json2, "往返导出一致");

    // 4) 导入后属性值校验
    TestButton* rb = dynamic_cast<TestButton*>(root2.get());
    CHECK(rb != nullptr && rb->label == "rootBtn", "root.label");
    CHECK(rb && rb->scale == 2.0f, "root.scale");
    CHECK(rb && rb->color == 0x11223344, "root.color");
    CHECK(rb && rb->rect.x == 1 && rb->rect.w == 3, "root.rect");
    CHECK(rb && rb->align == TestAlign::Right, "root.align");
    CHECK(rb && rb->midName == "rootMid", "root.midName");
    CHECK(rb && rb->midInt == 42, "root.midInt");
    CHECK(rb && rb->name == "root", "root.name");
    CHECK(rb && root2->getChildrenCount() == 1, "子树数量");
    if (rb && root2->getChildrenCount() == 1)
    {
        TestButton* kb = dynamic_cast<TestButton*>(root2->getChild(0));
        CHECK(kb && kb->label == "kidBtn", "kid.label");
        CHECK(kb && kb->enabled == false, "kid.enabled");
    }

    // 5) 错误路径
    std::string err2;
    Ref<Node> bad1 = io::nodeTreeFromJson("{\"type\":\"NoSuchClass\"}", &err2);
    CHECK(!bad1 && err2.find("未知节点类型") != std::string::npos, "未知类型报错");
    std::string err3;
    Ref<Node> bad2 = io::nodeTreeFromJson("{\"label\":\"no type\"}", &err3);
    CHECK(!bad2 && err3.find("缺少 type") != std::string::npos, "缺少 type 报错");
    std::string err4;
    Ref<Node> bad3 = io::nodeTreeFromJson("{invalid json", &err4);
    CHECK(!bad3 && err4.find("JSON 解析失败") != std::string::npos, "JSON 语法错误报错");

    // 6) 未知 JSON 成员应被忽略、缺省属性保持默认
    std::string err5;
    Ref<Node> root3 = io::nodeTreeFromJson(
        "{\"type\":\"TestButton\",\"label\":\"x\",\"unknownKey\":123,\"children\":[]}", &err5);
    CHECK((bool)root3, "未知成员被忽略");
    TestButton* rb3 = dynamic_cast<TestButton*>(root3.get());
    CHECK(rb3 && rb3->label == "x", "部分属性可导入");
    CHECK(rb3 && rb3->scale == 1.5f, "缺省属性保持默认");

    printf("\n%s (%d failures)\n", failures == 0 ? "ALL PASSED" : "FAILED", failures);
    return failures == 0 ? 0 : 1;
}
