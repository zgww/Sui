#include "Fps.h"
#include "Canvas.h"

void Fps::endFrame() {
	endMs = time_unixMs();
	drawCostMs = drawEndMs - drawStartMs;
	layoutCostMs = layoutEndMs - layoutStartMs;
	costMs = endMs - startMs;
	fps = costMs > 0 ? 1000.0f / (float)costMs : 1000.0f;
	layoutFps = layoutCostMs > 0 ? 1000.0f / (float)layoutCostMs : 1000.0f;
	drawFps = drawCostMs > 0 ? 1000.0f / (float)drawCostMs : 1000.0f;
}

void Fps::draw(Canvas* canvas, int h) {
	canvas->save();
	canvas->translate(0, (float)h - 30);

	char text[60];
	snprintf(text, sizeof(text), "fps:%.1f/%.1f/%.1f", fps, layoutFps, drawFps);

	canvas->fillColor(0, 0, 0, 64);
	canvas->beginPath();
	canvas->rect(0, 0, 200, 30);
	canvas->fill();

	canvas->fillColor(255, 255, 255, 255);
	canvas->text(6, 12, text);

	snprintf(text, sizeof(text), "ms:%lld/%lld/%lld", (long long)costMs, (long long)layoutCostMs, (long long)drawCostMs);
	canvas->text(6, 26, text);
	canvas->restore();
}
