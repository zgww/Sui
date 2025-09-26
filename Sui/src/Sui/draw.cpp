#include "tgfx/core/Canvas.h"
#include "tgfx/core/Image.h"
#include "tgfx/core/Matrix.h"
#include "tgfx/core/Paint.h"
#include "tgfx/core/RRect.h"
#include "tgfx/core/TextBlob.h"
#include "tgfx/core/Typeface.h"
#include <memory>
#include <stdlib.h>
#include <unordered_map>
#define NOMINMAX

#include "tgfx/gpu/opengl/wgl/WGLWindow.h"

#include <Windows.h>
#undef max
#include <stdio.h>
#include <gl/GL.h>

#include "./Sui/Core/Fps_orc.h"
#include "./Sui/Core/View_orc.h"
#include "./Sui/Core/ViewBase_orc.h"
#include "./Sui/View/Button_orc.h"
#include "./Sui/View/TableView_orc.h"
#include "./Sui/View/Slider_orc.h"
#include "./Sui/View/ScrollArea_orc.h"
#include "./Sui/View/ProgressView_orc.h"
#include "./Sui/View/ImageView_orc.h"
#include "./Sui/View/DockLayout_orc.h"
#include "./Sui/View/ColorPalete_orc.h"
#include "./Sui/View/TextView_orc.h"
#include "./Sui/View/EditText_orc.h"
#include "./Sui/View/EditText_orc.h"
#include "./SuiDesigner/Scene_orc.h"
#include "../../Naga/Utf8Util.h"


using namespace tgfx;

static Color mkColorByInt(int c){
    return Color::FromRGBA(
        SuiCore$colorGetR (c),
        SuiCore$colorGetG (c),
        SuiCore$colorGetB (c),
        SuiCore$colorGetA (c)
    );
}

static void getMatrixToTransform(Canvas *canvas, float *data){
    float tmp[6];
    canvas->getMatrix().get6(tmp);
    data[0] = tmp[0]; data[2] = tmp[1]; data[4] = tmp[2];
    data[1] = tmp[3]; data[3] = tmp[4]; data[5] = tmp[5];
}

std::shared_ptr<tgfx::Typeface> getDefaultTypeface(){
    static std::shared_ptr<tgfx::Typeface> defaultTypeface = NULL;
    if (!defaultTypeface){
        defaultTypeface = tgfx::Typeface::MakeFromName("Microsoft YaHei", "");
    }
    return defaultTypeface;
}

//tgfx返回的都是智能指针。 智能指针不好放到c结构体中
// static std::unordered_map<void*, std::shared_ptr<tgfx::Image>> imageSharedPtrPool;

void SuiView$ImageFromFile$dtor(SuiView$ImageFromFile *  self){
    auto img = (SuiView$Image*)self;
    if (img->data){
        std::shared_ptr<tgfx::Image> *p = (std::shared_ptr<tgfx::Image>*)img->data;
        // std::shared_ptr<tgfx::Image> *p = new std::shared_ptr<tgfx::Image>();
        // self->data = p;
        delete p;
        img->data = NULL;
    }
}
static std::shared_ptr<tgfx::Image> getImageSharedPtr(void *data){
    std::shared_ptr<tgfx::Image> *pImg = (std::shared_ptr<tgfx::Image>*)data;
    return (*pImg);
}
int  SuiView$ImageFromFile$width(SuiView$ImageFromFile *  self){
    auto img = (SuiView$Image*)self;
    if (img->data){
        return getImageSharedPtr(img->data)->width();
    }
    return 0;
}
int  SuiView$ImageFromFile$height(SuiView$ImageFromFile *  self){
    auto img = (SuiView$Image*)self;
    if (img->data){
        return getImageSharedPtr(img->data)->height();
    }
    return 0;
}
bool  SuiView$ImageFromFile$_initByFilePath(SuiView$ImageFromFile *  self, const char *  path){
    auto image = (SuiView$Image*)self;
    if (image->data){
        return false;
    }

    auto acpPath = Utf8Util::utf8_to_active_code_page(std::string(path));

    auto img = tgfx::Image::MakeFromFile(acpPath);
    if (!img){
        return false;
    }
    image->data = new std::shared_ptr<tgfx::Image>(img);

    return true;
}

