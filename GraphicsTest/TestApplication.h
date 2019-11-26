/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_TEST_APPLICATION_H_
#define _ENGINE_TEST_APPLICATION_H_

#include <graphics/GraphicsApplication.h>
#include <core/Log.h>
#include <OGL/OGL.h>
#include <OGL/OGLGraphicsSystem.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
	class Window;
	class GraphicsSystem;
	
	class TestApplication :	public GraphicsApplication {
	public:
		GLuint quadObject;
		GLuint quadObject2;

		TestApplication(Window* window, GraphicsSystem* graphics);

		~TestApplication();

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime);
		
		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics);

	private:
		float m_totalTime;
		int posX;
		int posY;
		int isClicked;
		OGLTexture2D* quadTexture;
		OGLTexture2D* quadTexture2;
		OGLTexture2D* quadTexture3;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_model;
	};

}

#endif

