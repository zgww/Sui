
#include <stdio.h>
#include "../Orc/Orc.h"
#include "../../UrgcDll/urgc_api.h"

import * from "../Sui/View/Button.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/Core/App.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Window.orc"

int main(){
    urgc_start_process_thread();

    // App@ app = App_use()

    Window@ win = new Window()
    win.setTitle("TestMini")
    win.setSize(800, 600)
    win.show()

    App_use().runEventLoop()
}