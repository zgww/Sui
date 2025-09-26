
package SuiDesigner

import * from "./Asset/AssetDirView.orc"
import * from "./Asset/AssetDirTreeView.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"

import * from "./Prefab.orc"
import * from "./FileItem.orc"
import * from "../Json/Json.orc"
import * from "./EventFileItemChanged.orc"
import * from "./EventANodeChanged.orc"
import * from "./ANode.orc"
import * from "./EditCtx.orc"
import * from "./SceneView.orc"
import * from "./SceneHierView.orc"
import * from "./Project.orc"
import * from "./ChessBgViewCallback.orc"

import type * from "../Sgl/Material.orc"
import type * from "../Sgl/DrawCtx.orc"
import type * from "../Sgl/SglSceneView.orc"



//创建prefab
void UiAction_createPrefab(FileItem@ parent){
    //确保parent是目录
    if parent && !parent.isDirectory{
        parent = parent.parent
    }

    if !parent {
        MessageDialog_alert("未指定父目录", "tip")
        return
    }



    MessageDialog_prompt("新建预制.prefab", "新建预制", ^void (String@ newName){
        String@ path = parent.path.clone().add("/").addString(newName)
        Prefab@ prefab = new Prefab()
        String@ text = prefab.toJson().dump()

        MessageDialog_alert(str("新建预制. 路径").add(path.str).str, "tip")

        if Path_writeText(path.str, text.str) {
            MessageDialog_alert(str("新建预制成功. 路径").add(path.str), "tip")

            parent.loadSubtree()

            new EventFileItemChanged().{
                o.fileItem = parent
                o.emitToEbus()
            }
        }
    })
}
//带有ui交互的
void UiAction_renameFileItem(FileItem@ fi){
    MessageDialog_prompt(fi.filename.str, "重命名", ^void (String@ newName){
        String@ newpath = Path_withBasename(fi.path.str, newName.str)
        Path_rename(fi.path.str, newpath.str)

        fi.filename = newName
        fi.updatePathByParnetPathAndSelfFilename_subtree()
        new EventFileItemChanged().{
            o.fileItem = fi
            o.emitToEbus()
        }
    })
}
void UiAction_createDirectory(FileItem@ parent){
    if true{
        // Toast_make("hi")
        Window@ win = new Window()
        win.{
            o.setTitle("hi")
            o.setSize(400, 400)
            o.show()
        }
        return
    }
    //确保parent是目录
    if parent && !parent.isDirectory{
        parent = parent.parent
    }


    MessageDialog_prompt("新建的目录", "新建目录", ^void (String@ newName){
        FileItem@ fi = new FileItem()
        fi.setPathByParentPathAndFilename(parent.path, newName)

        if Path_mkdirs(fi.path.str){
            fi.setPath(fi.path)//更新属性: isDirectory
            parent.appendChild(fi)

            Project_ins().dirFileItem.printTree(0)
            // MessageDialog_alert(str("新建目录成功").addString(fi.path).str, "tip")


            new EventFileItemChanged().{
                o.fileItem = fi
                o.emitToEbus()
            }
        }
    })
}
void UiAction_deleteDirectory(FileItem@ fi){
    if Path_removeDirs(fi.path.str){
        new EventFileItemChanged().{
            o.fileItem = fi.parent
            fi.removeSelf()
            o.emitToEbus()
        }
    }
    else {
        MessageDialog_alert("删除目录失败", "tip")
    }
}
void UiAction_deleteFile(FileItem@ fi){
    if !fi || !fi.parent {
        MessageDialog_alert("删除文件失败,未指定文件或者文件没有父目录", "tip")
        return
    }
    Toast_make(str("删除文件:").add(fi.path.str).str)
    if Path_remove(fi.path.str){
        new EventFileItemChanged().{
            o.fileItem = fi.parent
            fi.removeSelf()
            o.emitToEbus()
        }
    }
    else {
        MessageDialog_alert("删除文件失败", "tip")
    }
}
void UiAction_delete(FileItem@ fi){
    Toast_make(str("删除:").add(fi.path.str).add(", 是目录?").addi(fi.isDirectory).str)
    if fi.isDirectory{
        UiAction_deleteDirectory(fi)
    }
    else {
        UiAction_deleteFile(fi)
    }
}


