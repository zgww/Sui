#include "Rect.h"


Rect Rect::containsPositionIn5Patch(float px, float py, Rect centerRect) {
	Rect ret = containsPositionIn5Patch_withOutType(
		px, py, centerRect, nullptr);
	return ret;
}

//是否包含位置在9宫格内
// 0 0 0
// 1 2 3
// 4 4 4
// -1 表示 不包含
// [centerRect]表示中间区域，以比例的方式表示
// [return] 返回以比例表示的rect
Rect Rect::containsPositionIn5Patch_withOutType(float px, float py, Rect centerRect, int* outType) {
	if (outType) {
		*outType = -1;
	}

	if (w == 0 || h == 0 || !containsPosition(px, py)) {
		return mkRect(-1, -1, -1, -1);
	}
	float dx = px - x;
	float dy = py - y;

	float x = dx / w;
	float y = dy / h;

	float x1 = centerRect.x;
	float x2 = centerRect.x + centerRect.w;
	float y1 = centerRect.y;
	float y2 = centerRect.y + centerRect.h;
	if (y < y1) {
		if (outType) {
			*outType = 0;
		}
		return mkRect(0, 0, 1, y1);
	}
	else if (y < y2) {
		if (x < x1) {
			if (outType) {
				*outType = 1;
			}
			return mkRect(0, y1, x1, centerRect.h);
		}
		else if (x < x2) {
			if (outType) {
				*outType = 2;
			}
			return mkRect(x1, y1, centerRect.w, centerRect.h);

		}
		else {
			if (outType) {
				*outType = 3;
			}
			return mkRect(x2, y1, 1.0 - x2, centerRect.h);
		}
	}
	else {
		if (outType) {
			*outType = 4;
		}
		return mkRect(0, y2, 1, 1.0 - y2);
	}
}

//是否包含位置在9宫格内
// 0 1 2
// 3 4 5
// 6 7 8
// -1 表示 不包含
Vec2 Rect::containsPositionIn9Patch(float px, float py) {
	if (!containsPosition(px, py)) {
		return mkVec2(-1, -1);
	}
	float dx = px - x;
	float dy = py - y;
	float w0_3 = 1 / 3.0 * w;
	float h0_3 = 1 / 3.0 * h;
	if (dx < w0_3) {
		if (dy < h0_3) {
			return mkVec2(0, 0);
		}
		if (dy < h0_3 * 2) {
			// return 3
			return mkVec2(0, 1);
		}
		if (dy < h0_3 * 3) {
			// return 6
			return mkVec2(0, 2);
		}
	}
	if (dx < w0_3 * 2) {
		if (dy < h0_3) {
			// return 1
			return mkVec2(1, 0);
		}
		if (dy < h0_3 * 2) {
			// return 4
			return mkVec2(1, 1);
		}
		if (dy < h0_3 * 3) {
			// return 7
			return mkVec2(1, 2);
		}
	}

	if (dy < h0_3) {
		// return 2
		return mkVec2(2, 0);
	}
	if (dy < h0_3 * 2) {
		// return 5
		return mkVec2(2, 1);
	}
	if (dy < h0_3 * 3) {
		// return 8
		return mkVec2(2, 2);
	}
	// return -1
	return mkVec2(-1, -1);
}
