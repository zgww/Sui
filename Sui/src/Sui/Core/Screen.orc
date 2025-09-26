package SuiCore

#include <stdio.h>
import * from "./Vec2.orc"

//屏幕相关接口

//取得屏幕可用区域,不含任务栏
extern Vec2 Screen_get_usable_size()
//真正的屏幕大小
extern Vec2 Screen_get_size()


void testScreen(){
	Vec2 usableSize = Screen_get_usable_size()
	Vec2 size = Screen_get_size()
	printf("usable size:%f, %f; size:%f, %f\n", usableSize.x, usableSize.y, size.x, size.y)
}