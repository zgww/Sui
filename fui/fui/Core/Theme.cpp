#include "Theme.h"

//static Ref<Theme> theme
Theme* themeIns() {
    static Theme ins;
    return &ins;
    //if theme == null{
    //    theme = new Theme()
    //}
    //    return theme
}
