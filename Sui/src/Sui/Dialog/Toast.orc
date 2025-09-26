package SuiDialog

import * from "./MessageDialog.orc"

void Toast_make(const char *label){
    MessageDialog_alert(label, "提示")
}

void testToast(){
    Toast_make("你好")
}
