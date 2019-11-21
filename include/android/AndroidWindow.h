#ifndef _ENGINE_ANDROIDWINDOW_H_
#define _ENGINE_ANDROIDWINDOW_H_
#if !defined(_WIN32)

#include <graphics/Window.h>
#include <android_native_app_glue.h>
#include <string>

namespace engine
{
	class AndroidWindow :
		public Window
	{
	public:
		AndroidWindow(EGLNativeWindowType nativeWindow);
		~AndroidWindow();

		// Returns native window handle
		virtual EGLNativeWindowType getNativeWindow() const;
	
	private:
		EGLNativeWindowType m_hwnd;
	};

}

#endif

#endif

