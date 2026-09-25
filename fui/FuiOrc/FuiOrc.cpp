// FuiOrc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "Core/App.h"
#include "Core/Window.h"
#include "Layout/LayoutLinear.h"
#include "View/Button.h"
#include "View/TextView.h"
#include <Windows.h>
#include "User_orc.h"



void reactRoot(LayoutLinear *root, User *user) {

    RINS(root) {
        o.backgroundColor = 0xffefefef;
        o.aic().jcc().column();

        RN(LayoutLinear) {
            o.row().aic().jcc();

            RN(Button) {
                o.setLabel("减");
                o.onClick = CLOSURE([=](MouseEvent* ev) {
                    printf("点击\n");
                    user->age--;
                    reactRoot(root, user);
                    });
            } REND;

            RN(TextView) {
                o.setText(std::format("用户年龄：{}", user->age));
            } REND;

            RN(Button) {
                o.setLabel("加");
                o.onClick = CLOSURE([=](MouseEvent* ev) {
                    printf("点击\n");
                    user->age++;
                    reactRoot(root, user);
                    });
            } REND;

            RN(Button) {
                o.setLabel("说话啊");
                o.onClick = CLOSURE([=](MouseEvent* ev) {
                    user->say(user, "你好啊。");
                    });
            } REND;

            RN(Button) {
                o.setLabel("创建新user");
                o.onClick = CLOSURE([=](MouseEvent* ev) {

                    OrcRef<User> user;
                    User_new(&user);
                    user->say(user, "这是新的user1");
                    });
            } REND;
        } REND;

    } REND;
}

int main()
{
    SetConsoleOutputCP(65001);
    urgc.start_process_thread();


    
    std::cout << "Hello World!\n";
    auto app = App_use();

    auto win = Ref(new Window());

    auto root = Ref(new LayoutLinear());
    
    OrcRef<User> user;
    User_new(&user);
    reactRoot(root.get(), user.get());

    

    win->setRootView(root);
    win->setTitle("测试fui里使用orc");
    win->setSize(400, 400);
    win->moveToCenter();
    win->show();
    app->runEventLoop();
}
