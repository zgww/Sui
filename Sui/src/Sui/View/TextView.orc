package SuiView 

#include <stdio.h>
#include <string.h>
#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Node.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Color.orc"
import * from "../Core/Frame.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../View/ViewBuilder.orc"
import * from "../../Orc/Math.orc"
import * from "../Core/Global.orc"
import * from "../Core/Canvas.orc"


 
class TextLineInfo  {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	String@ text;

	void ctor(){
		// printf("new TextLineInfo :%p\n", self)
	}
	void dtor(){
		// printf("free TextLineInfo:%p rect:%d,%d,%d,%d, &text:%p\n", self, self.x, self.y, self.w, self.h, self.text)
	}
	//vector<int> rune_x_list;//符号的x坐标
	
	void update_text_align(int out_w, const char * text_align){
		if (strcmp(text_align, "left") == 0) {
			self.x = 0;
		} 
		else if (strcmp(text_align, "center") == 0) {
			self.x = (out_w - self.w) / 2;
		}
		else if (strcmp(text_align,  "right") == 0) {
			self.x = (out_w - self.w);
		}
	}
}



class  TextLayout {
	void ctor(){
		// printf("new TextLayout :%p\n", self)
	}
	void dtor(){
		// printf("free TextLayout:%p\n", self)
	}
	String@ ellipsis_line(const char * text){
		String@ s = str(text)
		String@ s2 = s.substringByCount(0, s.size() - 1).add("..")
		
		// const char * ret = Utf8Util::substr(text, 0, Utf8Util::length(text) - 1) + "..";
		// return str(ret)
		return s2;
	}
	String@ text = str("");
	// center|right|left
	String@ text_align = str("left");
	int max_line = 0;//<=0表示不限制
	int font_size = 14;
	float line_height = 1.4f;
	//SkTypeface *typeface;
	// /*<TextLineInfo>*/
	List@ line_infos = new List()
	// Trace t;
	//限定区域
	int w;
	int h;
	// 实际使用区域
	int use_max_w = 0;
	int use_max_h = 0;
	bool ellipsis = false; 
	// SkFont _font;

	//整个文本块适应text_align后的起始位置LineInfo中存放的是相对于文本块的对齐； 文本块相对于整个空间的对齐,记录在此;
	int area_x = 0;
	//唯一标识
	char _key[256];


	int get_actual_line_height(){

		float lh = self.line_height * self.font_size;
		return maxInt((int)lh, self.font_size);
	}

	bool dirty = true
	void setText(const char *v){
		if (!self.text.equals(v)){
			self.text.set(v)
			self.dirty = true;
		}
	}
	void setTextAlign(const char *v){
		if (!self.text_align.equals(v)){
			self.text_align.set(v)
			self.dirty = true;
		}
	}
	void setMaxLine(int v){
		if (self.max_line != v){
			self.max_line = v
			self.dirty = true
		}
	}
	void setW(int w){
		if (self.w != w){
			self.w = w
			self.dirty = true
		}
	}
	void setH(int v){
		if (self.h != v){
			self.h = v
			self.dirty = true
		}
	}
	void setFontSize(int v){
		if (self.font_size != v){
			self.font_size = v
			self.dirty = true
		}
	}

