#include <stdio.h>
#include "Urgc/UrgcIndex.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "Layout/LayoutLinear.h"
#include "Layout/RowWrap.h"
#include "View/TextView.h"

int main(){
    auto app = App_use();

    auto root = Ref(new RowWrap());
    RINS(root.get()){
        o.backgroundColor = 0xffefefef;
        // o.direction = "column";
        // o.aic().jcc();

        R(TextView){
            o.setText("欢3迎 j");
            o.setFontSize(18);
            o.color = 0xff0000ff;
        } REND;

        for (int i = 0; i < 2000; i++){
            R(TextView){
                o.setText("欢迎jj光影");
                o.setFontSize(14);
                o.color = 0xff0000ff;
            } REND;
        }


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