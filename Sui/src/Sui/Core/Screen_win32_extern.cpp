#include "./Screen_orc.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>


#include <Naga/StrUtil.h>
#include <Naga/Utf8Util.h>



SuiCore$Vec2 SuiCore$Screen_get_usable_size() {
    auto w = GetSystemMetrics(SM_CXFULLSCREEN);
    auto h = GetSystemMetrics(SM_CYFULLSCREEN);

    auto ret = SuiCore$mkVec2(0, 0);
    ret.x = w;
    ret.y = h;
    // return (SuiCore$Vec2 *) urgc_set_var_for_return((void**)__outRef__, (void*)ret);
    return ret;
}
SuiCore$Vec2 SuiCore$Screen_get_size() {
    auto w = GetSystemMetrics(SM_CXSCREEN);
    auto h = GetSystemMetrics(SM_CYSCREEN);

    auto ret = SuiCore$mkVec2(0, 0);
    ret.x = w;
    ret.y = h;
    // return (SuiCore$Vec2*)urgc_set_var_for_return((void**)__outRef__, (void*)ret);
    return ret;
}