void  SuiCore$Fps$draw(SuiCore$Fps *  self, void *  pCanvas, int  h){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    // tgfx::Canvas* canvas = dynamic_cast<tgfx::Canvas*>(pCanvas);
    // canvas->clear(tgfx::Color{1.f, 0.3f, 1.f, 1.f});
        // NVGcontext*vg = (NVGcontext*)canvas;

        // printf("%lld,%lld,%lld\n", 
        //     self.costMs,
        //     self.layoutCostMs,
        //     self.drawCostMs,
        // );
        // if 1 {
        //     return;
        // }
    tgfx::Paint paint = {};

        for (int i = 0; 0&&i < 70000; i++){
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            paint.setColor(tgfx::Color::FromRGBA(r, g, b));

            auto rect = tgfx::Rect::MakeXYWH(
                rand() % 8000,
                rand() % 600,
                rand() % 40 + 10,
                rand() % 40 + 10
            );

            canvas->drawRect(rect, paint);
        }


        canvas->save();
        canvas->translate(0, h - 30);

        char text[60];
        sprintf(text, "fps:%.1f/%.1f/%.1f", 
            self->fps,
            self->layoutFps,
            self->drawFps
        );

    paint.setColor(tgfx::Color::FromRGBA(0, 0, 0, 64));
    auto rect = tgfx::Rect::MakeXYWH(0, 0, 200, 30);
    canvas->drawRect(rect, paint);

    paint.setColor(tgfx::Color::FromRGBA(255,255,255,255));
    tgfx::Font font(getDefaultTypeface(), 14);
    canvas->drawSimpleText(text, 6, 12, font, paint);

        // nvgFillColor(vg, nvgRGBA(255, 255, 255, 255))
        // nvgText(vg, 6, 12, text, null)

        sprintf(text, "ms:%lld/%lld/%lld", 
            self->costMs,
            self->layoutCostMs,
            self->drawCostMs
        );

    paint.setColor(tgfx::Color::FromRGBA(255,255,255,255));
    canvas->drawSimpleText(text, 6, 26, font, paint);
        // nvgText(vg, 6, 26, text, null)
        // canvas->drawSimpleText(text, 6, 26, const Font &font, const Paint &paint)

    canvas->restore();
}

