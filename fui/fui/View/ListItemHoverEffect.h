#pragma once

#include "HoverViewEffect.h"

// 列表项悬停/选中效果。
// 行为与 HoverViewEffect 一致（普通/hover/active 三态背景与边框），额外提供“单选互斥”：
// 当本 ItemView 进入 hover 或 active(选中) 时，会取消同一父容器下其他兄弟项的 active 状态，
// 使同一时刻最多只有一个列表项处于选中态。
class ListItemHoverEffect : public HoverViewEffect {
public:
	// 左键点击后是否自动置为 active(选中)，默认开启（单选列表语义）
	bool selectOnClick = true;
	// 是否与同级兄弟项互斥（清除其他项 active），默认开启
	bool exclusive = true;

	void onMounted() override;
	void applyEffect() override;

	// 清除同级其他 ListItemHoverEffect 的 active 并复位其视觉
	void clearSiblingsActive();

	virtual const char* getClassName() const override { return "ListItemHoverEffect"; }

	RTTR_ENABLE(HoverViewEffect)
};
