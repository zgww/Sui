#include <stdio.h>

// #include "./NanovgEntry.h"

#include "../UrgcDll/urgc_api.h"
#include "Orc/Orc.h"
import * from "./Sui/Core/App.orc"
import * from "./Sui/Core/Window.orc"
import * from "./Sui/Core/View.orc"
import * from "./Sui/View/ViewBuilder.orc"
import * from "./Sui/View/ImageView.orc"
import * from "./Sui/View/TextView.orc"
import * from "./Sui/View/EditText.orc"
import * from "./Sui/View/Button.orc"
import * from "./Sui/Layout/LayoutLinear.orc"
import * from "./Sui/Layout/LayoutGrid.orc"
import * from "./Sui/Layout/RowWrap.orc"
import * from "./Sui/Layout/LayoutAlign.orc"
import * from "./Sui/Dialog/Toast.orc"
// import * from "./Orc/Thread.orc"
import * from "./Orc/String.orc"

 

// import * from "./Orc/Mutex.orc"
// import * from "./Orc/Math.orc"
// import * from "./Orc/List.orc"
// import * from "./Orc/Map.orc"
// import * from "./Orc/Path.orc"
// import * from "./Sui/Dialog/Toast.orc"
// import * from "./Sui/Core/Vec2.orc"
// import * from "./Sui/Core/Rect.orc"
// import * from "./Sui/Core/Radius.orc"
// import * from "./Sui/Core/Inset.orc"
// import * from "./Sui/Core/Global.orc"
// import * from "./Sui/Core/Event.orc"
// import * from "./Sui/Core/Emitter.orc"
// import * from "./Sui/Core/Edge.orc"
// import * from "./Sui/Core/Cursor.orc"
// import * from "./Sui/Core/Color.orc"
// import * from "./Sui/Core/Clipboard.orc"
// import * from "./Sui/Core/Border.orc"
// import * from "./Sui/Core/Screen.orc"
// import * from "./Sui/Core/Timer.orc"

extern void windowInit()
// extern void testWindow();


void initMain(){
    // urgc_start_process_thread();
}


int main(){
    if (1){
        printf("return \n")
        return 0;
    }
    initMain()
    windowInit();

    printf("app used0\n")
    App@ app = App_use()
    printf("app used\n")
    

    // testWindow()

    if 1 {
        Window@ win = new Window()
        // win.show();
        win. {
            LayoutLinear@ ll = new LayoutLinear()
            win.rootView = ll
            ll.{
                //layoutLinear(o, 0).{
                    o.width = 400
                    o.height = 400
                    o.backgroundColor = 0x93000000

                    mkDrawButton(o, 0).{
                        o.text = str("submit")
                        o.onClick = ^void(){
                            // Toast_make("click")
                            app.eachWindow(^void (Window *win){
                                win.rootView.printLayoutTimes(0)
                            })
                        }
                    }
                    mkView(o, 0).{
                        o.backgroundColor = 0xffff0000
                        o.width = 100
                        o.height = 100
                        o.margin.setAll(10)
                    }
                    mkEditText(o, 0).{
                        // o.setText(str("hi there buzi buzi"))
                        // o.width = 200
                        o.color = 0xff000000
                        o.height = 40
                        o.backgroundColor = 0x99999999
                    }
                    mkImageView(o, 0).{
                        o.setSrc(str("./asset/SpongeBob.png"))
                    }
                    mkTextView(o, 0).{
                        o.setText(str("hi there buzi buzi"))
                        // o.width = 200
                        // o.height = 40
                        o.backgroundColor = 0x13ff0000
                    }
                    layoutLinear(o, 0).{
                        o.direction.set("column")
                        o.backgroundColor = 0x33112233
                        mkView(o, 0).{
                            o.backgroundColor = 0xff00ff00
                            o.width = 80
                            o.height = 80
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 160
                            o.margin.setAll(10)
                        }
                    }
                    mkLayoutGrid(o, 0).{
                        o.width = 200
                        o.height = 200
                        o.backgroundColor = 0x33330000

                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                    }
                    mkRowWrap(o, 0).{
                        o.width = 200
                        o.height = 200
                        o.backgroundColor = 0x33009900

                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff0000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)
                        }
                    }
                    layoutAlign(o, 0).{
                        o.width = 200
                        o.height = 200
                        o.backgroundColor = 0x33009900

                        mkView(o, 0).{
                            o.backgroundColor = 0xfffff06f
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)

                            layoutAlignCell(o, 0).{
                                o.setBottomRight()
                            }
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff6000ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)

                            layoutAlignCell(o, 0).{
                                o.setBottomCenter()
                            }
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff00ffff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)

                            layoutAlignCell(o, 0).{
                                o.setCenter()
                            }
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xffff00ff
                            o.width = 60
                            o.height = 60
                            o.margin.setAll(10)

                            layoutAlignPositionCell(o, 0).{
                                o.left = nan
                                o.right = -60
                                o.top = 3
                            }
                        }
                        mkView(o, 0).{
                            o.backgroundColor = 0xff6f009f

                            layoutAlignPositionCell(o, 0).{
                                o.left = 10
                                o.right = 150
                                o.top = 30
                                o.bottom = 30
                            }
                        }
                    }
                //}
            }


            o.setTitle("orc机器人")
            o.setSize(840, 480)
            o.setPos(400, 200)
            o.show()
        }

    }



    app.runEventLoop()

    // testApp()
    // testWindow()

    // testVec2()
    // // testToast()
    // testRect()
    // testRadius();
    // testInset()
    // testGlobal()
    // testEvent()
    // testEmitter()
    // testEdge()
    // testCursor()
    // testColor()
    // testClipboard()
    // testBorder()
    // testScreen()
    // testTimer();


    // testWindow();

    // int ok = glewInit();
    // printf("test Main ctx:%d\n", ctx)
    // getchar();
    // printf("glewINit:%d\n", ok);
    printf("glewINit:%d\n", 1);
    getchar();
    return 0
}

