参考F:\ws\Sui\Sui\src\Sui 的实现。

将GUI实现搬到此项目。


要求保留继承结构：
View extends ViewBase extends Node extends Emitter

每个类自己单独一个文件。


绘图库使用nanovg,
窗口使用原生窗口。

目录结构:
Core
	App
	Bezier
	Border
	BoxShadow
	Canvas
	Clipboard
	Color
	Cursor
	Edge
	Emitter
	Euler
	Event
	Focus
	Fps
	Frame
	Frustum
	Keyboard
	KeyEvent
	LayoutCell
	Line3
	Mat2d
	Mat3
	Mouse
	MouseEvent
	Node
	NodeLib
	Plane
	Quat
	Quaternion
	Radius
	Rect
	Screen
	Spherical
	Timer
	TimerNode
	Triangle
	Vec2
	Vec3
	Vec4
	View
	ViewBase
	Window
Dialog
	FileDialog
	MessageDialog
	Toast
Layout
	LayoutAlign
	LayoutGrid
	LayoutLinear
	RowWrap
View
	Button
	Checkbox
	ColorPalete
	ColorPicker
	DockLayout
	Drag
	EditText
	HoverViewEffect
	ImageManager
	ImageView
	Menu
	MenuNative
	Panel
	ProgressView
	ScrollArea
	Select
	Slider
	SplitterView
	Switch
	SystemTrayIcon
	TableView
	TextView
	TreeView
Meta
	MetaProperty
	MetaClass
	MetaRegistry
	MetaRegistrar
	
需要特别注意， 内存管理使用的是URGC.  主要使用Ref这个类。 要特别注意Ref类是怎么用在局部变量上的，是怎么用在成员变量上的。
在局部变量使用Ref:
Ref<User> user{new User()};

在成员变量上使用Ref:
class Role: public GcObj{
};
class User : public GcObj{
public:
	int age = 10;
	Ref<Role> role{this, new Role()};
};

还有闭包的使用， 如果闭包内有用到ref,需要这样使用：
Ref<User> user{new User()};
auto closure = CLOSURE([=](){
	printf("user:%d\n", user->age);
});
closure->invoke();

参考以下例子：
```c++


class User : public GcObj {
public:
	int age= 10;
	~User() {
		printf("~User\n");
	}
};
Ref<Closure<void ()>> test() {
	Ref<User> user{ new User() };
	auto clo = CLOSURE([=]() {
		printf("age:%d\n", user->age);
		
		});
	clo->invoke();
	return clo;
}
void test2() {
	auto clo = test();
	getchar();
	clo->invoke();
}
int main() {
	SetConsoleOutputCP(65001);
	urgc.start_process_thread();
	test2();
	printf("hi\n");
	getchar();
	getchar();
	return 0;
}

```