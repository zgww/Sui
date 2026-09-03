#include "TextView.h"
#include "../Core/Window.h"
#include "../Core/Canvas.h"
#include "../Core/App.h"
#include "../Meta/MetaRegistry.h"

void TextView::setText(const std::string& t) {
	if (text != t) {
		text = t;
		invalidLayout();
	}
}

void TextView::setFontSize(float s) {
	if (fontSize != s) {
		fontSize = s;
		invalidLayout();
	}
}

void TextView::setColor(int c) {
	color = c;
	invalidDraw();
}

void TextView::setTextAlign(const std::string& a) {
	if (textAlign != a) {
		textAlign = a;
		invalidLayout();
	}
}

void TextView::setWrap(bool w) {
	if (wrap != w) {
		wrap = w;
		invalidLayout();
	}
}

void TextView::setMaxLine(int m) {
	if (maxLine != m) {
		maxLine = m;
		invalidLayout();
	}
}

void TextView::setLineHeight(float h) {
	if (lineHeight != h) {
		lineHeight = h;
		invalidLayout();
	}
}

void TextView::invalidLayout() {
	layoutDirty = true;
	View::invalidLayout();
}

void TextView::measureText(Canvas* canvas, const char* str, float* bounds) {
	if (!canvas || !canvas->data) {
		bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0;
		return;
	}
	canvas->fontSize(fontSize);
	canvas->fontFace(fontFace.c_str());
	canvas->textBounds(0, 0, str, nullptr, bounds);
}

void TextView::doTextLayout(float maxW, float maxH, Canvas* canvas) {
	lineInfos.clear();
	if (text.empty()) {
		areaX = 0;
		return;
	}

	float actualLineHeight = maxFloat(lineHeight * fontSize, fontSize);

	std::vector<std::string> lines;
	{
		std::string current;
		for (size_t i = 0; i <= text.size(); i++) {
			if (i == text.size() || text[i] == '\n') {
				lines.push_back(current);
				current.clear();
			} else {
				current += text[i];
			}
		}
	}

	int lineCount = 0;
	for (const auto& line : lines) {
		if (maxLine > 0 && lineCount >= maxLine) break;

		if (line.empty()) {
			TextLine li;
			li.text = "";
			li.w = 0;
			li.h = actualLineHeight;
			lineInfos.push_back(li);
			lineCount++;
			continue;
		}

		if (wrap && maxW > 0 && maxW != infinity) {
			std::string current;
			std::string bestFit;
			float bounds[4] = {0};
			for (size_t i = 0; i <= line.size(); i++) {
				if (i == line.size()) {
					TextLine li;
					li.text = current;
					measureText(canvas, current.c_str(), bounds);
					li.w = bounds[2] - bounds[0];
					li.h = actualLineHeight;
					lineInfos.push_back(li);
					current.clear(); 
					lineCount++; 
					break;
				}
				current += line[i];
				measureText(canvas, current.c_str(), bounds);
				float textW = bounds[2] - bounds[0];
				if (textW > maxW && current.size() > 1) {
					if (overflowEllipsis && maxLine > 0 && lineCount >= maxLine - 1) {
						TextLine li;
						std::string ellipsisText = current.substr(0, current.size() - 1) + "..";
						measureText(canvas, ellipsisText.c_str(), bounds);
						li.text = ellipsisText;
						li.w = bounds[2] - bounds[0];
						li.h = actualLineHeight;
						lineInfos.push_back(li);
						lineCount++;
						current.clear();
						break;
					}
					TextLine li;
					li.text = bestFit.empty() ? current.substr(0, current.size() - 1) : bestFit;
					measureText(canvas, li.text.c_str(), bounds);
					li.w = bounds[2] - bounds[0];
					li.h = actualLineHeight;
					lineInfos.push_back(li);
					lineCount++;
					current = std::string(1, line[i]);
					bestFit.clear();
					if (maxLine > 0 && lineCount >= maxLine) break;
				} else {
					bestFit = current;
				}
			}
		} else {
			float bounds[4] = {0};
			measureText(canvas, line.c_str(), bounds);
			TextLine li;
			li.text = line;
			li.w = bounds[2] - bounds[0];
			li.h = actualLineHeight;
			lineInfos.push_back(li);
			lineCount++;
		}
	}

	float y = 0;
	float maxLineWidth = 0;
	for (auto& li : lineInfos) {
		li.y = y;
		y += li.h;
		if (li.w > maxLineWidth) maxLineWidth = li.w;
	}

	if (textAlign == "center") {
		areaX = 0;
		for (auto& li : lineInfos) {
			li.x = (maxLineWidth - li.w) / 2.0f;
		}
	} else if (textAlign == "right") {
		areaX = 0;
		for (auto& li : lineInfos) {
			li.x = maxLineWidth - li.w;
		}
	} else {
		areaX = 0;
		for (auto& li : lineInfos) {
			li.x = 0;
		}
	}
}

void TextView::layout(Frame* ctx) {
	updateFrame_forSelfWidthHeight(ctx);
	initLayoutSize(ctx);

	Window* win = getWindow();
	Canvas* canvas = win ? (Canvas*)win->canvas : nullptr;

	Frame contentCtx = makeContentLayoutCtx(ctx);

	if (layoutDirty) {
		float maxW = contentCtx.maxWidth;
		float maxH = contentCtx.maxHeight;
		doTextLayout(maxW, maxH, canvas);
		layoutDirty = false;
	}

	float textW = 0;
	float textH = 0;
	for (auto& li : lineInfos) {
		if (li.w > textW) textW = li.w;
		textH += li.h;
	}

	contentCtx.setSize(textW, textH);
	updateFrame_byContentCtx(ctx, &contentCtx);
	ctx->saveConstraints();
}

void TextView::draw_self(Canvas* canvas) {
	View::draw_self(canvas);

	if (text.empty() || !canvas || !canvas->data) return;

	canvas->fillColorByInt32(color);
	canvas->fontSize(fontSize);
	canvas->fontFace(fontFace.c_str());
	canvas->textAlign(CANVAS_ALIGN_LEFT );

	float pl = padding.left + border.l.w;
	float pt = padding.top + border.t.w;

	//pt = 0.f;
	auto tm = canvas->textMetrics();
	for (auto& li : lineInfos) {
		canvas->text(li.x + pl + areaX, li.y + pt 
			+ tm.ascender
			//- tm.descender
			, li.text.c_str());
	}
}

void TextView::registerMeta() {
	auto reg = MetaRegistry::instance()->registerClass<TextView, View>();

	reg.property("text", &TextView::text);
	reg.property("fontSize", &TextView::fontSize);
	reg.property("color", &TextView::color);
	reg.property("textAlign", &TextView::textAlign);
	reg.property("lineHeight", &TextView::lineHeight);
	reg.property("wrap", &TextView::wrap);
	reg.property("maxLine", &TextView::maxLine);
	reg.property("overflowEllipsis", &TextView::overflowEllipsis);
	reg.property("fontFace", &TextView::fontFace);
}
