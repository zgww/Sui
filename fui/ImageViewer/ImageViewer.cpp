#include <Windows.h>
#include <string>
#include <stdio.h>
#include "Naga/Utf8Util.h"

import ImageViewerApp;

void AppMain() {

}

int wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR      lpCmdLine,
	int       nShowCmd
) {    
	FreeConsole();//解除ide/vscode的控制台。否则AllocConsole无效
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	int argc = 0;
	auto newArgs = CommandLineToArgvW(lpCmdLine, &argc);
	std::string initialFile;
	//initialFile = "F:\\ws\\Sui\\fui\\fui\\x64\\Release\\asset\\sample.png";
	if (argc > 0) {
		initialFile = Utf8Util::toutf8(newArgs[0]);
	}
	LocalFree(newArgs);
	printf("WinMainW lpCmdLine2:%s. nShowCmd:%d; argc:%d \n", initialFile.c_str(), nShowCmd, argc);
	runImageViewer(initialFile);
	return 0;
}

int main(int argc, char* argv[]) {
	std::string initialFile = "F:\\ws\\Sui\\fui\\fui\\x64\\Release\\asset\\sample.png";
	if (argc > 1) {
		initialFile = argv[1];
	}

	runImageViewer(initialFile);
	return 0;
}
