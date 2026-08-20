#include <Windows.h>
#include "./Urgc/Urgc.h"
#include <stdio.h>

#include "Core/App.h"
#include "Core/Window.h"
#include "Core/View.h"
#include "Core/Canvas.h"
#include "Layout/LayoutLinear.h"
#include "Layout/LayoutAlign.h"
#include "Layout/LayoutGrid.h"
#include "View/TextView.h"
#include "View/ImageView.h"
#include "View/Button.h"
#include "View/ProgressView.h"
#include "View/Slider.h"
#include "View/Checkbox.h"
#include "View/Switch.h"
#include "View/Panel.h"
#include "View/ScrollArea.h"
#include "View/EditText.h"
#include "View/Select.h"
#include "View/TreeView.h"
#include "View/TableView.h"
#include "View/SplitterView.h"
#include "View/ColorPicker.h"
#include "Dialog/Toast.h"
#include "Dialog/FileDialog.h"
#include "Dialog/MessageDialog.h"
#include "Core/NodeLib.h"
#include "Core/Screen.h"
#include "Core/Clipboard.h"

int main() {
	SetConsoleOutputCP(65001);
	urgc.start_process_thread();

	App* app = App_use();

	Ref<Window> win{new Window()};
	win->initData();

	//Ref<ScrollArea> scroll{new ScrollArea()};
	//scroll->backgroundColor = 0xfff5f5f5;

	//Ref<LayoutLinear> root{new LayoutLinear()};
	//root->direction = "column";
	//root->alignItems = "stretch";
	//root->padding.setAll(16);
	//root->backgroundColor = 0xfff5f5f5;

	//{
	//	Ref<TextView> title{new TextView()};
	//	title->text = "fui Demo - Complete Controls";
	//	title->fontSize = 24;
	//	title->color = 0xff333333;
	//	title->padding.bottom = 12;
	//	root->appendChild(title);
	//}

	//{
	//	Ref<LayoutLinear> row{new LayoutLinear()};
	//	row->direction = "row";
	//	row->alignItems = "center";
	//	row->padding.bottom = 12;

	//	Ref<Button> btn{new Button()};
	//	btn->setLabel("Show Toast");
	//	btn->setNormalBg(0xff1677ff);
	//	btn->onClick = CLOSURE([=](MouseEvent* me) {
	//		showToast("Hello from Toast!", 2000);
	//	});

	//	Ref<Button> btnDialog{new Button()};
	//	btnDialog->setLabel("Message Dialog");
	//	btnDialog->setNormalBg(0xff52c41a);
	//	btnDialog->margin.left = 8;
	//	btnDialog->onClick = CLOSURE([=](MouseEvent* me) {
	//		bool ok = MessageDialog_confirm("Are you sure?", "Confirm");
	//		if (ok) {
	//			showToast("Confirmed!", 1500);
	//		}
	//	});

	//	Ref<Button> btnFile{new Button()};
	//	btnFile->setLabel("Open File");
	//	btnFile->setNormalBg(0xff722ed1);
	//	btnFile->margin.left = 8;
	//	btnFile->onClick = CLOSURE([=](MouseEvent* me) {
	//		std::string path = FileDialog_getFirstOpenFileName(".", "Select a file");
	//		if (!path.empty()) {
	//			showToast("Selected: " + path, 3000);
	//		}
	//	});

	//	row->appendChild(btn);
	//	row->appendChild(btnDialog);
	//	row->appendChild(btnFile);
	//	root->appendChild(row);
	//}

	//{
	//	Ref<LayoutLinear> row{new LayoutLinear()};
	//	row->direction = "row";
	//	row->alignItems = "center";
	//	row->padding.bottom = 12;

	//	Ref<Slider> sliderRef{new Slider()};
	//	sliderRef->setRatio(0.5f);
	//	sliderRef->onChanged = CLOSURE([=](float v) {
	//		printf("Slider value: %f\n", v);
	//	});

	//	Ref<Checkbox> cb{new Checkbox()};
	//	cb->margin.left = 16;
	//	cb->onChanged = CLOSURE([=](bool checked) {
	//		printf("Checkbox: %s\n", checked ? "checked" : "unchecked");
	//	});

	//	Ref<TextView> cbLabel{new TextView()};
	//	cbLabel->text = "Checkbox";
	//	cbLabel->fontSize = 14;
	//	cbLabel->color = 0xff333333;
	//	cbLabel->margin.left = 6;

	//	Ref<Switch> sw{new Switch()};
	//	sw->margin.left = 16;
	//	sw->onCheckedChanged = CLOSURE([=](Switch* s) {
	//		printf("Switch: %s\n", s->checked ? "on" : "off");
	//	});

	//	Ref<TextView> swLabel{new TextView()};
	//	swLabel->text = "Switch";
	//	swLabel->fontSize = 14;
	//	swLabel->color = 0xff333333;
	//	swLabel->margin.left = 6;

	//	row->appendChild(sliderRef);
	//	row->appendChild(cb);
	//	row->appendChild(cbLabel);
	//	row->appendChild(sw);
	//	row->appendChild(swLabel);
	//	root->appendChild(row);
	//}

	//{
	//	Ref<LayoutLinear> row{new LayoutLinear()};
	//	row->direction = "row";
	//	row->alignItems = "center";
	//	row->padding.bottom = 12;

	//	Ref<EditText> edit{new EditText()};
	//	edit->setValue("Type here...");
	//	edit->width = 200;
	//	edit->height = 28;

	//	Ref<ColorPicker> cp{new ColorPicker()};
	//	cp->margin.left = 16;

	//	row->appendChild(edit);
	//	row->appendChild(cp);
	//	root->appendChild(row);
	//}

	//{
	//	Ref<ProgressView> progress{new ProgressView()};
	//	progress->setValue(0.7f);
	//	progress->padding.bottom = 12;
	//	root->appendChild(progress);
	//}

	//{
	//	Ref<Panel> panel{new Panel()};
	//	panel->setTitle("TreeView & TableView Demo");
	//	panel->setOpen(true);

	//	Ref<LayoutLinear> panelContent{new LayoutLinear()};
	//	panelContent->direction = "row";
	//	panelContent->padding.setAll(8);
	//	panelContent->height = 200;

	//	Ref<TreeView> tree{new TreeView()};
	//	tree->state->getId = [](void* item) -> std::string {
	//		return std::to_string((int)(intptr_t)item);
	//	};
	//	tree->state->getItemChildren = [](void* item) -> std::vector<void*> {
	//		int id = (int)(intptr_t)item;
	//		if (id < 10) {
	//			std::vector<void*> kids;
	//			for (int i = 1; i <= 3; i++) {
	//				kids.push_back((void*)(intptr_t)(id * 10 + i));
	//			}
	//			return kids;
	//		}
	//		return {};
	//	};
	//	tree->state->roots = {
	//		(void*)(intptr_t)1,
	//		(void*)(intptr_t)2,
	//		(void*)(intptr_t)3
	//	};
	//	tree->state->setOpen((void*)(intptr_t)1, true);
	//	tree->reactItem = CLOSURE([=](Node* o, void* item, int deep) {
	//		TextView* tv = gocTextView(o, 0);
	//		if (tv) {
	//			tv->setText("Node " + std::to_string((int)(intptr_t)item));
	//			tv->fontSize = 13;
	//			tv->color = 0xff333333;
	//		}
	//	});
	//	tree->width = 250;
	//	tree->invalidReact();

	//	Ref<TableView> table{new TableView()};
	//	table->addColumn(80, "ID");
	//	table->addColumn(120, "Name");
	//	table->addColumn(100, "Status");
	//	table->rowCount = 5;
	//	table->rowHeight = 22;
	//	table->renderTd = CLOSURE([=](Node* o, int row, int col) {
	//		TextView* tv = gocTextView(o, 0);
	//		if (tv) {
	//			if (col == 0) tv->setText(std::to_string(row + 1));
	//			else if (col == 1) tv->setText("Item " + std::to_string(row + 1));
	//			else tv->setText(row % 2 == 0 ? "Active" : "Idle");
	//			tv->fontSize = 13;
	//			tv->color = 0xff333333;
	//		}
	//	});
	//	table->margin.left = 8;
	//	table->invalidReact();

	//	panelContent->appendChild(tree);
	//	panelContent->appendChild(table);
	//	panel->setBody(panelContent);
	//	root->appendChild(panel);
	//}

	//scroll->appendChild(root);
	//win->setRootView(scroll);
	auto white = Ref(new LayoutLinear());
	white->cbOnEvent = CLOSURE([](Event *event) {
		printf("event:%s\n", event->name.c_str());
		});
	white->backgroundColor = 0xffffeeee;

	RINS(white) {
		o->direction = "column";
		o->alignItems = "center";
		o->justifyContent = "center";

		R(TextView) {
			o->setText("你好啊");
		}REND;

		R(TextView) {
			o->setText("你好啊");
		}REND;

		R(LayoutLinear) {
			o->backgroundColor = 0x3300ff00;
			R(TextView) {
				o->setText("左边");
				o->setFontSize(34);
			}REND;

			R(TextView) {
				o->setText("右边");
			}REND;
		}REND;

		R(TextView) {
			o->setText("你好啊");
		}REND;

		R(TextView) {
			o->setText("你好啊");
		}REND;


		R(ImageView) {
			o->setSrc("asset/sample.png");
			o->setImageMode(ImageMode_WidthFix);
			o->width = 400;
		}REND;
	}REND;


	class TmpViewCb : public ViewCallback {
	public:

		virtual bool cbDrawSelf(View* div, Canvas* canvas) { 
			canvas->fillColorByInt32(0xff00ff00);
			canvas->beginPath();
			canvas->rect(100, 100, 200, 200);
			canvas->fill();
			return true;
		}
	};
	auto cb = Ref(new TmpViewCb());
	//white->cb = cb;
	win->setRootView(white);
	win->setTitle("fui - GUI Framework Demo中文");
	win->setSize(800, 600);
	win->moveToCenter();
	win->show();
	//FileDialog_getSaveFileName("./", "请选择保存路径");
	
	//SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);

	//mkTimerInterval(CLOSURE([]() {
	//	printf("定时器到达\n");
	//	}), 1000);


	//Vec2 a= Screen_get_usable_size();
	//Vec2 b = Screen_get_size();
	//printf("screen:%f,%f,%f,%f\n", 
	//	a.x, a.y, b.x, b.y
	//	);

	mkTimerTimeout(CLOSURE([]() {
		printf("定时器到达\n");
		}), 1000);
	win->onClosed = CLOSURE([](Window* win) {
		printf("window 关闭:%s。 剪贴板:%s\n", win->getTitle().c_str(),
			Clipboard_getText().c_str());
		Clipboard_setText("你好啊");
		});
	app->runEventLoop();

	return 0;
}
