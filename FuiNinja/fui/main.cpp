#include <stdio.h>
#include "Urgc/UrgcIndex.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "Layout/LayoutLinear.h"
#include "View/TextView.h"

int mainxxx(){
    auto app = App_use();

    auto root = Ref(new LayoutLinear());
    RINS(root.get()){
        o.backgroundColor = 0xffefefef;
        o.aic().jcc();

        R(TextView){
            o.setText("欢迎");
            o.setFontSize(18);
            o.color = 0xff0000ff;
        } REND;

        R(TextView){
            o.setText("欢迎");
            o.setFontSize(18);
            o.color = 0xff0000ff;
        } REND;


        auto win = Ref(new Window());
        win->setRootView(root);
        win->setSize(400, 400);
        win->setTitle("hi");
        win->show();
        app->runEventLoop();
    }REND;
    printf("hi\n");
    // getchar();
    return 0;
}