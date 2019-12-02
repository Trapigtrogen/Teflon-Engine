/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <DemoGame.h>
#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <math.h>

namespace engine
{

	float DemoGame::getRandom(int start, int end) {
		return start + rand() % end;
	}

	DemoGame::DemoGame(Window* window, GraphicsSystem* graphics) : GraphicsApplication(window, graphics), m_totalTime(0.0f), m_windowHandle(window->getNativeWindow()) {
		// Load shader files
		std::string vShader = graphics->loadFile("shaders/vertexShader.txt");
		std::string fShader = graphics->loadFile("shaders/fragmentShader.txt");

		// Create Shader object
		quadObject = graphics->createShaderProgram(vShader, fShader);

		// CREATE TEXTURE FROM IMAGE FILE
		int width, height, bits;
		blueTexture = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/blue.png", width, height, bits));
		redTexture = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/red.png", width, height, bits));
		greenTexture = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/green.png", width, height, bits));
		yellowTexture = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/yellow.png", width, height, bits));

		playAreaColumns[0] = window->getWidth() / 12;
		playAreaColumns[1] = window->getWidth() / 6;
		playAreaColumns[2] = window->getWidth() / 4;
		playAreaColumns[3] = window->getWidth() / 3;
		goal = window->getHeight() - 500.0f;
	}

	DemoGame::~DemoGame() {}

	bool DemoGame::update(float deltaTime) {
		m_totalTime += deltaTime;
		speed = m_totalTime * 800;

		// MOUSE INPUT
		posX = getWindow()->input->getMousePosX();
		posY = getWindow()->input->getMousePosY();
		clicked = getWindow()->input->getButton();
		//std::cout << posX << " - " << posY << " - " << clicked << std::endl;

		// KEYBOARD INPUT
		// Close app with ESC
		if (getWindow()->input->getKey(VK_ESCAPE) == 1) {
			SendMessage(m_windowHandle, WM_CLOSE, 0, 0);
		}
		// other keys
		keyPressedX = getWindow()->input->getKey(WM_KEY_X);
		keyPressedZ = getWindow()->input->getKey(WM_KEY_Z);
		keyPressedComma = getWindow()->input->getKey(VK_OEM_COMMA);
		keyPressedDot = getWindow()->input->getKey(VK_OEM_PERIOD);

		if (spawnrate < m_totalTime * 5) {
			float note = getRandom(0, 3);
			notes.push_back(note);
			spawnrate++;
		}

		return true;
	}

	void DemoGame::render(Window* window, GraphicsSystem* graphics) {
		// FPS CAP
		if (i < m_totalTime * 120) {
			(void)window;
			float wave = fabsf(sinf(2.0f * m_totalTime));

			// Clear screen with pulsating colour
			graphics->clearScreen(0, 0, 0, true);

			// Texture coordinates
			GLfloat quadTexCoords[] = {
				0,1,
				0,0,
				1,0,
				1,1,
				1,0,
				0,1
			};

			// Quad information
			float size = 1.0f;
			float dx = -0.5f; //starting corner X
			float dy = -0.5f; //starting corner Y
			float depth = 0.0f; // Z-index

			// Quad vertice coordinates
			GLfloat quad[] = {
				dx + 0.0f,  dy + size, depth,
				dx + 0.0, dy + 0.0f, depth,
				dx + size, dy + 0.0f, depth,
				dx + size, dy + size, depth
			};


			for each (int note in notes) {
				graphics->transform(quadObject, 0, playAreaColumns[note], -100 + speed, 0.0f, 0.0f, 0.0f, 1.0f, 100.0f);
				graphics->drawRectangle(quadObject, blueTexture, quad, quadTexCoords, 6);
			}


			// Goals
			if (!keyPressedZ) {
				graphics->transform(quadObject, 0, playAreaColumns[0], goal, 0.0f, 0.0f, 0.0f, 1.0f, 100.0f);
				graphics->drawRectangle(quadObject, blueTexture, quad, quadTexCoords, 6);
			}
			if (!keyPressedX) {
				graphics->transform(quadObject, 0, playAreaColumns[1], goal, 0.0f, 0.0f, 0.0f, 1.0f, 100.0f);
				graphics->drawRectangle(quadObject, redTexture, quad, quadTexCoords, 6);
			}
			if (!keyPressedComma) {
				graphics->transform(quadObject, 0, playAreaColumns[2], goal, 0.0f, 0.0f, 0.0f, 1.0f, 100.0f);
				graphics->drawRectangle(quadObject, greenTexture, quad, quadTexCoords, 6);
			}
			if (!keyPressedDot) {
				graphics->transform(quadObject, 0, playAreaColumns[3], goal, 0.0f, 0.0f, 0.0f, 1.0f, 100.0f);
				graphics->drawRectangle(quadObject, yellowTexture, quad, quadTexCoords, 6);
			}

			// DAFUQ BUG FIX
			graphics->drawRectangle(quadObject, yellowTexture, quad, quadTexCoords, 6);

			// Swap buffers
			graphics->swapBuffers();
			i++;
		}
	}
}