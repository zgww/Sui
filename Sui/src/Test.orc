#include <stdio.h>
// #include "./NanovgEntry.h"
#include <stdio.h>

// #include "UrgcDll/urgc_api.h"
#include "../UrgcDll/urgc_api.h"
#include "Orc/Orc.h"
// import * from "./Orc/Time.orc"
// import * from "./Orc/Thread.orc"
// import * from "./Orc/String.orc"


 
// import * from "./Orc/Mutex.orc"
// import * from "./Orc/Math.orc"
// import * from "./Orc/List.orc"
// import * from "./Orc/Map.orc"
// import * from "./Orc/Path.orc"
// import * from "./Sui/Dialog/Toast.orc"
// import * from "./Sui/Core/Vec2.orc"
// import * from "./Sui/Core/Rect.orc"
// import * from "./Sui/Core/Radius.orc"
// import * from "./Sui/Core/Inset.orc"
// import * from "./Sui/Core/Global.orc"
// import * from "./Sui/Core/Event.orc"
// import * from "./Sui/Core/Emitter.orc"
// import * from "./Sui/Core/Edge.orc"
// import * from "./Sui/Core/Cursor.orc"
// import * from "./Sui/Core/Color.orc"
// import * from "./Sui/Core/Clipboard.orc"
// import * from "./Sui/Core/Border.orc"
// import * from "./Sui/Core/Screen.orc"
// import * from "./Sui/Core/Timer.orc"

extern void windowInit()
extern void testWindow();


void initMain(){
    urgc_start_process_thread();
}

int main(){
    initMain()


    windowInit();
    testWindow()

    // testVec2()
    // // testToast()
    // testRect()
    // testRadius();
    // testInset()
    // testGlobal()
    // testEvent()
    // testEmitter()
    // testEdge()
    // testCursor()
    // testColor()
    // testClipboard()
    // testBorder()
    // testScreen()
    // testTimer();


    // testWindow();

    // int ok = glewInit();
    // printf("test Main ctx:%d\n", ctx)
    // getchar();
    // printf("glewINit:%d\n", ok);
    printf("glewINit:%d\n", 1);
    getchar();
    return 0
}
