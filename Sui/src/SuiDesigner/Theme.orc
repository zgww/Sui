
package SuiDesigner




// 主题
class Theme {

    //文本色
    int colorLabel = 0xff333333;
    int colorDesc = 0xff666666;

    int c_main = 0xff007aff;//0xff3634a3;

    //背景色层次
    int bg1 = 0xffe5e5e5;
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
    int dock_head_c = 0xff666666

    // docklayout tab背景色
    int dock_headbar_bg = 0xffd1d1d6

    // docklayout tab背景色
    int dock_head_bg = 0x00000030
    //选中的tab背景色
    int dock_head_bg_active = 0x99fafafa
    int dock_content_bg = 0xe5e5e5
}


static Theme @theme = null
Theme* themeIns(){
    if theme == null {
        theme = new Theme()
    }
    return theme
}
