/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_APPLICATION_H_
#define _ENGINE_APPLICATION_H_

#include <core/Object.h>

namespace engine
{
	class Window;
	class GraphicsSystem;
	

	class GraphicsApplication :	public Object {
	public:
		GraphicsApplication(Window* window, GraphicsSystem* graphics);

		virtual ~GraphicsApplication();

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime) = 0;
		
		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics) = 0;

		GraphicsSystem* getGraphicsSystem();
		Window* getWindow();
	private:
		Window* m_window;
		GraphicsSystem* m_graphics;
	};

}

#endif