	// /*给定宽高和最大行数，确定每行文本，坐标; */
	void layout(int w, int h){
		
		self.setW(w)
		self.setH(h)

		if (!self.dirty){
			return
		}
		self.dirty = false
		
		// bool c0 = t.changed(text, "text");
		// bool c1 = t.changed(font_size, "font_size");
		// bool c2 = t.changed(text_align, "text_align");
		// bool c3 = t.changed(w, "w");
		// bool c4 = t.changed(h, "h");
		// bool c5 = t.changed(max_line, "max_line");
		// if (!(c0 || c1 || c2 || c3 || c4 || c5)) {//输入不变
		// 	return;
		// }
		List@ lines = self.text.splitByRe("\n");

		//重置
		self.use_max_w = 0;
		self.use_max_h = 0;
		self.line_infos.clear();
		int l = lines.size()
		for (int i = 0; i < l; i++) { 
			String* line = (String*)lines.get(i);
			if (self.layout_line(line.str)) {
				break;
			}
		}
		float lh = self.get_actual_line_height();
		float half_lh_space = (lh - self.font_size) / 2;
		float y = half_lh_space + self.font_size;
		l = self.line_infos.size()
		for (int i = 0; i < l; i++) {
			TextLineInfo* li = (TextLineInfo*)self.line_infos.get(i);
			li.y = y;
			if (self.use_max_w < li.w) {
				self.use_max_w = li.w;
			}
			y = y + lh;
			if (h > 0) { //高度有限制时的'..'
				//if (ellipsis && y > h) {// overflow
				//	line_infos.erase(line_infos.begin() + i + 1, line_infos.end());
				//	auto& tmp = line_infos[line_infos.size() - 1];
				//	tmp.text = ellipsis_line(tmp.text);
				//	break;
				//}
				//if (y > h + lh) {//已经在高度外了
				//	line_infos.erase(line_infos.begin() + i + 1, line_infos.end());
				//	break;
				//}
			}
		}
		l = self.line_infos.size()
		for (int i = 0; i < l; i++) {
			//文本是内容，对齐只对多行文本有效
			TextLineInfo* li = (TextLineInfo*)self.line_infos.get(i);
			li.update_text_align(self.use_max_w, self.text_align.str);
		}
		float descent = self.font_size / 3.f; //约算
		self.use_max_h = y - half_lh_space - self.font_size + descent;
		self.area_x = 0;
		if (self.text_align .equals( "center")) {
			self.area_x = (w - self.use_max_w) / 2.f;
		}
		if (self.text_align .equals("right")) {
			self.area_x = (w - self.use_max_w);
		}

		//ellipsis
		if (self.use_max_w > w) { //use_max_w > w肯定是不换行，只有一行的情况
		}
		else if (self.use_max_h > h) { //多行。
		}
	}
	// /*单行布局 返回 最大行是否满了*/
	bool layout_line(const char * line){
		List@ lines = self.break_text(line);
		if (self.max_line <= 0) {
			int l = lines.size()
			for (int i = 0; i < l; i++) {
				self.line_infos.add(lines.get(i));
			}
			return false;
		}
		else {
			int l = lines.size()	
			for (int i = 0; i < l; i++) {
				TextLineInfo* line = (TextLineInfo*)lines.get(i);
				if (self.line_infos.size() < self.max_line) {
					self.line_infos.add(line);
				}
				else { //省略号 overflow
					if (self.ellipsis) { 
						if (i > 0) {
							TextLineInfo* li = (TextLineInfo*)self.line_infos.get(self.line_infos.size() - 1);
							li.text = self.ellipsis_line(li.text.str);
						}
					}
					break;
				}
			}
			return self.line_infos.size() >= self.max_line;
		}
	}
	float measureText(const char *str, float *bounds){
		
	 	Canvas *canvas = Global_getCanvas();
		int line_w = (int)canvas.textBounds( 0, 0, str, NULL, bounds);
		return line_w
	}
	//超出就换行，每行最少一个字符
	// vector<TextLineInfo> break_text(string line);
	List@ break_text(const char *line){
	 	Canvas *canvas = Global_getCanvas();
		//预估字符数。
		int min_cap_char_cnt = maxInt(1, (int)(self.w / self.font_size) - 1);
		String@ remain = str(line);
		// vector<TextLineInfo> lines;
		List@ lines = new List();
		// Rect@ bounds = new Rect();
		float bounds[4];//[xmin,ymin, xmax,ymax]
		memset(bounds, 0, sizeof(bounds))

		int prev_w = 0;
		//if (line.find("23233") != -1) {
			//printf("line:%s\n", line.c_str());
		//}

		canvas.fontSize( self.font_size);

		while (remain.notEquals("")) {
			int l = min_cap_char_cnt + 1; //对应规则，每行至少一个字符
			int ml = remain.size();
			while (true) { // 寻找结束位置
				String@ subtext = remain.substringByCount(0, l);
				int line_w = (int)canvas.textBounds( 0, 0, subtext.str, NULL, bounds);
				// float line_w = (int)_font.measureText(
				// 	subtext.c_str(), subtext.size(),
				// 	SkTextEncoding::kUTF8,
				// 	&bounds
				// );
				float boundHeight = bounds[3] - bounds[1];
				if (line_w > self.w) {//提前break
					TextLineInfo @line_info = new TextLineInfo();
					line_info.text = remain.substringByCount(0, l - 1);
					line_info.w = prev_w;
					line_info.h = (int)(boundHeight);
					lines.add(line_info);
					remain = remain.substringByCount(l - 1, remain.size());
					break;
				}
				if (l >= ml) { //最后一行，还没有满
					TextLineInfo @line_info = new TextLineInfo();
					line_info.text = remain.substringByCount(0, l);
					line_info.w = line_w;
					line_info.h = (int)boundHeight;
					lines.add(line_info);
					remain = str("");
					break;
				}
				prev_w = line_w;
				l = l + 1;
			}
		}
		return lines
	}

}
struct RuneInfo{
	int rune_index// = -1;
	//int char_index = -1;
	int x //= 0; //相对于text view坐标
	int y //= 0;
}
/// 布局上下文
class TextView extends View {
	// void dtor(){
	// 	printf("~TextView:%p\n", self)
	// }
	Vec2 get_pos_by_rune_cnt(int rune_cnt){
		Vec2 ret = mkVec2(0, 0);
		for (int r = 0; r < self._text_layout.line_infos.size(); r++) {
			TextLineInfo* li = (TextLineInfo*)self._text_layout.line_infos.get(r);
			String@ utf8 = li.text;
			int rune_len = utf8.length();
			if (rune_cnt > rune_len){
				rune_cnt = rune_cnt - rune_len;
				continue;
			}
			else {
				String@ tmpText = utf8.substringByCount(0, rune_cnt);
				ret.x = li.x + (int)self._text_layout.measureText(
						tmpText.str, 
						NULL
					);
				ret.y = li.y;
			}
		}

		return ret;
	}
	Frame cacheFrame = mkFrame();
	void layout(Frame* ctx) {
		if (!self.layoutDirty){
			// 如果上一次的结果，还能满足此次的约束，
			if (self.cacheFrame.isSizeSatisfy_otherFrameConstraints(ctx)){
				// printf("TextView layout use cache layout \n")
				return;
			}
			// printf("TextView :%s layout not dirty %f,%f,%f,%f %f,%f,%f,%f\n",
			// 	self.text.str,
			// 	ctx.minWidth,
			// 	ctx.minHeight,
			// 	ctx.maxWidth,
			// 	ctx.maxHeight,

			// 	ctx.prevMinWidth,
			// 	ctx.prevMinHeight,
			// 	ctx.prevMaxWidth,
			// 	ctx.prevMaxHeight,
			// )
		}

		self.layoutDirty = false;

		ctx.incTimesInOneLayout()
		
		//根据自身的宽高声明，进一步约束
		self.updateFrame_forSelfWidthHeight(ctx);

		//约束定死了，不用布局
		if (ctx->setSize_ifTight()) {
			Frame _ctx = self.makeContentLayoutCtx(ctx);
			//逐字计算
			self._set_tl();
			self._text_layout.layout(_ctx.maxWidth, _ctx.maxHeight );
			self.cacheFrame = ctx.copy()
			return;
		}

		if (self.text.equals( "")) {
			ctx->setSize(self.margin.hor(), self.margin.ver());

			Frame _ctx = self.makeContentLayoutCtx(ctx);
			self._set_tl();
			self._text_layout.layout(_ctx.maxWidth, _ctx.maxHeight );

			self.cacheFrame = ctx.copy()
			return;
		}

		Frame contentCtx = self.makeContentLayoutCtx(ctx);

		//逐字计算
		self._set_tl();
		self._text_layout.layout(
			ctx->maxWidth == infinity ? 99999999 : ctx->maxWidth,
			ctx->maxHeight == infinity ? 99999999 : ctx->maxHeight
		);

		//得到了宽高
		contentCtx.setSize(self._text_layout.use_max_w, self._text_layout.use_max_h);

		self.updateFrame_byContentCtx(ctx, &contentCtx);
		self.cacheFrame = ctx.copy()

			// printf("TextView :%s after layout %f,%f,%f,%f %f,%f,%f,%f %d\n",
			// 	self.text.str,
			// 	ctx.minWidth,
			// 	ctx.minHeight,
			// 	ctx.maxWidth,
			// 	ctx.maxHeight,

			// 	ctx.prevMinWidth,
			// 	ctx.prevMinHeight,
			// 	ctx.prevMaxWidth,
			// 	ctx.prevMaxHeight,
			// 	ctx.isConstraintsNotChanged(),
			// )
	}
	// void ctor(){

