package SuiCore

#include <stdio.h>

// import * from "./Node.orc"
import * from "../../Orc/String.orc"

/// 布局上下文
class Cursor{

	extern void init()

	bool setCursor(const char * cursor){
        // 锁住了，无法设置
        if (self.isLocked){
            return false
        }
        self.cursor = str(cursor)
        self._updateCursor()
        return true
    }

	void setIsLocked(bool v){
        self.isLocked = v
    }
	extern void _updateCursor() 

	//锁住使用指定的cursor;拖拽时，不希望cursor改变,可以设置lock_cusor
    bool isLocked = false
    // arrow|pointer|sizewe|sizens|sizeall
	String@ cursor

}

static Cursor @cursor = NULL;
Cursor@ Cursor_ins(){
    if (cursor == NULL){
        cursor = new Cursor();
    }
    return cursor;
}
void testCursor(){
    Cursor@ tmp = Cursor_ins()
    tmp.setCursor("sizeall")
    printf("test cursor\n")
}