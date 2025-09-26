# win32 多窗口与opengl渲染


有以下方案：
* 一个窗口一个opengl上下文
* 多个窗口共用同一个opengl上下文

实测 HGLRC可以多窗口共用同一个。


如果是一个窗口一个opengl上下文，通常需要资源共享，如纹理。
可以创建共享的opengl上下文，然后把资源创建到共享的opengl上下文中


OpenGL 中的共享上下文 https://zhuanlan.zhihu.com/p/444440326