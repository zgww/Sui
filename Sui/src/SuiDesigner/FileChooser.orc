package SuiDesigner

#include <stdio.h>

import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/Core/Focus.orc"
import * from "../Sui/Core/App.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/RowWrap.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"

class FileChooser {
    List@ paths = new List()
    ^bool (String* path) cbFilter;
    ^void (String@ path) onChoose

    String@ dir = str(".")
    String@ search = str("")

    void fire_onChoose(String@ path){
        printf("FileChooser. onChoose:%s\n", path.str)
        if self.onChoose {
            self.onChoose(path)
        }
        // Toast_make(str("已选择：").addString(path).str)
    }

    void use_filterImage(){
        self.cbFilter = ^bool (String* path){
            if Path_isUsualImage(path.str){
                return true
            }
            return false
        }
    }

    void loadPaths(){
        List@ tmp = new List()
        Path_listSubtree_toList(self.dir.str, tmp)
        self.paths.clear()
        for int i = 0; i < tmp.size(); i++{
            String* path = (String*)tmp.get(i)
            printf("\tfilter path:%s\n", path.str);
            if self.cbFilter {
                if !self.cbFilter(path){
                    continue
                }
            }
            self.paths.add(path)
        }
        printf("total path count:%d\n", self.paths.size())
    }

    Window@ win = null

    void doSearch(){
        self.react()
    }

    bool matchSearch(String *path){
        if path.indexByteOf(self.search.str) != -1{
            return true
        }
        return false
    }

    void react(){
        self.win.rootView.{
            layoutLinear(o, 0).{
                o.margin.setVer(6)
                mkTextView(o, 0).{
                    o.setText(str("文件选择器"))
                }
                mkEditText(o, 0).{
                    if !insFocus().isFocus(o) {
                        o.setValue(self.search)
                    }
                    o.onValueChanged = ^void(EditText*et){
                        self.search = et.getValue()
                        printf("on CHanged:%s\n", self.search.str)
                        self.doSearch()
                    }

                    layoutLinearCell(o, 0)
                }
            }
            mkScrollArea(o, 0).{
                o.useMaxWidthConstraint = true
                o.useMinWidthConstraint = true
                layoutLinearCell(o, 0)

                mkRowWrap(o, 0).{
                    o.rowGap = 10
                    o.colGap = 10


                    for int i = 0; i < self.paths.size(); i++{
                        String@ path = (String@)self.paths.get(i)
                        if !self.matchSearch(path){
                            continue
                        }
                        String@ filename = Path_basename(path.str)
                        // mkTextView(o, 10000000+i).{
                        layoutLinear(o, 100000+i).{
                            o.direction.set("column")
                            o.alignItems.set("stretch")

                            o.cbOnEvent = ^ void (Event *e){
                                if e instanceof MouseEvent{
                                    MouseEvent* me = (MouseEvent*)e;
                                    if me.button == 1 && me.isClickInBubble(){
                                        // Toast_make(path.str)
                                        self.fire_onChoose(path)
                                    }
                                }
                            }

                            mkImageView(o, 10000000+i).{
                                o.width = 60
                                o.height = 60
                                o.setImageMode(Fill)
                                // o.setText_align(str("center"))
                                // o.backgroundColor = 0x1100ffff
                                // o.setText(str("item").addi(i))
                                // o.setText(filename)
                                o.setSrc(path)

                                o.cursor.set("pointer")

                                mkHoverViewEffect(o, 0).{
                                    o.hoverBackgroundColor = 0x2200ffff
                                    o.backgroundColor = 0x1100ffff
                                }
                            }
                            mkTextView(o, 0).{
                                o.setFont_size(10)
                                o.setText(filename)
                            }
                        }
                    }
                }
            }
        }
    }

    void showWindow(){

        new Window().{
            Window* win = o
            self.win = o

            new LayoutLinear().{
                o.direction.set("column")
                o.alignItems.set("stretch")
                // o.justifyContent.set("center")
                o.padding.setAll(8)

                win.setRootView(o)

            }
            self.react()

            o.setTitle("文件选择")
            o.setSize(300, 300)
            o.moveToCenter()
            o.show()
        }

    }

}