void UiAction_deleteANode(ANode@ anode){
    if !anode.parent {
        MessageDialog_alert_error("无法删除根结点", "tip");
        return 
    }
    ANode@ parent = anode.parent
    if MessageDialog_confirm("确认删除", "tip"){
        anode.removeSelf()
        parent.updateSubTreeNodes()

        new EventANodeChanged().{
            o.anode = anode
            o.emitToEbus()
        }
    }
}
class ClipboardForANodes{
    List@ list = new List()
    // cut|copy
    String@ kind = str("cut")
}
static ClipboardForANodes@ useClipboardForANodes(){
    static ClipboardForANodes@ ins = null
    if !ins {
        ins = new ClipboardForANodes()
    }
    return ins
}
void UiAction_cutANodes(List@ anodes){
    ClipboardForANodes@ clipboard = useClipboardForANodes()
    clipboard.list = anodes
    clipboard.kind.set("cut")

    for int i = 0; i < anodes.size(); i++ {
        ANode@ anode = (ANode@)anodes.get(i)
        anode.removeSelf()
    }

    // anode.removeSelf()

    new EventANodeChanged().{
        // o.anode = anode
        o.emitToEbus()
    }
}

void UiAction_copyANodes(List@ anodes){
    ClipboardForANodes@ clipboard = useClipboardForANodes()
    clipboard.list = anodes
    clipboard.kind.set("copy")

    // anode.removeSelf()

    new EventANodeChanged().{
        // o.anode = anode
        o.emitToEbus()
    }
}
void UiAction_pasteANodes(ANode@ parent){
    ClipboardForANodes@ clipboard = useClipboardForANodes()

    if clipboard.list && clipboard.list.size() > 0 {
        if clipboard.kind.equals("cut"){
            for int i = 0; i < clipboard.list.size(); i++ {
                ANode@ anode = (ANode@)clipboard.list.get(i)
                parent.appendChild(anode)
            }
            parent.updateSubTreeNodes()
            clipboard.list.clear() //清空剪切板
        }
        else if clipboard.kind.equals("copy"){
            for int i = 0; i < clipboard.list.size(); i++ {
                ANode@ anode = (ANode@)clipboard.list.get(i)
                ANode@ newANode = anode.clone()
                parent.appendChild(newANode)
            }
            parent.updateSubTreeNodes()
        }
    }
    // clipboard.list = anodes
    // clipboard.kind.set("copy")

    // anode.removeSelf()

    new EventANodeChanged().{
        o.anode = parent
        o.emitToEbus()
    }
}