	// }
	bool layoutDirty = true;

	void invalidLayout(){
		super.invalidLayout()
		// printf("TextView invalidLayout\n")
		self.layoutDirty = true;
	}

	String@ text = str("")	
	// void setTextCstr(const char *text){
	// 	self.setText(str(text))
	// }
	void setText(String@ text){
		if (self->text .equalsString( text) ) {
			return;
		}
		self->text = text;
		self.invalidLayout();
	}
	int font_size = 14;
    void setFont_size(int v){ 
        if (v != self->font_size){
            self->font_size = v; 
			self.invalidLayout();
        }
    }
	//BUG 类型错误。。 orcc 没有诊断出来
	String@ font_face = str("");
    void setFont_face(String* v){ 
        if (!self->font_face.equals(v.str)){
            self->font_face = v; 
			self.invalidLayout();
        }
    }

	int color = 0xff000000;
    void setColor(int v){ 
        if (v != self->color){
            self->color = v; 
			self.invalidDraw();
        }
    }

	int font_weight = 0;
    void setFont_weight(int v){ 
        if (v != self->font_weight){
            self->font_weight = v; 
			self.invalidLayout();
        }
    }
	bool underline = false;
    void setUnderline(bool v){ 
        if (v != self->underline){
            self->underline = v; 
			self.invalidDraw();
        }
    }
	bool line_through = false;
    void setLine_through(bool v){ 
        if (v != self->line_through){
            self->line_through = v; 
			self.invalidDraw();
        }
    }
	bool italic = false;
    void setItalic(bool v){ 
        if (v != self->italic){
            self->italic = v; 
			self.invalidDraw();
        }
    }
	float line_height = 1.4f;
    void setLine_height(float v){ 
        if (v != self->line_height){
            self->line_height = v; 
			self.invalidLayout();
        }
    }
	String@ text_align = str("left");
    void setText_align(String@ v){ 
        if (v != self->text_align){
            self->text_align = v; 
			self.invalidLayout();
        }
    }
	bool wrap = false;
    void setWrap(bool v){ 
        if (v != self->wrap){
            self->wrap = v; 
			self.invalidLayout();
        }
    }
	int max_line = 0;
    void setMax_line(int v){ 
        if (v != self->max_line){
            self->max_line = v; 
			self.invalidLayout();
        }
    }

