
package SuiDesigner




// 主题
class Theme {

    //文本色
    int colorLabel = 0xff333333;
    int colorDesc = 0xff666666;

    // edittext
    int textview_color = 0xb5f1f7fe
    int textview_bg = 0x00000000
    int textview_fontSize = 12

    // edittext
    int edittext_color = 0xb5f1f7fe
    int edittext_bg = 0x1dd3edf8
    int edittext_caretColor = 0xb5f1f7fe
    int edittext_fontSize = 12

    int c_main = 0xff007aff;//0xff3634a3;

    //背景色层次
    int bg1 = 0xff18191b;//0xffe5e5e5;
    int bg2 = 0xfff2f2f2;

    // 菜单栏的背景
    int menubar_bg = 0xff2c2c2e

    // 工具栏的背景
    int toolbar_bg = 
    // 0xffc7c7cc
    // 0xffd1d1d6
    // 0xffff0000 
    0xffe5e5ea

    // 工具栏菜单按钮的颜色
    int toolbar_menubutton_bg = 0x00000000;
    int toolbar_menubutton_bg_hover = 0x339c9c9c;

    int splitLine_c1 = 0xffd8d8d8;
    int splitLine_c2 = 0xffe5e5e5;


    //正文字号
    int fs1 = 10;
    int fs2 = 12;
    int fs3 = 14;

    // 标题字号
    int fs_h1 = 16;
    int fs_h2 = 18;


    // docklayout tab 标题文本
    int dock_head_c = 0xffedeef0// 0xff666666

    // docklayout tab背景色
    int dock_headbar_bg = 0xff2e3135//0x00d1d1d6

    // docklayout tab背景色
    int dock_head_bg = 0x00000000//0x00000030
    //选中的tab背景色
    int dock_head_bg_active = 0xff212225 //0x990000fa
    int dock_content_bg = 0xe5e5e5
    int dock_splitterBg = 0x25d9edfe
    int dock_splitterBgHover = 0xff007aff


    //按钮
    int button_bg = 0x14ddeaf8
    int button_bgHover = 0x1dd3edf8
    int button_bgActive = 0xff0090ff// 0x2dd3edf8
    int button_fontSize = 12
    int button_color = 0xb5f1f7fe
    int button_colorHover = 0xeffcfdff
    int button_colorActive = 0xffffffff

    int button_primary_bg = 0xff0090ff
    int button_primary_bgHover = 0xff3b9eff
    int button_primary_color = 0xffffffff


    // sceneHierView
    int hier_color = 0xffb0b4ba
    int hier_fontSize = 12

    /// dirTree
    int dirTree_bg = 0xff212225;
    int dirTree_color = 0xffb0b4ba
    int dirTree_fontSize = 12

    /// dir
    int dir_bg = 0xff212225;
    int dir_color = 0xffb0b4ba
    int dir_fontSize = 12

    // panel
    int panel_titleColor = 0xb5f1f7fe
    int panel_titleFontSize = 12

    // insp
    int insp_color = 0xff777b84
    int insp_fontSize = 12
    int insp_panelTitleColor = 0xb5f1f7fe

    // scrollbar
    int scrollbar_bg = 0x00ffffff
    int scrollbar_barBg = 0x33ffffff
    int scrollbar_size = 4
}


static Theme @theme = null
Theme* themeIns(){
    if theme == null {
        theme = new Theme()
    }
    return theme
}
