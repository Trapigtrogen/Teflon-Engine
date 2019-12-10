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

	private:
		HWND m_windowHandle;
		float m_totalTime = 0;
		std::vector<Note*>::iterator it;

		std::vector<Note*> notes;
		float noteSize = 70.0f;
		float columnPadding = 80;

		float scoreSize = 30.0f;
		float scoreStartX = 50;
		float scoreStartY = 50;
		float scorePadding = 30;
		int combo = 0;
		int score1000 = 0;
		int score100 = 0;
		int score10 = 0;
		int score1 = 0;

		float goal = 0;
		float treshold = 50;
		float speed = 0;
		float acceleration = 9; // smaller = faster
		float minSpeed = 7;
		float maxSpeed = 25;

		bool keyPressed[4] = {0, 0, 0, 0};
		bool keyReleased[4] = {true, true, true, true};
		bool hasLost = false;

		int i = 0;
		float spawnTimer = 0;
		float playAreaColumns[4];
		OGLTexture2D* notesTextures[4];
		OGLTexture2D* scoreTextures[10];
		OGLTexture2D* losingScreen;

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