	bool overflow_ellipsis = false;
    void setOverflow_ellipsis(bool v){ 
        if (v != self->overflow_ellipsis){
            self->overflow_ellipsis = v; 
			self.invalidDraw();
        }
    }
	TextLayout@ _text_layout = new TextLayout();

	bool _measure_dirty = true;

	//按位置找到字符的位置
	RuneInfo get_rune_index_at_local_pos(Vec2* pos){
		RuneInfo ret;
		memset(&ret, 0, sizeof(ret))

		ret.rune_index = 0;
		//ret.char_index = 0;
		float lh = self._text_layout.get_actual_line_height();
		int l = self._text_layout.line_infos.size()
		for (int i = 0; i < l; i++) {
			TextLineInfo* li = (TextLineInfo*)self._text_layout.line_infos.get(i);
			//行的下边界
			//auto y1 = i < l - 1 ? _text_layout.line_infos[i + 1].y : getLayoutHeight();
			String@ utf8 = li.text;
			float y0 = i * lh;
			if (y0 <= pos.y && pos.y <= y0 + lh) {//是当前行
				//判断x
				int left = 0;
				ret.y = li.y;
				int jl = utf8.size()
				for (int j = 1; j < jl; j++) {
					String@ subtext = utf8.substringByCount(0, j);
					// auto right = (int)_text_layout._font.measureText(
					// 	subtext.c_str(), subtext.size(),
					// 	SkTextEncoding::kUTF8,
					// 	nullptr
					// );
					float right = self._text_layout.measureText(
						subtext.str, NULL
					)
					if (left <= pos.x && pos.x <= right) {
						//决定偏左还是偏右
						if (pos.x <= (left + right) / 2.0f) {//偏左
							String@ prevtext = subtext.substringByCount(0, j - 1);
							ret.rune_index = ret.rune_index + prevtext.size();
							//ret.char_index += prevtext.utf8string.size();
							ret.x = left;
						}
						else {//偏右
							ret.rune_index = ret.rune_index + subtext.size();
							//ret.char_index += subtext.size();
							ret.x = right;
						}
						return ret;
					}
					left = right;
				}
				//不在字符范围内，默认为最后
				ret.rune_index = ret.rune_index + utf8.size();
				//ret.char_index += utf8.utf8string.size();
				ret.x = self._text_layout.measureText(
					li.text.str, NULL
				)

				// ret.x = (int)_text_layout._font.measureText(
				// 		li.text.c_str(), li.text.size(),
				// 		SkTextEncoding::kUTF8,
				// 		nullptr
				// 	);
				return ret;
			}
			else {
				ret.rune_index = ret.rune_index + utf8.size();
				//ret.char_index += utf8.utf8string.size();
			} 
		}
		return ret
	}
	//virtual void onUnmounting() override;