void  SuiCore$View$clip(SuiCore$View *  self, void *  pCanvas){
    Canvas* canvas = (Canvas*)(pCanvas);

    auto vb = (SuiCore$ViewBase*)self;

    float x = self->margin.left;
    float y = self->margin.top;
    float w = vb->frame.width - SuiCore$Inset$hor(&self->margin);
    float h = vb->frame.height - SuiCore$Inset$ver(&self->margin);
    // canvas->clipRect(Rect::MakeXYWH(x, y, w, h));
}
void  SuiCore$View$draw(SuiCore$View *  self, void *  pCanvas){
    Canvas* canvas = (Canvas*)(pCanvas);
    // {
    //     Paint paint;
    //     int r = 255;//rand() % 256;
    //     int g = 0;
    //     int b = 0;
    //     paint.setColor(tgfx::Color::FromRGBA(r, g, b));

    //     auto rect = tgfx::Rect::MakeXYWH(
    //         100, 10, 100, 100
    //     );

    //     canvas->drawRect(rect, paint);
    // }

    canvas->save();

    auto vb = (SuiCore$ViewBase*)self;
    float l = vb->frame.x;
    float t = vb->frame.y;

    canvas->translate(l, t);
    float *m = vb->transform.data;


    auto matrix = Matrix::MakeAll(
        m[0], m[2], m[4],
        m[1], m[3], m[5]);
    canvas->concat(matrix);
    getMatrixToTransform(canvas, vb->_world_transform.data);

    canvas->translate(self->margin.left, self->margin.right);
    bool need_draw = true;
    if (self->needClip && need_draw){
        // self->clip(self, pCanvas);
    }
    {
        //绘制自己
        if (need_draw){
            vb->draw_self(vb, pCanvas);
        }
        //内容区开始位置。并不用考虑内容区原点
        canvas->save();
        canvas->translate(self->padding.left + self->border->l->w, self->padding.top + self->border->t->w);
        vb->draw_children(vb, pCanvas);
        canvas->restore();
        //绘制边框。 在窗体内
        if (need_draw){
            self->drawSelfBorder(self, pCanvas);
        }
    }

    canvas->restore();

}
void  SuiCore$View$drawSelfBorder(SuiCore$View *  self, void *  pCanvas){
    Canvas* canvas = (Canvas*)(pCanvas);
        int tc = self->border->t->color;
        int rc = self->border->r->color;
        int bc = self->border->b->color;
        int lc = self->border->l->color;
        //不透明边框
        if (
            // self.border.t.w > 0 && 
            (
                SuiCore$colorGetA(tc) > 0 ||
                SuiCore$colorGetA(rc) > 0 ||
                SuiCore$colorGetA(bc) > 0 ||
                SuiCore$colorGetA(lc) > 0
                )
            ) {

            // Vec2 size = self.getSizeWithoutMargin();
            auto viewRect = self->getViewRect(self);
            float w = viewRect.w;
            float h = viewRect.h;

            // SkRRect rr = RadiusUtil::makeRRect(radius, w, h);
            //边框以stroke绘制。 导致边框可以溢出,所以需要内缩一半
            // float inset_dx = border.t.w / 2.f;
            // float inset_dy = border.t.w / 2.f;
            // rr.inset(inset_dx, inset_dy);
            //rr.inset(0.5f, 0.5f); //配合hairline,好像真的1像素左右了
            //TODO 暂不支持边框有分别的颜色
            // SkPaint paint;
            // if (border.t.w >= 1.001f) {
            //     paint.setAntiAlias(true);
            // }

            // paint.setColor(tc);
            // paint.setStrokeWidth(border.t.w <= 1.001f ? 0.0f : border.t.w);//0.0f for hairline
            // paint.setStyle(SkPaint::kStroke_Style);

            // canvas->drawRRect(rr, paint);

            Paint paint;
            paint.setStyle(PaintStyle::Stroke);
            if (SuiCore$Border$isAllHasWidth(self->border)){
                // nvgBeginPath(vg)
                if (self->border->t->w <= 1.001f ){
                    paint.setStrokeWidth(0);
                    // nvgStrokeWidth(vg, 1.0f)
                    // https://github.com/memononen/nanovg/issues/282
                    // 绘制一像素的线
                    // nvgRoundedRect(vg, 0.5f, 0.5f, w, h, self.radius.tl);
                } else {
                    // nvgRoundedRect(vg, 0.5f, 0.5f, w, h, self.radius.tl);
                    // nvgStrokeWidth(vg, self.border.t.w)
                }
                // nvgStrokeColor(vg, mkNVGColorByInt(self.border.t.color))
                paint.setColor(mkColorByInt(self->border->t->color));
                canvas->drawRoundRect(Rect::MakeXYWH(0.5, 0.5, w, h), 
                self->radius->tl,
                self->radius->tl,
                    paint);
                // nvgStrokeColor(vg, mkNVGColorByInt(self.border.t.color))
                // nvgStroke(vg);
            } 
            else {//单边
                if (self->border->t->w > 0.f){
                    Path path;
                    path.moveTo(0.5f, 0.5f);
                    path.lineTo(w + 0.5f, 0.5f);

                    paint.setStrokeWidth(self->border->t->w);
                    paint.setColor(mkColorByInt(self->border->t->color));

                    canvas->drawPath(path, paint);

                    // nvgBeginPath(vg)
                    // nvgMoveTo(vg, 0.5f, 0.5f)
                    // nvgLineTo(vg, w + 0.5f, 0.5f)

                    // nvgStrokeWidth(vg, self.border.t.w)
                    // nvgStrokeColor(vg, mkNVGColorByInt(self.border.t.color))
                    // nvgStroke(vg);
                }
                if (self->border->r->w > 0.f){
                    Path path;
                    path.moveTo(w + 0.5f, 0.5f);
                    path.lineTo(w + 0.5f, h + 0.5f);

                    paint.setStrokeWidth(self->border->r->w);
                    paint.setColor(mkColorByInt(self->border->r->color));

                    canvas->drawPath(path, paint);



                    // nvgBeginPath(vg)
                    // nvgMoveTo(vg, w + 0.5f, 0.5f)
                    // nvgLineTo(vg, w + 0.5f, h + 0.5f)

                    // nvgStrokeWidth(vg, self.border.r.w)
                    // nvgStrokeColor(vg, mkNVGColorByInt(self.border.r.color))
                    // nvgStroke(vg);
                }
                if (self->border->b->w > 0.f){

                    Path path;
                    path.moveTo(0 + 0.5f, h + 0.5f);
                    path.lineTo(w + 0.5f, h + 0.5f);

                    paint.setStrokeWidth(self->border->b->w);
                    paint.setColor(mkColorByInt(self->border->b->color));

                    canvas->drawPath(path, paint);


                    // nvgBeginPath(vg)
                    // nvgMoveTo(vg, 0.5f, h + 0.5f)
                    // nvgLineTo(vg, w + 0.5f, h + 0.5f)

                    // nvgStrokeWidth(vg, self.border.b.w)
                    // nvgStrokeColor(vg, mkNVGColorByInt(self.border.b.color))
                    // nvgStroke(vg);
                }
                if (self->border->l->w > 0.f){


                    Path path;
                    path.moveTo(0 + 0.5f, 0 + 0.5f);
                    path.lineTo(0 + 0.5f, h + 0.5f);

                    paint.setStrokeWidth(self->border->l->w);
                    paint.setColor(mkColorByInt(self->border->l->color));

                    canvas->drawPath(path, paint);

                    // nvgBeginPath(vg)
                    // nvgMoveTo(vg, 0.5f, 0.5f)
                    // nvgLineTo(vg, 0.5f, h + 0.5f)

                    // nvgStrokeWidth(vg, self.border.l.w)
                    // nvgStrokeColor(vg, mkNVGColorByInt(self.border.l.color))
                    // nvgStroke(vg);
                }
            }

        }
}
void  SuiCore$View$draw_self(SuiCore$View *  self, void *  pCanvas){
    Canvas* canvas = (Canvas*)(pCanvas);
    uint8_t bga = SuiCore$colorGetA (self->backgroundColor);
    if (bga > 0){//不透明
        auto size = self->getSizeWithoutMargin(self);
        float w = size.x;
        float h = size.y;

        uint8_t r = SuiCore$colorGetR (self->backgroundColor);
        uint8_t g = SuiCore$colorGetG (self->backgroundColor);
        uint8_t b = SuiCore$colorGetB (self->backgroundColor);

        Paint paint;
        paint.setStyle(PaintStyle::Fill);
        paint.setColor(Color::FromRGBA(
            r, g, b, bga
        ));
        canvas->drawRoundRect(Rect::MakeWH(w, h), self->radius->tl, self->radius->tl, paint);
    }
}
void  SuiCore$ViewBase$draw(SuiCore$ViewBase *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    canvas->save();

    float l = self->frame.x;
    float t = self->frame.y;

    //     //auto ml = get_taitank_node_layout_margin(yg, CSS_LEFT);
    //     //auto mt = get_taitank_node_layout_margin(yg, CSS_TOP);

    canvas->translate(l, t);

    float *m = self->transform.data;

    auto matrix = Matrix::MakeAll(
        m[0], m[2], m[4],
        m[1], m[3], m[5]);
    canvas->concat(matrix);
    getMatrixToTransform(canvas, self->_world_transform.data);

    {
        self->draw_self(self, canvas);
        self->draw_children(self, canvas);
    }

    canvas->restore();
}
void  SuiCore$ViewBase$draw_self(SuiCore$ViewBase *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    Paint paint;
    paint.setColor(mkColorByInt(0xff00ff33));
    paint.setStrokeWidth(10);
    canvas->drawRect(Rect::MakeXYWH(10, 10, 100, 100), paint);
    paint.setStyle(PaintStyle::Fill);
    canvas->drawRect(Rect::MakeXYWH(10, 10, 100, 100), paint);
    //     NVGcontext *vg =  (NVGcontext*)canvas;
    //     nvgFillColor(vg, mkNVGColorByInt(0xff00ff33));
    //     nvgStrokeColor(vg, mkNVGColorByInt(0xffff0033));
    //     nvgStrokeWidth(vg, 10);
    //     nvgBeginPath(vg)
    //     nvgRect(vg, 10, 10, 100, 100)
    //     nvgFill(vg)
    //     nvgStroke(vg)

}
void  SuiView$DrawButton$draw_self(SuiView$DrawButton *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
        //nvgFillColor(vg, mkNVGColorByInt(0xff00ff33));
        //nvgStrokeColor(vg, mkNVGColorByInt(0xffff0033));
        //nvgStrokeWidth(vg, 10);
        //nvgBeginPath(vg)
        //nvgRect(vg, 10, 10, 100, 100)
        //nvgFill(vg)
        //nvgStroke(vg)
        auto v = (SuiCore$View*)self;
        auto vb = (SuiCore$ViewBase*)self;

        auto vr = v->getViewRect(v);
		int x = 0;
		int y = 0;
		int w = vr.w;
		int h = vr.h;
		int cornerRadius = 5;

		int r = 156;
		int g = 156;
		int b = 156;
		// NVGpaint bg = nvgLinearGradient(vg, x,y,x,y+h, 
		// 	self.hover ? nvgRGBA(r,g,b,100) : nvgRGBA(r,g,b,128), 
		// 	self.hover ? nvgRGBA(r,g,b,160) : nvgRGBA(r,g,b,200),
		// );
        Paint paint;
        // self->normalBg = 0xffff0000;
        paint.setColor(mkColorByInt(vb->hover ? self->hoverBg : self->normalBg));

        canvas->drawRoundRect(
            Rect::MakeXYWH(x + 1, y + 1, w - 2, h - 2)
            , cornerRadius - 1, cornerRadius - 1, paint);

		// nvgFillColor(vg, 
			// mkNVGColorByInt(self.hover? self.hoverBg : self.normalBg));

		// nvgBeginPath(vg);
		// nvgRoundedRect(vg, x+1,y+1, w-2,h-2, cornerRadius-1);
		//if (!isBlack(col)) {
			//nvgFillColor(vg, col);
			//nvgFill(vg);
		//}
		// nvgFillPaint(vg, bg);
		// nvgFill(vg);
}
void  SuiView$TableView$draw_self(SuiView$TableView *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

    SuiCore$View$draw_self(v, pCanvas);

    // int w = self.layoutCtx.width
    // int h = self.layoutCtx.height
    auto r = v->getContentRect_baseViewRect(v);
    int w = r.w;
    int h = r.h;


    canvas->save();
    canvas->translate(r.x, r.y);

    //绘制网格线
    Paint paint;
    paint.setStrokeWidth(1);
    paint.setStyle(PaintStyle::Stroke);
    paint.setColor(Color::FromRGBA(255, 255, 255, 128));

    Path path;

    int colX = 0;
    //竖线
    int l = self->columns->size(self->columns);
    for (int i = 0; i < l - 1; i++){
        SuiView$TableViewColumn* col = (SuiView$TableViewColumn*)self->columns->get(self->columns, i);
        colX = colX + col->width;

        path.moveTo(colX, 0);
        path.lineTo( colX, h);
        // if (i < l){
        // 	TableViewColumn* col = self.columns.get(i)
        // 	colX = colX + col.width
        // }
    }

    int maxRow = ceil(h / self->rowHeight);
    int rowToDraw = Orc$maxInt(maxRow, self->row);

    //横线
    for (int r = 0; r < rowToDraw + 1; r++){
        int y = r * self->rowHeight;
        path.moveTo( 0, y);
        path.lineTo( w, y);
    }

    canvas->drawPath(path, paint);


    paint.setColor(Color::FromRGBA(255, 255, 255, 16));
    paint.setStyle(PaintStyle::Fill);
    // nvgFillColor(vg, nvgRGBA(255, 255, 255, 16))
    // nvgBeginPath(vg)
    Path path2;
    //隔行绘制
    for (int r = 0; r < rowToDraw + 1; ){
        int y = r * self->rowHeight;
        path2.addRect(Rect::MakeXYWH(0, y, w, self->rowHeight));
        r = r + 2;
    }
    canvas->drawPath(path2, paint);

    //绘制hover
    if (self->hoverRow != -1){
        int y = self->hoverRow * self->rowHeight;
        paint.setColor(Color::FromRGBA(255, 255, 255, 32));
        paint.setStyle(PaintStyle::Fill);

        canvas->drawRect(Rect::MakeXYWH(0, y, w, self->rowHeight), paint);
    }
    if (self->hoverCol != -1){
        //隔行绘制
        int y = self->hoverRow * self->rowHeight;

        paint.setColor(Color::FromRGBA(255, 255, 255, 32));
        paint.setStyle(PaintStyle::Fill);

        canvas->drawRect(
            Rect::MakeXYWH(self->hoverStartX, 0, self->hoverEndX - self->hoverStartX, h), 
            paint);
    }

    canvas->restore();
}
void  SuiView$Slider$draw_self(SuiView$Slider *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

		// super.draw_self(canvas)
    SuiCore$View$draw_self(v, pCanvas);

    //更新circle的位置
    ((SuiCore$ViewBase*)self->circle)->frame.x = self->calcToX(self);
    ((SuiCore$ViewBase*)self->circle)->frame.y = self->calcToY(self);

    float barH = 6;
    float w = vb->frame.width;
    float y = (vb->frame.height - barH) / 2.0;

		
    Paint paint;
    paint.setColor(mkColorByInt(0xffe1e1e1));
    //绘制进度条
    canvas->drawRect(Rect::MakeXYWH(0.f, y, w, barH), paint);

		//绘制底条
    paint.setColor(mkColorByInt(0xff1677ff));
    canvas->drawRect(Rect::MakeXYWH(0.f, y, w * self->value, barH), paint);
}
void  SuiView$ScrollArea$draw_children(SuiView$ScrollArea *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;
    auto ll = (SuiLayout$LayoutLinear*)self;

    //偏移到scroll原点
    canvas->save();
    v->clip(v, canvas);

    canvas->translate( 
        -self->scroll_model->scroll_left,
        -self->scroll_model->scroll_top
    );
    SuiCore$ViewBase$draw_children(vb, canvas);
    canvas->restore();
}
void  SuiView$ScrollArea$draw(SuiView$ScrollArea *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;
    auto ll = (SuiLayout$LayoutLinear*)self;

    //确保偏移正常
    if (self->scroll_model->clampScrollOffsetValid(self->scroll_model)) {
        self->fireScrollChanged(self);
        vb->invalidLayout(vb);
    }
    canvas->save();

    //应用基础偏移
    canvas->translate(
        vb->frame.x + v->margin.left, 
        vb->frame.y + v->margin.top);


    float *m = vb->transform.data;
    auto matrix = Matrix::MakeAll(
        m[0], m[2], m[4],
        m[1], m[3], m[5]);
    canvas->concat(matrix);
    getMatrixToTransform(canvas, vb->_world_transform.data);

    //绘制自己
    vb->draw_self(vb, canvas);
    //绘制内容
    SuiCore$ViewBase$draw_children(vb, canvas);
    canvas->restore();
}
void  SuiView$ScrollBar$draw_self(SuiView$ScrollBar *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;
    int x = 0;
    int w = vb->frame.width;
    int y = 0;
    int h =vb->frame.height;


    printf("绘制ScrollBar hover:%d\n", vb->hover);
		// 	//绘制滚动条背景
		// 	NVGpaint shadowPaint = nvgBoxGradient(
		// 		vg, 
		// 		x+w-12+1,y, 8,h,
		// 		3,4, 
		// 		nvgRGBA(0,0,0, self.hover ? 32: 16), 
		// 		nvgRGBA(0,0,0, self.hover ? 92 : 64)
		// 		);

		// 	nvgBeginPath(vg);
		// 	nvgRoundedRect(vg, x+w-12,y, 8,h, 3);
		// 	nvgFillPaint(vg, shadowPaint);
		// //	nvgFillColor(vg, nvgRGBA(255,0,0,128));
		// 	nvgFill(vg);

		// 	//滚动条
		// 	int scrollh = 50
		// 	int u = 30
		// 	int stackh = 150
		// 	if (self.scrollArea != null){
		// 		ScrollModel *model = self.scrollArea.scroll_model
		// 		stackh = model.get_v_length(h)
		// 		u = model.get_v_pos(h)
		// 		// u = self.scrollArea.scroll_model.scroll_top
		// 		// stackh = self.scrollArea.scroll_model.get_scroll_size().y
		// 	}
		// 	scrollh = (h/stackh) * (h-8);
		// 	// x+w-12-1,y+4+(h-8-scrollh)*u-1, 8,scrollh,
		// 		// x+w-12+2,y+4+1, 80,h-8,
		// 	NVGpaint shadowPaint2 = nvgBoxGradient(
		// 		vg, 
		// 		x - 2, u, 5, stackh,
		// 		3,4, 
		// 		nvgRGBA(255,255,255,128), 
		// 		nvgRGBA(128,128,128,128),
		// 		);
		// 	nvgBeginPath(vg);
		// 	nvgRoundedRect(vg, x, u, 5, stackh, 3);
		// 	// nvgRoundedRect(vg, 
		// 	// 	x+w-12+1,
		// 	// 	y+4+1 + (h-8-scrollh)*u, 
		// 	// 	8-2,scrollh-2, 2);
		// 	nvgFillPaint(vg, shadowPaint2);
		// //	nvgFillColor(vg, nvgRGBA(0,0,0,128));
		// 	nvgFill(vg);
		// }
}
void  SuiView$ProgressView$draw_self(SuiView$ProgressView *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

    SuiCore$View$draw_self(v, pCanvas);

    float w = vb->frame.width;


    //绘制进度
    Paint paint;
    paint.setColor(mkColorByInt(0xff1677ff));
    canvas->drawRect(
        Rect::MakeXYWH(0.f, 0.f, w * self->valueForAnim, vb->frame.height)
        , paint);
}
void  SuiView$ImageView$draw_self(SuiView$ImageView *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

    SuiCore$View$draw_self(v, pCanvas);
    if (self->_isImageValid(self)) {
        //ImageModeCalc@ calc = new ImageModeCalc();

        auto r = v->getViewRect(v);
        float w = r.w;// taitank::get_taitank_node_layout_width(yg);
        float h = r.h;// taitank::get_taitank_node_layout_height(yg);
        self->calc->calc(
            self->calc,
            self->_img->width(self->_img), self->_img->height(self->_img),
            w, h, self->imageMode
        );
        // drawImage_atRect(vg, self._img._img, 
        //     self.calc.sx, self.calc.sy, self.calc.sw, self.calc.sh, 
        //     self.calc.dx, self.calc.dy, self.calc.dw, self.calc.dh);
        // nvgFill(vg);

        auto img = getImageSharedPtr(self->_img->data);
        if (img){
            auto calc = self->calc;
            float wscale = calc->dw / (float)calc->sw;
            float hscale = calc->dh / (float)calc->sh;

            float ox = -calc->sx * wscale + calc->dx;
            float oy = -calc->sy * hscale + calc->dy;
            //需要缩放和平移
            Matrix mat = Matrix::MakeAll(
                wscale, 0, ox, 
                0, hscale, oy);
            canvas->drawImage(img, mat);
        }


        // SkRect src; 
        // src.setXYWH(calc.sx, calc.sy, calc.sw, calc.sh);
        // SkRect dst;
        // dst.setXYWH(calc.dx, calc.dy, calc.dw, calc.dh);
        // SkSamplingOptions opt{SkFilterMode::kLinear};
        // canvas->drawImageRect(_img, src, dst, opt, nullptr, SkCanvas::kFast_SrcRectConstraint);
    }

}
void  SuiView$DockLayout$drawDndIndicator(SuiView$DockLayout *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;
    auto node = (SuiCore$Node*)self;

    auto *drag = self->dragTab;

    if (!drag->isDragging){
        return;
    }
    if (!node->ownerWindow){
        return;
    }
    //计算绘制的位置
    auto mousePos = SuiCore$Mouse_getPosOfWindow(node->ownerWindow);
    auto *target = self->findDockItem_containsVec2(self, self->root, mousePos.x, mousePos.y);

    if (target && target->view){
        canvas->save();

        canvas->translate(
            v->padding.left + v->border->l->w, 
            v->padding.top + v->border->t->w
        );

        auto absRect = target->view->get_abs_rect(target->view);
        printf("mousePos.:%f,%f abs:%f,%f,%f,%f\n", 
            mousePos.x, mousePos.y, absRect.x, absRect.y, absRect.w, absRect.h
        );
        // drop type
        // Vec2 geo = absRect.containsPositionIn9Patch(mousePos.x, mousePos.y)
        auto geo = SuiCore$Rect$containsPositionIn5Patch(&absRect, mousePos.x, mousePos.y,
            SuiCore$mkRect(0.2, 0.2, 0.6, 0.6)
        );

        auto r =  SuiCore$Frame$toRect(&target->view->frame);

        Paint paint;
        paint.setColor(Color::FromRGBA(255, 0, 0, 64));
        canvas->drawRect(Rect::MakeXYWH(

                r.x + r.w * geo.x 
                , r.y + r.h * geo.y 
                , r.w * geo.w
                , r.h * geo.h
        ), paint);
        canvas->restore();
    }
}
void  SuiView$ColorPalete$drawCircle(SuiView$ColorPalete *  self, void *  pCanvas, int  x, int  y){

}

