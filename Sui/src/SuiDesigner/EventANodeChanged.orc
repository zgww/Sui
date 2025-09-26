package SuiDesigner

import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "./ANode.orc"


class EventToEbus extends Event{
    void emitToEbus(){
        useEbus().emit(self)
    }
}

//项目文件变化
class EventANodeChanged extends EventToEbus{
    ANode@ anode
}

//项目文件变化
class EventANodeAttrChanged extends EventToEbus{
    ANode@ anode

    // //延后
    // void fireDebounce(){
    // }
}
