# 完整opengl窗口创建流程，支持半透明窗口，msaa



* 创建辅助窗口
* setpixelformat 使窗口支持opengl
* 如果要开启半透明窗口，就需要在AlphaBuffer设置为8， 启用alpha 缓冲区， dwm才会生效。 而且只有第一次SetPixelFormat才会生效。 **有没有alpha**在第一次SetPixelFormat就决定了。
* 创建临时的context,用来调用wglGetProcAddress，此函数用来获取  进一步操作所需要的wgl ARB扩展函数
* 获取wglarb扩展函数
* 删除临时的wglcontext
* 找到最匹配的pixelformat并设置setPixelFormat
* 使用wglCreateContextAttribsARB 创建wgl context


如果只是想要半透明，在设置Pixelformat时，选择带有alpha buffer bit=8的format,然后使用dwm启用，即可有半透明的效果

**启用dwm**最好是在设置完pixelformat之后，不然有些windows版本不生效


如果想要msaa，需要先创建临时的窗口，先加载wglarb, 调用wglChoosePixelFormatARB选择带有
            WGL_SAMPLE_BUFFERS_ARB, 1,           // 启用多重采样
            WGL_SAMPLES_ARB, 4,                  // 4x MSAA（可改为 2, 8 等）
的pixelformat,  再到主窗口调用SetPixelFormat(刚刚的带msaa的pixelformat)。 
SetPixelFormat只有第一次生效，后续设置不同的pixelformat都会返回失败。  所以需要创建临时窗口。这是 Win32 OpenGL 编程中一个经典且必须掌握的技巧

渲染时启用 glEnable（GL_MULTISAMPLE）


# 无边窗口,展开窗口，鼠标穿透

glfw使用分层窗口实现。
godot使用SetWindowRgn实现。直接指定窗口的范围。支持多边形。这方案更简单？？

## 查询pixelformat的属性

```c++
// 加载扩展函数
wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)
    wglGetProcAddress("wglGetPixelFormatAttribivARB");

int attrib = WGL_SAMPLES_ARB;
int vals = 0;
wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &vals);

attrib = WGL_SAMPLE_BUFFERS_ARB;
int valsSampleBuffers = 0;
wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsSampleBuffers);

attrib = WGL_STENCIL_BITS_ARB;
int valsWGL_STENCIL_BITS_ARB = 0;
wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsWGL_STENCIL_BITS_ARB);

attrib = WGL_DEPTH_BITS_ARB;
int valsWGL_DEPTH_BITS_ARB = 0;
wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsWGL_DEPTH_BITS_ARB);

attrib = WGL_COLOR_BITS_ARB;
int valsWGL_COLOR_BITS_ARB = 0;
wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsWGL_COLOR_BITS_ARB);

```


demo工程详见WglPixelFormat