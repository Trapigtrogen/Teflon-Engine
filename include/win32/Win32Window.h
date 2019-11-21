/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_WIN32WINDOW_H_
#define _ENGINE_WIN32WINDOW_H_

#include <graphics/Window.h>
#include <windows.h>
#include <string>

namespace engine
{
	class Win32Window :
		public Window
	{
	public:
		Win32Window(int width, int height, const std::wstring& title);
		~Win32Window();

		// Returns native window handle
		virtual EGLNativeWindowType getNativeWindow() const;
		
		// Returns true, if window is still active
		bool updateMessages();
		
	private:
		HWND m_hwnd;
		bool m_active;
	};

}

#endif

