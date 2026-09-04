#include "TextView.h"
#include "../Core/Window.h"
#include "../Core/Canvas.h"
#include "../Core/App.h"
#include "../Meta/MetaRegistry.h"

// 返回 s 中从 i（位于合法字符边界）开始的 UTF-8 字符的字节长度；非法字节按 1 处理，避免越界
static int utf8CharLen(const std::string& s, size_t i) {
	unsigned char c = (unsigned char)s[i];
	if (c < 0x80) return 1;
	if ((c & 0xE0) == 0xC0) return 2;
	if ((c & 0xF0) == 0xE0) return 3;
	if ((c & 0xF8) == 0xF0) return 4;
	return 1;
}

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
	//for (const auto& line : lines) {
	for (int i = 0; i < lines.size(); i++){
		auto& line = lines[i];
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
			// 按 UTF-8 码点拆分，避免多字节字符（中文等）被逐字节拆断后产生非法序列导致测量崩溃
			std::vector<std::string> chars;
			for (size_t i = 0; i < line.size(); ) {
				int len = utf8CharLen(line, i);
				if (len < 1 || i + (size_t)len > line.size()) len = 1;
				chars.push_back(line.substr(i, len));
				i += len;
			}

			std::string current;
			std::string bestFit;
			float bounds[4] = {0};
			size_t ci = 0;
			while (true) {
				if (ci == chars.size()) {
					if (!current.empty()) {
						TextLine li;
						li.text = current;
						measureText(canvas, current.c_str(), bounds);
						li.w = bounds[2] - bounds[0];
						li.h = actualLineHeight;
						lineInfos.push_back(li);
						lineCount++;
					}
					break;
				}

				const std::string& ch = chars[ci];
				current += ch;
				measureText(canvas, current.c_str(), bounds);
				float textW = bounds[2] - bounds[0];

				if (textW > maxW && current.size() > ch.size()) {
					if (overflowEllipsis && maxLine > 0 && lineCount >= maxLine - 1) {
						std::string fit = bestFit.empty() ? current.substr(0, current.size() - ch.size()) : bestFit;
						TextLine li;
						std::string ellipsisText = fit + "..";
						measureText(canvas, ellipsisText.c_str(), bounds);
						li.text = ellipsisText;
						li.w = bounds[2] - bounds[0];
						li.h = actualLineHeight;
						lineInfos.push_back(li);
						lineCount++;
						break;
					}

					TextLine li;
					li.text = bestFit.empty() ? current.substr(0, current.size() - ch.size()) : bestFit;
					measureText(canvas, li.text.c_str(), bounds);
					li.w = bounds[2] - bounds[0];
					li.h = actualLineHeight;
					lineInfos.push_back(li);
					lineCount++;

					current = ch;
					bestFit.clear();
					ci++;
					if (maxLine > 0 && lineCount >= maxLine) break;
				} else {
					bestFit = current;
					ci++;
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
