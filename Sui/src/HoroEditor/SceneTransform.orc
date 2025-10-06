package HoroEditor

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"


#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Mat2d.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Canvas.orc"

import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Dialog/Toast.orc"

import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/MenuNative.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../Sui/View/ViewBuilder.orc"
import * from "../SuiDesigner/Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Json/Json.orc"
import * from "../SuiDesigner/Asset/AssetDirView.orc"
import * from "../SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "../SuiDesigner/RegisterNodes.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "../SuiDesigner/UiAction.orc"
import * from "../SuiDesigner/ANode.orc"
import * from "../SuiDesigner/Gizmo.orc"
import * from "../SuiDesigner/EditCtx.orc"
import * from "../SuiDesigner/EventANodeChanged.orc"
import * from "../SuiDesigner/EventFileItemChanged.orc"
import * from "./Horo2dSceneView.orc"



class SceneTransform {
    Vec3 _translate;
    float _scale = 1;
    Mat2d mat = mkMat2d()//最终生成的矩阵
    void setScale(float s){
        self._scale = s
        self.updateMat()
    }
    void updateMat(){
        self.mat.identity()
        self.mat.translate(
            self._translate.x,
            self._translate.y,
            self._translate.z,
        )
        self.mat.scale(
            self._scale,
            self._scale,
            self._scale,
        )
    }
    void translate(float x, float y, float z){
        self._translate = self._translate.add3f(x, y, z)
        self.updateMat()
    }
    void setTranslate(float x, float y, float z){
        self._translate.set(x, y, z)
        self.updateMat()
    }
    void identity(){
        self._translate.set(0, 0, 0)
        self._scale = 1
        self.updateMat()
    }
    void performScaleByWheelEventAndSceneView(
        WheelEvent* we,
        Horo2dSceneView* v
    ){
        Vec2 viewPos = v.worldToLocal(we.clientX, we.clientY)
        Mat2d invMat = self.mat.inverseNew()
        Vec3 scenePos = invMat.transformPoint(viewPos.x, viewPos.y, 0)

        // float s = self._scale
        // float nextScale = maxFloat(0.01, self._scale + (we.deltaY > 0 ? 1 : -1) * 0.1)
        // int idx = v.degree.levelOptions.indexOf(v.degree.curOption)
        // int nextIdx = minInt(maxInt(0, idx + (we.deltaY > 0 ? 1 : -1)), v.degree.levelOpotions.size() - 1)
        // // DrawDegreeItem@ opt = v.degree.findAndUpdateCurOption(nextScale)
        // self.setScale(opt.value)
        DrawDegreeItem@ opt = v.degree.findAndReturnOffset(self._scale, we.deltaY > 0 ? 1 : -1)
        v.degree.curOption = opt
        v.degree.curScale = opt.value
        self.setScale(opt.value)


        Vec3 newViewPos = self.mat.transformPoint(scenePos.x, scenePos.y, 0)
        printf("scale. client:%d,%d, viewPos:%f,%f, scenePos:%f,%f,newViewPos:%f,%f, delta:%f,%f\n",
            we.clientX, 
            we.clientY, 
            viewPos.x,
            viewPos.y,
            scenePos.x,
            scenePos.y,
            newViewPos.x,
            newViewPos.y,
            viewPos.x - 
            newViewPos.x,
            viewPos.y - 
            newViewPos.y,
        )
        self.translate(
            viewPos.x - 
            newViewPos.x,
            viewPos.y - 
            newViewPos.y,
            0,
        )


        printf("wheel. result:%f opt:%f,degree:%f\n", 
            self._scale, opt.value, opt.degree);
    }
}
