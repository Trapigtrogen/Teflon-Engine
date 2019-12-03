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
#include <time.h>

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
		notesTextures[0] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/blue.png", width, height, bits));
		notesTextures[1] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/red.png", width, height, bits));
		notesTextures[2] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/green.png", width, height, bits));
		notesTextures[3] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/yellow.png", width, height, bits));

		playAreaColumns[0] = window->getWidth() / 7;			 // Blue
		playAreaColumns[1] = playAreaColumns[0] + columnPadding; // Red
		playAreaColumns[2] = playAreaColumns[1] + columnPadding; // Green
		playAreaColumns[3] = playAreaColumns[2] + columnPadding; // Yellow
		goal = window->getHeight() - 500.0f;

		srand(time(NULL));
	}

	DemoGame::~DemoGame() {}

	bool DemoGame::update(float deltaTime) {
		m_totalTime += deltaTime;
		// Note timing. values set in header
		if (m_totalTime/acceleration < minSpeed) { // Minimum speed
			speed = minSpeed;
		}
		else if (m_totalTime/acceleration > maxSpeed) { // Maximum speed
			speed = maxSpeed;
		}
		else {
			speed = m_totalTime / acceleration;
		}

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

		if (spawnTimer < m_totalTime * 5) {
			int id = getRandom(0, 4);
			Note* note = new Note;
			note->id = id;
			note->location = -100.0f;
			notes.push_back(note);
			spawnTimer++;
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

			for (std::vector<Note*>::iterator it = notes.begin(); it != notes.end(); ++it) {
				int index = std::distance(notes.begin(), it);
				notes[index]->location += speed;
				//std::cout << notes[index] << " - " << notes[index]->id  << " - " << notes[index]->location << std::endl;
				graphics->transform(quadObject, 0, playAreaColumns[notes[index]->id], notes[index]->location, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
				graphics->drawRectangle(quadObject, (notesTextures[notes[index]->id]), quad, quadTexCoords, 6);
				if (notes[index]->location > 1000) {
					//notes.erase(notes.begin() + index);
				}
			}
	

			// Goals
			if (!keyPressedZ) {
				graphics->transform(quadObject, 0, playAreaColumns[0], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 10);
				graphics->drawRectangle(quadObject, notesTextures[0], quad, quadTexCoords, 6);
			}
			if (!keyPressedX) {
				graphics->transform(quadObject, 0, playAreaColumns[1], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 10);
				graphics->drawRectangle(quadObject, notesTextures[1], quad, quadTexCoords, 6);
			}
			if (!keyPressedComma) {
				graphics->transform(quadObject, 0, playAreaColumns[2], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 10);
				graphics->drawRectangle(quadObject, notesTextures[2], quad, quadTexCoords, 6);
			}
			if (!keyPressedDot) {
				graphics->transform(quadObject, 0, playAreaColumns[3], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 10);
				graphics->drawRectangle(quadObject, notesTextures[3], quad, quadTexCoords, 6);
			}

			// DAFUQ BUG FIX
			graphics->drawRectangle(quadObject, notesTextures[3], quad, quadTexCoords, 6);

			// Swap buffers
			graphics->swapBuffers();
			i++;
		}
	}
}