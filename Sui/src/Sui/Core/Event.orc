package SuiCore

#include <stdio.h>
import * from "../../Orc/String.orc"

class Event {
    String@ name = str("")

    // 1表示 停止传播, 2表示立即停止传播。 在emit时，如果检测到2，就会脱离emit
    int isStopPropagation = 0
    

    void stopPropagation(){
        self.isStopPropagation = 1
    }
    void stopImmediatePropagation(){
        self.isStopPropagation = 2
    }
}

void testEvent(){
    Event@ e = new Event()
    
    e.name = str("test") 
    printf("testEvent:%s\n", e.name.str)
    e.stopPropagation()
    printf("testEvent stopPropagation:%d\n", e.isStopPropagation)

}

