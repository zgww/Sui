package HoroEditor

import * from "./HoroEditCtx.orc"
import * from "./HoroEditor.orc"


void UiAct_savePrefab(HoroEditor* editor){
    HoroEditCtx@  ctx = editor.editCtx
    if ctx.prefab {
        ctx.prefab.save()
    }
}