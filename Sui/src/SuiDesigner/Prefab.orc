package SuiDesigner


#include <stdio.h>

//预制体
import * from "../Json/Json.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "./ANode.orc"


class Prefab {
    String@ version = str("0.0.3")
    ANode@ root = null;

    String@ _path = str("")

    void fromJson(Json@ jo){
        self.version = jo.getString("version")

        Json@ rootJo = jo.get("root")
        ANode@ root =  new ANode()
        root.fromJson(rootJo)
        self.root = root
    }
    Json@ toJson(){
        Json@ jo = Json_mkObject()
        jo.putString("version", self.version)
        
        if self.root {
            Json@ rootJo = self.root.toJson()
            jo.put("root", rootJo)
        }
        return jo
    }

    Prefab@ loadByPathCstr(const char *path){
        Json@ jo = Json_parseByPathCstr(path)
        self.fromJson(jo)
        self._path.set(path)

        return self
    }
    bool save(){
        if self._path && self._path.notEmpty() {
            bool ok = self.saveTo(self._path.str)
            return ok
        }
        else {
            Toast_make("保存路径未确定")
        }
        return false
    }
    bool saveTo(const char *path){
        Json@ jo = self.toJson()
        String@ text = jo.dump()
        bool ok = Path_writeText(path, text.str)
        return ok
    }
}