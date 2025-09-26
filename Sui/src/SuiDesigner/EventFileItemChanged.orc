package SuiDesigner

import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "./FileItem.orc"
import * from "./EventANodeChanged.orc"



//项目文件变化
class EventFileItemChanged extends EventToEbus{
    FileItem@ fileItem

}