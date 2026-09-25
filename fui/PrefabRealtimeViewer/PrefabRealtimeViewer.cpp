
#include "PrefabRealtimeViewerApp.h"


#include <Windows.h>
#include <string>
#include <stdio.h>


class Tmp {
public:
};

void AppMain() {
}

int wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR      lpCmdLine,
	int       nShowCmd
) {
	FreeConsole();
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	runPrefabRealtimeViewer();
	return 0;
}

int main(int argc, char* argv[]) {
	runPrefabRealtimeViewer();
	return 0;
}
