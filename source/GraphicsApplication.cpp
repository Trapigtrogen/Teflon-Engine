/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <graphics/GraphicsApplication.h>
#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <stdio.h>
#include <math.h> // sinf
#include <random>

namespace engine
{
	GraphicsApplication::GraphicsApplication(Window* window, GraphicsSystem* graphics) : Object() , m_window(window) , m_graphics(graphics)	{}


	GraphicsApplication::~GraphicsApplication()	{}


	GraphicsSystem* GraphicsApplication::getGraphicsSystem() {
		return m_graphics;
	}

	
	Window* GraphicsApplication::getWindow() {
		return m_window;
	}
}