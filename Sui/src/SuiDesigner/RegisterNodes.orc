package SuiDesigner
#include <stdio.h>

import * from "./Serial/BiJson.orc"

import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/View.orc"

import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/TableView.orc"
import * from "../Sui/View/Switch.orc" 
import * from "../Sui/View/Slider.orc"
import * from "../Sui/View/Select.orc"
import * from "../Sui/View/Panel.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/ProgressView.orc" 
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"

import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutGrid.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/Layout/RowWrap.orc"
import * from "../Sui/Core/NodeLib.orc"

import * from "../Sgl/Scene.orc"
import * from "../Sgl/Obj3d.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/Camera.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "../Sgl/Light.orc"
import * from "../Sgl/PointLight.orc"
import * from "../Sgl/DirLight.orc"
import * from "../Sgl/SpotLight.orc"
import * from "../Sgl/ModelLoader.orc"


void registerNodes(){
    // BiJson_registerClass(ViewBase)
    // BiJson_registerClass(View)

    // BiJson_registerClass(ImageView)
    // BiJson_registerClass(HoverViewEffect)
    // BiJson_registerClass(TextView)
    // BiJson_registerClass(TreeView)
    // BiJson_registerClass(TableView)
    // BiJson_registerClass(Switch)
    // BiJson_registerClass(Select)
    // BiJson_registerClass(Panel)
    // BiJson_registerClass(EditText)
    // BiJson_registerClass(ProgressView)
    // BiJson_registerClass(ScrollArea)

    // BiJson_registerClass(Button)
    // BiJson_registerClass(DrawButton)
    // BiJson_registerClass(MenuButton)

    // BiJson_registerClass(LayoutLinear)
    // BiJson_registerClass(LayoutGrid)
    // BiJson_registerClass(LayoutAlign)
    // BiJson_registerClass(RowWrap)

    NodeLib@ lib = NodeLib_use()

    lib.registerClass(ViewBase)
    lib.registerClass(View)

    lib.registerClass(ImageView)
    lib.registerClass(HoverViewEffect)
    lib.registerClass(TextView)
    lib.registerClass(TreeView)
    lib.registerClass(TableView)
    lib.registerClass(Switch)
    lib.registerClass(Select)
    lib.registerClass(Panel)
    lib.registerClass(EditText)
    lib.registerClass(ProgressView)
    lib.registerClass(ScrollArea)

    lib.registerClass(Button)
    lib.registerClass(DrawButton)
    lib.registerClass(MenuButton)

    lib.registerClass(LayoutLinear)
    lib.registerClass(LayoutLinearCell)
    lib.registerClass(LayoutGrid)
    lib.registerClass(LayoutGridCell)
    lib.registerClass(LayoutAlign)
    lib.registerClass(LayoutAlignCell)
    lib.registerClass(RowWrap)

    lib.registerClass(Scene)
    lib.registerClass(Obj3d)
    lib.registerClass(Mesh)
    lib.registerClass(Camera)
    lib.registerClass(PerspectiveCamera)
    lib.registerClass(Light)
    lib.registerClass(PointLight)
    lib.registerClass(DirLight)
    lib.registerClass(SpotLight)
    lib.registerClass(ModelLoader)
}


