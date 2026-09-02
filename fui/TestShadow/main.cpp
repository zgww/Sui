#include <Windows.h>
#include <string>
#include <format>
#include <stdio.h>
#include "Core/App.h"
#include "Core/Window.h"
#include "Layout/RowWrap.h"
#include "View/TextView.h"
#include "View/ScrollArea.h"

class ShadowView : public View {
public:
	virtual void draw_self(Canvas * canvas) override{
		canvas->shadowBlur( 10);
		canvas->shadowColor (0, 0, 0, 128);
		canvas->shadowOffset(5, 5);
		View::draw_self(canvas);
	}
};
void AppMain() {
	urgc.start_process_thread();
	auto app = App_use();
	auto root = Ref(new ScrollArea());
	RINS(root.get()) {

		o.useMaxWidthConstraint = true;
		o.backgroundColor = 0xffefefef;
		R(RowWrap) {

			for (int i = 0; i < 10; i++) {
				R(TextView, i) {
					o.setText(std::format("第[{}]项", i));
				} REND;
			}

			for (int i = 0; i < 1000; i++) {
				R(ShadowView, i) {
					o.backgroundColor = 0xff2d2d2d;
					o.width = 40;
					o.height = 40;
					o.margin.setAll(10);
				} REND;
			}
		} REND;

		auto win = Ref(new Window()); 
		win->setRootView(root);
		win->setSize(600, 400);
		win->moveToCenter();
		win->setTitle("标题");
		win->show();
	} REND;
	app->runEventLoop();
}

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {    
	//FreeConsole();//解除ide/vscode的控制台。否则AllocConsole无效
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	//printf("lpCmdLine:%s\n", lpCmdLine);

	std::string initialFile = lpCmdLine;
	AppMain();
	return 0;
}

int main(int argc, char* argv[]) {
	std::string initialFile;
	if (argc > 1) {
		initialFile = argv[1];
	}

	AppMain();
	return 0;
}
