/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <graphics/Window.h>

namespace engine
{

	Window::Window() : Object(), m_app(0), m_graphics(0){
		input = new InputManager();
		functions = new Functionality();
		srand(time(NULL));
	}
	
	Window::~Window(){}
	
	int Window::getWidth() const{
		return m_width;
	}


	int Window::getHeight() const{
		return m_height;
	}


	void Window::setSize(int w, int h){
		m_width = w;
		m_height = h;
	}


	void Window::setApplication(GraphicsApplication* app)
	{
		m_app = app;
	}


	void Window::setGraphics(GraphicsSystem* graphics)
	{
		m_graphics = graphics;
	}


	GraphicsApplication* Window::getApplication() const
	{
		return m_app;
	}


	GraphicsSystem* Window::getGraphics() const
	{
		return m_graphics;
	}
}