void  SuiView$ColorPalete$drawMark(SuiView$ColorPalete *  self, void *  pCanvas, int  w, int  y){

}
void  SuiView$ColorPalete$drawHue(SuiView$ColorPalete *  self, void *  pCanvas, int  w, int  h){

}
void  SuiView$ColorPalete$drawAlpha(SuiView$ColorPalete *  self, void *  pCanvas, int  w, int  h){

}
void  SuiView$ColorPalete$drawSv(SuiView$ColorPalete *  self, void *  pCanvas, int  w, int  h){

}
int SuiView$TextLayout$measureText_returnLineWidth(SuiView$TextLayout *  self, const char *  str, float *  bounds)
{
    tgfx::Font font(getDefaultTypeface(), self->font_size);
    auto blob = TextBlob::MakeFrom(std::string(str), font);
    auto b = blob->getBounds();

    bounds[0] = b.left;
    bounds[1] = b.top;
    bounds[2] = b.right;
    bounds[3] = b.bottom;

    return b.right;
}
void  SuiView$TextView$draw_self(SuiView$TextView *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;


    SuiCore$View$draw_self(v, pCanvas);

    //_canvas = canvas; //记录使用的canvas

    // if (for_test != nullptr) for_test();

    //if (_measure_dirty) {
        //_set_tl();
    float w = 0.f;// taitank::get_taitank_node_layout_width(yg);
    float h = 0.f;// taitank::get_taitank_node_layout_height(yg);
        //_text_layout.layout(w, h);
    //}
    float pl = v->padding.left;// taitank::get_taitank_node_layout_padding(yg, CSS_LEFT);
    float pt = v->padding.top;// taitank::get_taitank_node_layout_padding(yg, CSS_TOP);
    // SkFont f;
    // f.setSize(font_size);
    // f.setTypeface(TextView_typeface);
    //f.setFontSize(font_size);

    auto color = mkColorByInt(self->color);
    Paint paint;
    paint.setColor(color);
    // paint.setAntiAlias(true);

    tgfx::Font font(getDefaultTypeface(), self->font_size);
    // SkPaint paint;
    // paint.setAntiAlias(true);
    // paint.setColor(color);
    int l = self->_text_layout->line_infos->size(self->_text_layout->line_infos);
    for (int i = 0; i < l; i++) {
        auto* li = (SuiView$TextLineInfo*)self->_text_layout->line_infos->get(self->_text_layout->line_infos, i);
        const char *s = li->text->str;

        canvas->drawSimpleText(li->text->str, 
            li->x + pl + self->_text_layout->area_x,
            li->y + pt,
            font, paint);

        // canvas->drawSimpleText(
        // 	li.text.c_str(),
        // 	li.text.size(),
        // 	SkTextEncoding::kUTF8,
        // 	li.x + pl + _text_layout.area_x,
        // 	li.y + pt,
        // 	f,
        // 	paint
        // );
    }

}
void  SuiView$EditText$draw_editing(SuiView$EditText *  self, void *  pCanvas, int  h){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

}
void  SuiView$EditText$draw_self(SuiView$EditText *  self, void *  pCanvas){
    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

}
void SuiDesigner$SceneView$draw_self(SuiDesigner$SceneView *self,
                                     void *pCanvas) {


    tgfx::Canvas* canvas = (tgfx::Canvas*)(pCanvas);
    auto v = (SuiCore$View*)self;
    auto vb = (SuiCore$ViewBase*)self;

    // super.draw_self(canvas)
    // int bg = self.chessBg.gocChessBgImage(canvas);
    //绘制背景
    // NVGpaint bp = nvgImagePattern(
    //     vg, 0, 0, self.chessBg.width, self.chessBg.height, 0, bg, 1
    // );

    auto r = v->getViewRect(v);

    // nvgBeginPath(vg);
    // nvgRect(vg, 0, 0, r.w, r.h)
    // nvgFillPaint(vg, bp)	
    // nvgFill(vg)
    Paint paint;
    float c = 0.85f;
    paint.setColor(Color{c, c, c, 1.f});
    int tileSize = 20;
    for (int y = 0; 0 && y < r.h; y += tileSize) {
        bool draw = (y / tileSize) % 2 == 1;
        for (int x = 0; x < r.w; x += tileSize) {
                if (draw) {
                    auto rect = tgfx::Rect::MakeXYWH(
                        static_cast<float>(x), static_cast<float>(y),
                        static_cast<float>(tileSize),
                        static_cast<float>(tileSize));
                    canvas->drawRect(rect, paint);
                }
                draw = !draw;
        }
    }

    // canvas->drawRect(Rect::MakeXYWH(0.f, 0.f, r.w, r.h), paint);
}
void SuiDesigner$SceneView$drawSelfBorder(SuiDesigner$SceneView *self,
                                          void *pCanvas) {}