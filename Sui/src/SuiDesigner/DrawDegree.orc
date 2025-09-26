package SuiDesigner

#include <math.h>
#include <stdio.h>


import * from "../Orc/Math.orc"
import * from "../Orc/List.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sui/Core/Mat2d.orc"
import * from "../Sui/Core/Vec3.orc"


class DrawDegreeItem {
    float value;//缩放级别
    float degree; //刻度间隔
}
static DrawDegreeItem@ mkItem(float value, float degree) {
    DrawDegreeItem@ item = new DrawDegreeItem();
    item.value = value;
    item.degree = degree;
    return item;
}
//绘制刻度尺
class DrawDegree {
    List@ options = new List()
    List@ levelOptions = new List()
    float curScale = 1.0; //当前缩放级别
    DrawDegreeItem@ curOption = null; //当前选中刻度尺选项

    void ctor(){
        self.options.{
            // o.add(mkItem( 0.1, 500));
            o.add(mkItem( 0.2, 500));
            o.add(mkItem( 0.5, 100));
            o.add(mkItem( 0.8, 80));
            o.add(mkItem( 1.0, 50));
            o.add(mkItem( 1.2, 45));
            o.add(mkItem( 1.4, 40));
            o.add(mkItem( 1.6, 35));
            o.add(mkItem( 1.8, 30));
            o.add(mkItem( 2.0, 25));
            o.add(mkItem( 4.0, 10));
            o.add(mkItem( 6.0, 5));
            o.add(mkItem( 10.0, 5));
            o.add(mkItem( 16.0, 2));
            o.add(mkItem( 26.0, 2));
            o.add(mkItem( 60.0, 1));
            o.add(mkItem( 100.0, 1));
            o.add(mkItem( 150.0, 1));
            o.add(mkItem( 200.0, 1));
        }
        self.genLevels(4)
        self.setScale(1.0);
    }
    // [count]每级生成多个
    void genLevels(int count){
        List@ opts = new List();
        printf("options.size:%d\n", self.options.size());
        for (int i = 0; i < self.options.size() - 1; i++) {
            DrawDegreeItem@ cur = (DrawDegreeItem@)self.options.get(i);
            DrawDegreeItem@ next = (DrawDegreeItem@)self.options.get(i + 1);
            float step = (next.value - cur.value) / (float)count;

            printf("\t\tnext.value.:%f\n", next.value);
            
            for (float j = cur.value; j < next.value; j += step) {
                DrawDegreeItem@ item = mkItem(j, cur.degree);
                opts.add(item);
            }
        }
        DrawDegreeItem@ last = (DrawDegreeItem@)self.options.last()
        opts.add(mkItem(last.value, last.degree));
        self.levelOptions = opts;
    }

    DrawDegreeItem@ findAndReturnOffset(float scale, int offset){
        //找到匹配的option
        for (int i = self.levelOptions.size() - 1;  i >= 0; i--){
            DrawDegreeItem@ cur = (DrawDegreeItem@)self.levelOptions.get(i);
            if (cur.value <= scale){
                int retIndex = i + offset
                retIndex = clampInt(retIndex, 0, self.levelOptions.size() - 1)
                DrawDegreeItem@ ret =  self.levelOptions.get(retIndex)
                return ret
            }
        }
        return null
    }

    DrawDegreeItem@ findAndUpdateCurOption(float scale){
        if scale == self.curScale {
            if self.curOption {
                return self.curOption;
            }
        }
        //找到匹配的option
        for (int i = self.levelOptions.size() - 1;  i >= 0; i--){
            DrawDegreeItem@ cur = (DrawDegreeItem@)self.levelOptions.get(i);
            if (cur.value <= scale){
                self.curOption = cur;
                break;
            }
        }
        self.curScale = scale
        return self.curOption
    }
    void setScale(float scale){
        self.findAndUpdateCurOption(scale)
    }

    void draw(
        Canvas *canvas, 
        Mat2d sceneMat2d, 
        float w, float h,
        float mouseX, float mouseY
        ){

        if !self.curOption{
            return
        }

        Mat2d inv = sceneMat2d.inverseNew()
        Vec3 leftTop = inv.transformPoint(0.f, 0.f, 0.f); //视图系转世界系
        Vec3 rightBottom = inv.transformPoint(w, h, 0.f);

        float degree = self.curOption.degree;
        float startX = floor(leftTop.x / degree) * degree - degree;
        float startY = floor(leftTop.y / degree) * degree - degree;
        float endX = floor(rightBottom.x / degree) * degree + degree;
        float endY = floor(rightBottom.y / degree) * degree + degree;

        // 绘制坐标轴
        {
            Vec3 left = sceneMat2d.transformPoint(leftTop.x, 0.f, 0.f);
            Vec3 right = sceneMat2d.transformPoint(rightBottom.x, 0.f, 0.f);
            // x轴
            canvas.beginPath();
            canvas.moveTo(left.x+0.0f, left.y+0.5f)//+0.5是因为nanovg 实现1像素线要求的
            canvas.lineTo(right.x + 0.0f, right.y+0.5f)
            canvas.strokeWidth(1.f)
            canvas.strokeColor(255, 0, 0, 128)
            canvas.stroke();
        }

        {
            Vec3 left = sceneMat2d.transformPoint(0.f, leftTop.y, 0.f);
            Vec3 right = sceneMat2d.transformPoint(0.f, rightBottom.y, 0.f);
            // y轴
            canvas.beginPath();
            canvas.moveTo(left.x + 0.5f, left.y)
            canvas.lineTo(right.x + 0.5f, right.y)
            canvas.strokeColor(0, 255, 0, 128)
            canvas.stroke();
        }


        canvas.fillColor(255, 255, 255, 200);
        canvas.fontSize(12)
        // 刻度尺水平轴
        for (float x = startX; x <= endX; x += degree ){
            float y = leftTop.y;
            Vec3 viewPoint = sceneMat2d.transformPoint(x, y, 0.f);
            canvas.beginPath();
            canvas.rect(viewPoint.x, viewPoint.y, 1.f, 12.f);
            canvas.fill();

            char tmp[20];
            sprintf(tmp, "%.0f", x);
            canvas.text(viewPoint.x + 3, 10.f, tmp);
        }
        // 刻度尺垂直轴
        float yDegree = endY >= startY ? degree : -degree;
        for (float y = startY; y <= endY; y += yDegree ){
            float x = leftTop.x;
            Vec3 viewPoint = sceneMat2d.transformPoint(x, y, 0.f);
            canvas.beginPath();
            canvas.rect(viewPoint.x, viewPoint.y, 12.f, 1.f);
            canvas.fill();

            char tmp[20];
            sprintf(tmp, "%.0f", y);
            canvas.text(0.f, viewPoint.y + 12.f, tmp);
        }

    }

}