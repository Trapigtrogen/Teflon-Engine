#if !defined(_WIN32)

#include <AndroidWindow.h>
#include <graphics/GraphicsApplication.h>

namespace engine
{
	AndroidWindow::AndroidWindow(EGLNativeWindowType nativeWindow)
		: Window()
		, m_hwnd(nativeWindow)
	{
	}


	AndroidWindow::~AndroidWindow()
	{
	}


	EGLNativeWindowType AndroidWindow::getNativeWindow() const
	{
		return m_hwnd;
	}

}



#endif