	//static void registerMeta();

	void _set_tl(){
		TextLayout* tl = self._text_layout;
		// SkFont font;
		// font.setSize(font_size);
		// font.setTypeface(TextView_typeface);

		//TODO set vg
		// tl.vg = vg
		// tl._font = font;
		tl.setText( self.text.str);
		tl.setTextAlign(self.text_align.str);
		tl.setFontSize(self.font_size);
		//tl.typeface = typeface;
		tl.setMaxLine(self.max_line); 
		
		tl.ellipsis = self.overflow_ellipsis;
		tl.line_height = self.line_height;
	}
	//virtual TaitankSize measure(float w, MeasureMode w_mode, float h, MeasureMode h_mode, void* layout_context) ;
    //只画自己,不用管坐标系
	void draw_self(Canvas* canvas){
		super.draw_self(canvas); 
		//_canvas = canvas; //记录使用的canvas

		// if (for_test != nullptr) for_test();

		//if (_measure_dirty) {
			//_set_tl();
			float w = 0.f;// taitank::get_taitank_node_layout_width(yg);
			float h = 0.f;// taitank::get_taitank_node_layout_height(yg);
			//_text_layout.layout(w, h);
		//}
			float pl = self.padding.left;// taitank::get_taitank_node_layout_padding(yg, CSS_LEFT);
			float pt = self.padding.top;// taitank::get_taitank_node_layout_padding(yg, CSS_TOP);
		// SkFont f;
		// f.setSize(font_size);
		// f.setTypeface(TextView_typeface);
		//f.setFontSize(font_size);

		// NVGcolor color = mkNVGColorByInt(self.color)
		canvas.fillColorByInt32(self.color)
		// SkPaint paint;
		// paint.setAntiAlias(true);
		// paint.setColor(color);
		canvas.fontSize( self.font_size)
		int l = self._text_layout.line_infos.size()
		for (int i = 0; i < l; i++) {
			TextLineInfo* li = (TextLineInfo*)self._text_layout.line_infos.get(i);
			const char *s = li.text.str
			canvas.text(
				li.x + pl + self._text_layout.area_x,
				li.y + pt,
				li.text.str
				)
			const char *s2 = li.text.str
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

}



TextView@ mkTextView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (TextView@)gocNode(sp, (Node*)parent, TextView)
}

