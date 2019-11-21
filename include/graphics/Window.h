/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_WINDOW_H_
#define _ENGINE_WINDOW_H_

#include <core/Object.h>
#include <EGL/eglplatform.h> // TODO: Make to cross platform

namespace engine
{
	// Forward declate Application and Graphics -classes.
	class GraphicsApplication;
	class GraphicsSystem;

	// Window-class
	class Window : public Object {
	public:
		Window();
		~Window();

		virtual EGLNativeWindowType getNativeWindow() const = 0;
		
		void setSize(int w, int h);
		int getWidth() const;
		int getHeight() const;

		void setApplication(GraphicsApplication* app);
		void setGraphics(GraphicsSystem* graphics);

		GraphicsApplication* getApplication() const;
		GraphicsSystem* getGraphics() const;


	private:
		int m_width;
		int m_height;
		GraphicsApplication*	m_app;
		GraphicsSystem*		m_graphics;
	};

}
#endif


