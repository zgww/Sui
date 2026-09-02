#include <Windows.h>
#include <string>
#include <format>
#include <stdio.h>
#include "Core/App.h"
#include "Core/Window.h"
#include "Layout/RowWrap.h"
#include "View/TextView.h"

void AppMain() {
	urgc.start_process_thread();
	auto app = App_use();
	auto root = Ref(new RowWrap());
	RINS(root.get()) {
		o.backgroundColor = 0xffefefef;

		for (int i = 0; i < 2000; i++) {
			R(TextView) {
				o.setText(std::format("第[{}]项", i));
			} REND;
		}

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
