cmake_minimum_required(VERSION 3.25)

project(Sui)


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
# set(C_STANDARD 11)

# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\bin\\Hostx64\\x64\\link.exe")

include_directories("./build/assimp/include")
include_directories("./assimp/build/include")
include_directories("./assimp/include")
include_directories(lib)
include_directories(src)
include_directories(./)
include_directories(UrgcDll)
include_directories(../miniaudio-master)
# add_compile_options("/utf-8")

add_definitions(-D_CRT_SECURE_NO_WARNINGS )
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
# set(FLAGS "-ftime-trace  -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(FLAGS "-fno-lto  -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
set(WARN_FLAGS "-Wno-int-conversion -Wno-unused-command-line-argument -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(FLAGS "-O0  -fsanitize=address  -fsanitize-recover=address -fno-stack-protector -fno-omit-frame-pointer")
# set(FLAGS "-O0  -Xclang --dependent-lib=libcmt -Xclang --dependent-lib=oldnames")
set(FLAGS "-O0  ")

# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

# lto 链接时优化
# set(FLAGS " -flto -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -fexceptions ${FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions ${FLAGS} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS} ${WARN_FLAGS}")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto ${FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS} ${WARN_FLAGS}")

file(COPY lib/glew32.dll  DESTINATION .)
file(COPY asset  DESTINATION .)





file(GLOB src 
    src/*.cpp
    # src/Main_orc.c
    src/SuiDesignerMain_orc.c
    src/MainProject_orc.c
    # src/*.c  

    src/Json/*.c  
    src/Json/*.cpp

    src/GL/*.c  
    src/GL/*.cpp


    src/nanovg/*.c  
    src/nanovg/*.cpp


    src/Sui/Dialog/*.c  
    src/Sui/Dialog/*.cpp

    src/Sui/Core/Image_orc.c  
    src/Sui/Core/Canvas_orc.c  
    src/Sui/Core/Canvas_extern.cpp
    src/Sui/Core/Fps_orc.c  
    src/Sui/Core/Vec2_orc.c  
    src/Sui/Core/Vec3_orc.c  
    src/Sui/Core/Vec4_orc.c  
    src/Sui/Core/Quat_orc.c  
    src/Sui/Core/Rect_orc.c  
    src/Sui/Core/Plane_orc.c  
    src/Sui/Core/Quaternion_orc.c  
    src/Sui/Core/Triangle_orc.c  
    src/Sui/Core/Spherical_orc.c  
    src/Sui/Core/Mat3_orc.c  
    src/Sui/Core/Line3_orc.c  
    src/Sui/Core/Euler_orc.c  

    src/Sui/Core/Radius_orc.c  
    src/Sui/Core/Inset_orc.c  
    src/Sui/Core/Global_orc.c  
    src/Sui/Core/Event_orc.c  
    src/Sui/Core/Emitter_orc.c  
    src/Sui/Core/Edge_orc.c  
    src/Sui/Core/Cursor_orc.c  
    src/Sui/Core/Cursor_win32_extern.cpp
    src/Sui/Core/Color_orc.c  
    src/Sui/Core/Clipboard_orc.c  
    src/Sui/Core/Clipboard_win32_extern.cpp
    src/Sui/Core/BoxShadow_orc.c  
    src/Sui/Core/Border_orc.c  
    src/Sui/Core/Screen_orc.c  
    src/Sui/Core/Screen_win32_extern.cpp
    src/Sui/Core/Node_orc.c
    src/Sui/Core/Timer_orc.c
    src/Sui/Core/Window_orc.c
    src/Sui/Core/ViewBase_orc.c
    src/Sui/Core/View_orc.c
    src/Sui/Core/Focus_orc.c
    src/Sui/Core/Frame_orc.c
    src/Sui/Core/LayoutCell_orc.c
    src/Sui/Core/Mat2d_orc.c
    src/Sui/Core/App_orc.c
    src/Sui/Core/KeyEvent_orc.c
    src/Sui/Core/MouseEvent_orc.c
    src/Sui/Core/Mouse_orc.c
    src/Sui/Core/Keyboard_orc.c
    src/Sui/Core/App_win32_extern.cpp
    src/Sui/Core/Mouse_win32_extern.cpp
    src/Sui/Core/Mat2d_extern.cpp
    src/Sui/Core/Window_win32_extern.cpp
    src/Sui/Core/NodeLib_orc.c
    src/Sui/Core/Bezier_orc.c
    src/Sui/Core/TestMath_orc.c


    src/Sui/View/Checkbox_orc.c
    src/Sui/View/ColorPalete_orc.c
    src/Sui/View/ColorPicker_orc.c
    src/Sui/View/DockLayout_orc.c
    src/Sui/View/Drag_orc.c
    src/Sui/View/Menu_orc.c
    src/Sui/View/MenuNative_orc.c
    src/Sui/View/MenuNative_win32_extern.cpp
    src/Sui/View/ViewBuilder_orc.c
    src/Sui/View/ImageView_orc.c
    src/Sui/View/HoverViewEffect_orc.c
    src/Sui/View/TextView_orc.c
    src/Sui/View/EditText_orc.c
    src/Sui/View/Button_orc.c
    src/Sui/View/ScrollArea_orc.c
    src/Sui/View/ProgressView_orc.c
    src/Sui/View/Panel_orc.c
    src/Sui/View/Switch_orc.c
    src/Sui/View/Select_orc.c
    src/Sui/View/Slider_orc.c
    src/Sui/View/Splitter_orc.c
    src/Sui/View/TableView_orc.c
    src/Sui/View/TreeView_orc.c
    src/Sui/View/SystemTrayIcon_orc.c
    src/Sui/View/SystemTrayIcon_win32.cpp


    src/Sui/Layout/LayoutLinear_orc.c
    src/Sui/Layout/LayoutGrid_orc.c
    src/Sui/Layout/RowWrap_orc.c
    src/Sui/Layout/LayoutAlign_orc.c


    src/SuiDesigner/BezierEditView_orc.c
    src/SuiDesigner/ANode_orc.c
    src/SuiDesigner/EditCtx_orc.c
    # src/SuiDesigner/Scene_extern.c
    src/SuiDesigner/RegisterNodes_orc.c
    src/SuiDesigner/Insp_orc.c
    src/SuiDesigner/Inspector_orc.c
    src/SuiDesigner/InspectorView_orc.c
    src/SuiDesigner/SglInspectorView_orc.c
    src/SuiDesigner/SglInspView_orc.c
    src/SuiDesigner/Inspector_extern.c
    src/SuiDesigner/Serial/BiJson_orc.c
    src/SuiDesigner/Serial/BiJson_extern.cpp
    # src/SuiDesigner/Asset/Asset_orc.c
    src/SuiDesigner/Asset/FileWatcher_orc.c
    src/SuiDesigner/Asset/FileWatcher.cpp
    src/SuiDesigner/Theme_orc.c
    src/SuiDesigner/DrawDegree_orc.c
    src/SuiDesigner/ProjectMgr_orc.c
    src/SuiDesigner/FileItem_orc.c
    src/SuiDesigner/EventFileItemChanged_orc.c
    src/SuiDesigner/EventANodeChanged_orc.c
    src/SuiDesigner/UiAction_orc.c
    src/SuiDesigner/Prefab_orc.c
    src/SuiDesigner/Project_orc.c
    src/SuiDesigner/Gizmo_orc.c
    src/SuiDesigner/SglGizmo_orc.c
    src/SuiDesigner/ToolBase_orc.c
    src/SuiDesigner/SceneView_orc.c
    src/SuiDesigner/SceneHierView_orc.c
    src/SuiDesigner/SglSceneHierView_orc.c
    src/SuiDesigner/SglEditCtx_orc.c
    src/SuiDesigner/Asset/AssetDirView_orc.c
    src/SuiDesigner/Asset/AssetDirTreeView_orc.c
    src/SuiDesigner/ChessBgViewCallback_orc.c
    src/SuiDesigner/FileChooser_orc.c
    src/SuiDesigner/SpriteSheetEditor_orc.c
    src/SuiDesigner/InvalidReact_orc.c
    src/SuiDesigner/TileEditor_orc.c
    src/SuiDesigner/W3eEditor_orc.c
    src/SuiDesigner/W3e_orc.c
    src/SuiDesigner/SglEditor_orc.c
    src/SuiDesigner/MdxReader_orc.c
    src/SuiDesigner/MenuBarCtrl_orc.c


    src/Sgl/Sgl_orc.c
    src/Sgl/PixelsReader_orc.c
    src/Sgl/Vbo_orc.c
    src/Sgl/Ray_orc.c
    src/Sgl/Vbo_extern.cpp
    src/Sgl/Vao_orc.c
    src/Sgl/Vao_extern.cpp
    src/Sgl/Fbo_orc.c
    src/Sgl/Fbo_extern.cpp
    src/Sgl/Program_orc.c
    src/Sgl/Program_extern.cpp
    src/Sgl/Material_orc.c
    src/Sgl/Material_extern.cpp
    src/Sgl/Geometry_orc.c
    src/Sgl/Geometry_extern.cpp
    src/Sgl/GeometryHeightMap_orc.c
    src/Sgl/GeometryBox_orc.c
    src/Sgl/GeometryTorus_orc.c
    src/Sgl/GeometryLine_orc.c
    src/Sgl/GeometryPlane_orc.c
    src/Sgl/GeometryRect_orc.c
    src/Sgl/GeometryCylinder_orc.c
    src/Sgl/GeometryCone_orc.c
    src/Sgl/GeometrySphere_orc.c
    src/Sgl/GeometryCircle_orc.c
    src/Sgl/GeometryRing_orc.c
    src/Sgl/GeometryArrow_orc.c
    src/Sgl/Draw_orc.c
    src/Sgl/Draw_extern.cpp
    src/Sgl/Draw_orc.c
    src/Sgl/Buffer_orc.c
    src/Sgl/Buffer_extern.cpp
    src/Sgl/Sgl_extern.cpp
    src/Sgl/OutlineFx_orc.c
    src/Sgl/GeometryFullscreenQuad_orc.c

    src/Sgl/Tex2d_extern.cpp
    src/Sgl/Tex2d_orc.c
    src/Sgl/Mat_orc.c

    src/Sgl/Obj3d_orc.c
    src/Sgl/SglSceneView_orc.c
    src/Sgl/DrawCtx_orc.c
    src/Sgl/Scene_orc.c
    src/Sgl/Camera_orc.c
    src/Sgl/PerspectiveCamera_orc.c
    src/Sgl/Light_orc.c
    src/Sgl/PointLight_orc.c
    src/Sgl/DirLight_orc.c
    src/Sgl/SpotLight_orc.c
    src/Sgl/Mesh_orc.c
    src/Sgl/Billboard_orc.c
    src/Sgl/SkinMesh_orc.c
    src/Sgl/Bone_orc.c
    src/Sgl/Skybox_orc.c
    src/Sgl/Particle_orc.c

    src/Sgl/Box2_orc.c
    src/Sgl/Box3_orc.c
    src/Sgl/Ray_orc.c
    src/Sgl/Raycaster_orc.c
    src/Sgl/Sphere_orc.c

    src/HoroEditor/Horo3dSceneView_orc.c
    src/HoroEditor/HoroEditor_orc.c
    src/HoroEditor/HoroEditCtx_orc.c
    src/HoroEditor/HoroSceneHierView_orc.c
    src/HoroEditor/HoroInspView_orc.c
    src/HoroEditor/UiAct_orc.c

    # src/testTgfx.cpp

    # src/Orc/*.c
    # src/Orc/*.cpp
    )

# add_definitions(-D_CRT=)
# add_definitions(-DURGC_DLLAPI=)

file(GLOB orcSrc 
    ./src/Orc/*.cpp
    ./src/Orc/*.c  
    )


add_executable(Sui 
    ${src}
    # resource.rc 
)


add_subdirectory(UrgcDll)
add_subdirectory(Naga)

# ADD_LIBRARY(UrgcDll SHARED ${UrgcDll_Src})


# target_link_directories(Sui PRIVATE
#                 "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/Llvm/x64/lib/clang/17/lib/windows"
#                 )


# target_link_options(Sui PRIVATE /wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib)

# ADD_SUBDIRECTORY(assimp)

target_link_directories(Sui PRIVATE 
    lib
    "build/assimp/lib"
    )

target_link_libraries(Sui 

    # clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64
    # asan
    Orc
    UrgcDll Naga 

    opengl32
    glu32
    glew32
    # tgfx

    assimp
    miniaudio
    

    # -fsanitize=address
    )

# ADD_LIBRARY(Orc SHARED ${orcSrc})
ADD_LIBRARY(Orc STATIC ${orcSrc})
target_link_libraries(Orc UrgcDll Naga)


set_target_properties(UrgcDll PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

set_target_properties(Naga PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)