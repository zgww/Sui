package SuiDialog

#include <stdio.h>

import * from "../../Orc/String.orc"
import * from "../Core/Window.orc"
import * from "../Core/App.orc"
import * from "../View/EditText.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../View/Button.orc"

/// 布局上下文
extern void MessageDialog_alert(const char * content, const char *title)
extern void MessageDialog_alert_error(const char * content, const char *title)
extern void MessageDialog_alert_warn(const char * content, const char *title)
// 确认
extern bool MessageDialog_confirm(const char *content, const char *title)


void MessageDialog_prompt(const char *value, const char *title, ^void (String@ newValue) onNewValue){
    Window@ win = new Window()
    win.{
        new LayoutLinear().{
            o.direction.set("column")
            o.alignItems.set("stretch")
            o.justifyContent.set("center")
            o.padding.setAll(8)
            o.backgroundColor = 0xffffffff

            win.setRootView(o)
        }


        win.rootView .{
            EditText@ editText = null
            mkEditText(o, 0).{
                editText = o
                o.setValue(str(value))
            }
            layoutLinear(o, 0).{
                o.justifyContent.set("center")
                o.margin.setVer(16)
                mkDrawButton(o, 0).{
                    o.text = str("确认")
                    o.onClick = ^void (){
                        if onNewValue {
                            String@ nv = editText.getValue()
                            // printf("editText value:%s\n", nv.str)
                            onNewValue(editText.getValue())
                            win.close()
                        }
                        // MessageDialog_alert("ok", "tip")
                    }
                }
                mkDrawButton(o, 0).{
                    o.text = str("取消")
                    o.onClick = ^void(){
                        // MessageDialog_alert("cancel", "tip")
                        win.close()
                    }
                }
            }

        }
        o.setTitle(title)
        o.setSize(300, 140)
        o.moveToCenter()
        o.show()
    }
}

void testMessageDialog(){
    // MessageDialog_alert("hi", "title")
    // MessageDialog_alert_error("hi error", "title")
    // MessageDialog_alert_warn("hi warn", "title")

    MessageDialog_prompt("苍天已死，黄天当立", "请输入", ^void(String@ nv){
        printf("new value:%s\n", nv.str)
        MessageDialog_alert(str("新值：").addString(nv).str, "tip")
    })
    App_use().runEventLoop()

}

//  void confirm(
// 	Ref<Closure<void (bool)>> onConfirm,
// 	string content, string title="提示");
///API_SYNC$

//  void input(
// 	Ref<Closure<void (string)>> onOk,
// 	string label, 
// 	string title="", //default is label
// 	string value=""
// );
