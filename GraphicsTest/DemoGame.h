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
#include <Note.h>

namespace engine
{
	class Window;
	class GraphicsSystem;

	class DemoGame : public GraphicsApplication {
	public:
		DemoGame(Window* window, GraphicsSystem* graphics);

		~DemoGame();

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime);

		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics);

		float getRandom(int start, int end);

	private:
		HWND m_windowHandle;
		float m_totalTime = 0;

		std::vector<Note*> notes;
		float goal = 0;
		float treshold = 0;
		float speed = 0;
		float acceleration = 10;
		float minSpeed = 5;
		float maxSpeed = 15;

		int posX = 0;
		int posY = 0;
		int clicked = 0;

		int keyPressedZ = 0;
		int keyPressedX = 0;
		int keyPressedComma = 0;
		int keyPressedDot = 0;

		float noteSize = 70.0f;
		float columnPadding = 80;

		int i = 0;
		float spawnTimer = 0;
		float playAreaColumns[4];
		OGLTexture2D* notesTextures[4];

		// Texture coordinates
		GLfloat quadTexCoords[12] = {
			0,1,
			0,0,
			1,0,
			1,1,
			1,0,
			0,1
		};

		GLuint quadObject;
	};

}

#endif

