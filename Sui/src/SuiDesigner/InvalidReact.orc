package SuiDesigner

#include "../Orc/Orc.h"
#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/View/DockLayout.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/Core/Timer.orc"
import * from "./ChessBgViewCallback.orc"
import * from "./Theme.orc"

class InvalidReact{

    bool _reactDirty = false
    ^void () react
    Object @target

    String@ reactName = str("react")

    InvalidReact* setReactName(const char *name){
        self.reactName.set(name)
        return self
    }


    void invalid(){
        if self._reactDirty{
            return
        }
        self._reactDirty = true
        requestAnimationFrame(^bool(){
            self._reactDirty = false
            // printf("do invalid\n")
            if self.react {
                self.react()
            }
            else if self.target {
                //通过反射调用
                void (**pReact)(Object *obj);
                OrcMetaField *mf = orc_getMetaFieldByObject(self.target, self.reactName.str)
                if mf {
                    pReact = OrcMetaField_getPtr(mf, self.target);
                    if *pReact{
                        (*pReact)(self.target);
                    }
                }
            }
            return true
        })
    }
}

InvalidReact@ mkInvalidReact(Object @target){
    InvalidReact@ invalidReact  =new InvalidReact()
    invalidReact.target = target
    return invalidReact
}