//带有ui交互的
void UiAction_renameANode(ANode@ anode){
    String@ name = anode.getAttrStringValueByName("name")
    
    MessageDialog_prompt(name.str, "重命名", ^void (String@ newName){
        Json@ strJo = Json_mkString(newName)
        anode.setAttr("name", strJo)

        new EventANodeAttrChanged().{
            o.anode = anode
            o.emitToEbus()
        }
    })
}
//定位视图
void UiAction_locateView(ANode@ anode){
    if !anode.node {
        Toast_make("node is null")
        return 
    }
    Node@ n = anode.node
    SceneView* sv = EditCtx_ins().sceneView
    ViewBase *v = n.getAncestorByClass(ViewBase)

    Rect svRect = sv.get_abs_rect()
    Vec2 vClientPos = v.localToWorld(0, 0)
    Vec2 svCenterPos = svRect.centerPos()
    Vec2 translate = svCenterPos.sub(vClientPos)
    //需要考虑缩放吗?
    sv.sceneTransform.translate(translate.x, translate.y, 0)
    sv.invalidDraw()
}
void UiAction_addView(ANode@ anode, String@ viewName){
    if !anode.node {
        Toast_make("node is null")
        return 
    }
    NodeRegisterInfo@ info = NodeLib_use().findByClassName(viewName.str);
    if !info {
        Toast_make("未找到节点类")
        return
    }

    new ANode().{
        o.tag = viewName
        anode.appendChild(o)
        
        o.updateSubTreeNodes()

        new EventANodeChanged().{
            o.anode = anode
            o.emitToEbus()
        }
    }

    
    // Toast_make(viewName.str)
    // NodeRegisterInfo@ info = NodeLib_use().findByClassName(viewName.str);
    // if !info {
    //     Toast_make("未找到节点类")
    //     return
    // }
    // Object@ obj = info.mk()
    // if obj instanceof Node{

    // }
    // else {
    //     Toast_make("不是节点类")
    // }
}
//保存场景
void UiAction_savePrefab(){
    EditCtx@  ctx = EditCtx_ins()
    if ctx.prefab {
        ctx.prefab.save()
    }
}
void UiAction_openFile(FileItem@ fi){
    // Toast_make("hi oepn")

    // 打开预制
    if fi.path.endsWith(".prefab.json") {
        EditCtx_ins().openPrefab(fi.path.str)
        new EventANodeChanged().{
            o.anode = EditCtx_ins().root
            o.emitToEbus()
        }
    }
}
void UiAction_closeCurrentPrefab(){
    EditCtx_ins().closeCurrentPrefab()
    new EventANodeChanged().{
        o.anode = EditCtx_ins().root
        o.emitToEbus()
    }
}
void UiAction_showImageInNewWindow(FileItem@ fi){
    Window@ win = new Window()
    win.{
        new LayoutAlign().{
            // o.direction.set("column")
            // o.alignItems.set("stretch")
            // o.justifyContent.set("center")
            // o.padding.setAll(8)
            win.setRootView(o)
            ChessBgViewCallback@ tmp= new ChessBgViewCallback()
            // TODO bug  这里生成的代码有误。。应该是urgc_set_field_class
            o.cb  = tmp
            // o.cb = new ChessBgViewCallback()
            // o.cb  = tmp

            mkImageView(o, 0).{
                // o.backgroundColor = 0x33ff0000
                o.setSrc(fi.path)
                // o.width = 200
                // o.height = 200
                o.setImageMode(Contain)

                layoutAlignPositionCell(o, 0).{
                    o.left = 10
                    o.top = 10
                    o.right = 10
                    o.bottom = 10
                }


            }
        }

        o.setTitle(str("图片").addString(fi.path).str)
        o.setSize(640, 480)
        o.moveToCenter()
        o.show()
    }
}

