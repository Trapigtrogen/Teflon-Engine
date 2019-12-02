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

namespace engine
{
	class Window;
	class GraphicsSystem;

	class DemoGame : public GraphicsApplication {
	public:
		int i;
		float spawnrate;
		float playAreaColumns[4];

		GLuint quadObject;

		DemoGame(Window* window, GraphicsSystem* graphics);

		~DemoGame();

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime);

		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics);

		float getRandom(int start, int end);

	private:
		HWND m_windowHandle;
		float m_totalTime;

		std::vector<float> notes;
		float goal;
		float treshold;
		float speed;

		int posX;
		int posY;
		int clicked;

		int keyPressedZ;
		int keyPressedX;
		int keyPressedComma;
		int keyPressedDot;

		OGLTexture2D* blueTexture;
		OGLTexture2D* redTexture;
		OGLTexture2D* greenTexture;
		OGLTexture2D* yellowTexture;
	};

}

#endif

