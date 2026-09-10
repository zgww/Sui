#include "Theme.h"

#include <rttr/registration>

//static Ref<Theme> theme
Theme* themeIns() {
    static Theme ins;
    return &ins;
    //if theme == null{
    //    theme = new Theme()
    //}
    //    return theme
}
RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Theme>("Theme")
		.constructor<>()(policy::ctor::as_object)
		.property("colorLabel", &Theme::colorLabel)
		.property("colorDesc", &Theme::colorDesc)
		.property("textview_color", &Theme::textview_color)
		.property("textview_bg", &Theme::textview_bg)
		.property("textview_fontSize", &Theme::textview_fontSize)
		.property("edittext_color", &Theme::edittext_color)
		.property("edittext_bg", &Theme::edittext_bg)
		.property("edittext_caretColor", &Theme::edittext_caretColor)
		.property("edittext_fontSize", &Theme::edittext_fontSize)
		.property("c_main", &Theme::c_main)
		.property("bg1", &Theme::bg1)
		.property("bg2", &Theme::bg2)
		.property("menubar_bg", &Theme::menubar_bg)
		.property("toolbar_bg", &Theme::toolbar_bg)
		.property("toolbar_menubutton_bg", &Theme::toolbar_menubutton_bg)
		.property("toolbar_menubutton_bg_hover", &Theme::toolbar_menubutton_bg_hover)
		.property("splitLine_c1", &Theme::splitLine_c1)
		.property("splitLine_c2", &Theme::splitLine_c2)
		.property("fs1", &Theme::fs1)
		.property("fs2", &Theme::fs2)
		.property("fs3", &Theme::fs3)
		.property("fs_h1", &Theme::fs_h1)
		.property("fs_h2", &Theme::fs_h2)
		.property("dock_head_c", &Theme::dock_head_c)
		.property("dock_headbar_bg", &Theme::dock_headbar_bg)
		.property("dock_head_bg", &Theme::dock_head_bg)
		.property("dock_head_bg_active", &Theme::dock_head_bg_active)
		.property("dock_content_bg", &Theme::dock_content_bg)
		.property("dock_splitterBg", &Theme::dock_splitterBg)
		.property("dock_splitterBgHover", &Theme::dock_splitterBgHover)
		.property("button_bg", &Theme::button_bg)
		.property("button_bgHover", &Theme::button_bgHover)
		.property("button_bgActive", &Theme::button_bgActive)
		.property("button_fontSize", &Theme::button_fontSize)
		.property("button_color", &Theme::button_color)
		.property("button_colorHover", &Theme::button_colorHover)
		.property("button_colorActive", &Theme::button_colorActive)
		.property("button_primary_bg", &Theme::button_primary_bg)
		.property("button_primary_bgHover", &Theme::button_primary_bgHover)
		.property("button_primary_color", &Theme::button_primary_color)
		.property("hier_color", &Theme::hier_color)
		.property("hier_fontSize", &Theme::hier_fontSize)
		.property("dirTree_bg", &Theme::dirTree_bg)
		.property("dirTree_color", &Theme::dirTree_color)
		.property("dirTree_fontSize", &Theme::dirTree_fontSize)
		.property("dir_bg", &Theme::dir_bg)
		.property("dir_color", &Theme::dir_color)
		.property("dir_fontSize", &Theme::dir_fontSize)
		.property("panel_titleColor", &Theme::panel_titleColor)
		.property("panel_titleFontSize", &Theme::panel_titleFontSize)
		.property("insp_color", &Theme::insp_color)
		.property("insp_fontSize", &Theme::insp_fontSize)
		.property("insp_panelTitleColor", &Theme::insp_panelTitleColor)
		.property("scrollbar_bg", &Theme::scrollbar_bg)
		.property("scrollbar_barBg", &Theme::scrollbar_barBg)
		.property("scrollbar_size", &Theme::scrollbar_size);
}