void UiAction_showFileInfoInNewWindow(FileItem@ fi){
    Window@ win = new Window()
    win.{
        new LayoutLinear().{
            o.direction.set("column")
            o.alignItems.set("start")
            o.padding.setAll(6)
            // o.justifyContent.set("center")
            // o.padding.setAll(8)
            win.setRootView(o)
            // ChessBgViewCallback@ tmp= new ChessBgViewCallback()
            // TODO bug  这里生成的代码有误。。应该是urgc_set_field_class
            // o.cb  = tmp
            // o.cb = new ChessBgViewCallback()
            // o.cb  = tmp

            mkTextView(o, 0).{
                String@ info = str("")
                // Path_m
                long long mtime = Path_mtimeMs(fi.path.str)
                String@ mtimeStr = Path_mtimeStr(fi.path.str)
                info.add("文件名：").addString(fi.filename).add("\n")
                info.add("修改时间：").addString(mtimeStr).add("\n")
                info.add("路径：").addString(fi.path).add("\n")

                String@ ext = Path_fullExt(fi.path.str)
                info.add("后缀：").addString(ext).add("\n")

                o.setText(info)

                layoutAlignPositionCell(o, 0).{
                    o.left = 10
                    o.top = 10
                    o.right = 10
                    o.bottom = 10
                }
            }
        }

        o.setTitle(str("文件属性").addString(fi.path).str)
        o.setSize(640, 480)
        o.moveToCenter()
        o.show()
    }
}
void UiAction_showFileTextInNewWindow(FileItem@ fi){
    Window@ win = new Window()
    win.{
        new LayoutAlign().{
            // o.direction.set("column")
            // o.alignItems.set("stretch")
            // o.padding.setAll(6)
            // o.justifyContent.set("center")
            // o.padding.setAll(8)
            win.setRootView(o)
            // ChessBgViewCallback@ tmp= new ChessBgViewCallback()
            // TODO bug  这里生成的代码有误。。应该是urgc_set_field_class
            // o.cb  = tmp
            // o.cb = new ChessBgViewCallback()
            // o.cb  = tmp

            mkScrollArea(o, 0).{
                // o.backgroundColor = 0x33ff0000
                layoutAlignPositionCell(o, 0).{
                    o.left = 10
                    o.top = 10
                    o.right = 10
                    o.bottom = 10
                }
                mkTextView(o, 0).{
                    String@ text = Path_readText(fi.path.str)
                    String@ newtext = text.replaceAll("\t", "    ")

                    // o.setText(text)
                    o.setText(newtext)
                    // o.setText(str("\tkspace jsdf24\t324"))
                    // o.backgroundColor = 0x33ff00ff

                }
            }
        }

        o.setTitle(str("文件属性").addString(fi.path).str)
        o.setSize(640, 480)
        o.moveToCenter()
        o.show()
    }
}
void UiAction_createMaterial(FileItem@ fi){
    // Toast_make(str("创建材质").addString(fi.filename).str)

    String@ basename = Path_basename(fi.path.str)
    String@ vsPath = Path_withExt(fi.path.str, ".vs")
    String@ fsPath = Path_withExt(fi.path.str, ".fs")

    if !Path_exists(vsPath.str){
        Toast_make(str(".vs文件不存在:").addString(vsPath).str)
        return;
    }
    if !Path_exists(fsPath.str){
        Toast_make(str(".fs文件不存在:").addString(fsPath).str)
        return;
    }


    MessageDialog_prompt("新建材质.matl.json", "新建预制", ^void (String@ newName){
        String@ matlPath = Path_withBasename(fi.path.str, newName.str)

        if Path_exists(matlPath.str){
            Toast_make(str("材质已存在").addString(matlPath).str)
            return;
        }
        // else {
            // Toast_make("材质可以创建")
        // }

        Material@ matl = new Material()
        matl.buildByShaderPathCstr(vsPath.str, fsPath.str)
        //matl在同目录下创建,要考虑的是vsPath是相对于matl的路径的.
        matl.vsPath = Path_withExt(basename.str, ".vs")
        matl.fsPath = Path_withExt(basename.str, ".fs")

        matl.saveTo(matlPath)
        Toast_make("材质创建成功")

        if fi.parent {
            fi.parent.loadSubtree()
        }

        new EventFileItemChanged().{
            o.fileItem = fi.parent
            o.emitToEbus()
        }
    })
}
//打开材质检视窗口
void UiAction_showMaterialInspectorWindow(FileItem@ fi){
    Material@ matl = new Material()
    matl.load(fi.path.str)
    new MaterialInsp().{
        o.showWindow(matl)
    }
}

void UiAction_previewCamera(DrawCtx* ctx, Node* camera){

    new Window().{
        Window* win = o
        
        // ImageView@ iv = new ImageView()
        // iv.{
        //     win.rootView = iv
        //     iv._img = loadImageByTex2d(tex)
        //     // iv.setSrc(str("../asset/SpongeBob.png"))
        // }

        new SglSceneView().{
            win.setRootView(o)

            o.scene = ctx.scene
            o.camera = camera
            o.buildDrawObj()
            // o.drawCtx.camera = camera
        }



        o.setTitle("纹理预览")
        o.setSize(640, 480)
        o.show()
    }

}