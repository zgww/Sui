#include <Windows.h>
#include <string>
#include <stdio.h>

import ImageViewerApp;

void AppMain() {

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
	runImageViewer(initialFile);
	return 0;
}

int main(int argc, char* argv[]) {
	std::string initialFile;
	if (argc > 1) {
		initialFile = argv[1];
	}

	runImageViewer(initialFile);
	return 0;
}
