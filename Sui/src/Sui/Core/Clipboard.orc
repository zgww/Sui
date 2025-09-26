package SuiCore

#include <stdio.h>

import * from "../../Orc/String.orc"



extern void clipboard_setText(const char *text)
extern String@ clipboard_getText()



void testClipboard(){
    String@ text = clipboard_getText()
    printf("clipboard:%s\n", text.str)
    clipboard_setText("hi");
    
    String@ text2 = clipboard_getText()
    printf("clipboard2??:%s\n", text2.str)
}