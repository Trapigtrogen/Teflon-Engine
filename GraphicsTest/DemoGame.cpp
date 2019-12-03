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
		notesTextures[0] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/noteBlue.png", width, height, bits));
		notesTextures[1] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/noteRed.png", width, height, bits));
		notesTextures[2] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/noteGreen.png", width, height, bits));
		notesTextures[3] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/noteYellow.png", width, height, bits));
		
		scoreTextures[0] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score0.png", width, height, bits));
		scoreTextures[1] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score1.png", width, height, bits));
		scoreTextures[2] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score2.png", width, height, bits));
		scoreTextures[3] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score3.png", width, height, bits));
		scoreTextures[4] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score4.png", width, height, bits));
		scoreTextures[5] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score5.png", width, height, bits));
		scoreTextures[6] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score6.png", width, height, bits));
		scoreTextures[7] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score7.png", width, height, bits));
		scoreTextures[8] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score8.png", width, height, bits));
		scoreTextures[9] = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/score9.png", width, height, bits));

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

		// Note spawner
		if (spawnTimer < m_totalTime * 5) {
			int id = getRandom(0, 4);
			Note* note = new Note;
			note->id = id;
			note->location = -100.0f;
			notes.push_back(note);
			spawnTimer++;
		}

		// Note speed. values set in header
		if (m_totalTime / acceleration < minSpeed) { // Minimum speed
			speed = minSpeed;
		}
		else if (m_totalTime / acceleration > maxSpeed) { // Maximum speed
			speed = maxSpeed;
		}
		else {
			speed = m_totalTime / acceleration;
		}

		// Score calculating
		while (combo > 0) {
			score1++;
			combo--;
			if (score1 > 9) {
				score10++;
				score1 -= 10;
				
			}
			if (score10 > 9) {
				score100++;
				score10 -= 10;

			}
			if (score100 > 9) {
				score1000++;
				score100 -= 10;
			}
			if (score1000 > 8) {
				score1000 = 9;
			}
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
			
			// Note remover
			it = notes.begin();
			while(it != notes.end()){
				int index = std::distance(notes.begin(), it);
				notes[index]->location += speed;
				graphics->transform(quadObject, 0, playAreaColumns[notes[index]->id], notes[index]->location, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
				graphics->drawRectangle(quadObject, (notesTextures[notes[index]->id]), quad, quadTexCoords, 6);

				// Remove notes that are out of screen
				if (notes[index]->location > (window->getHeight() + 200.0f)) {
					combo = 0;
					score1 = 0;
					score10 = 0;
					score100 = 0;
					score1000 = 0;
					it = notes.erase(it);
				}

				// Remove notes when they are hit
				if (keyPressedZ && notes[index]->id == 0 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold) {
					combo++;
					it = notes.erase(it);
				}
				if (keyPressedX && notes[index]->id == 1 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold) {
					combo++;
					it = notes.erase(it);
				}
				if (keyPressedComma && notes[index]->id == 2 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold) {
					combo++;
					it = notes.erase(it);
				}
				if (keyPressedDot && notes[index]->id == 3 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold) {
					combo++;
					it = notes.erase(it);
				}
				else {
					it++;
				}
			}

			// Score
			graphics->transform(quadObject, 0, scoreStartX, scoreStartY, -1.0f, 0.0f, 0.0f, 1.0f, scoreSize);
			graphics->drawRectangle(quadObject, scoreTextures[score1000], quad, quadTexCoords, 6);
			graphics->transform(quadObject, 0, scoreStartX + scorePadding, scoreStartY, -1.0f, 0.0f, 0.0f, 1.0f, scoreSize);
			graphics->drawRectangle(quadObject, scoreTextures[score100], quad, quadTexCoords, 6);
			graphics->transform(quadObject, 0, scoreStartX + scorePadding * 2, scoreStartY, -1.0f, 0.0f, 0.0f, 1.0f, scoreSize);
			graphics->drawRectangle(quadObject, scoreTextures[score10], quad, quadTexCoords, 6);
			graphics->transform(quadObject, 0, scoreStartX + scorePadding * 3, scoreStartY, -1.0f, 0.0f, 0.0f, 1.0f, scoreSize);
			graphics->drawRectangle(quadObject, scoreTextures[score1], quad, quadTexCoords, 6);

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

			// DAFUQ BUG FIX: For some reason on my laptop hte program ignores the last draw call.
			//                This is to fix that untill I figure out why it happens in the first place.
			graphics->drawRectangle(quadObject, notesTextures[3], quad, quadTexCoords, 6);

			// Swap buffers
			graphics->swapBuffers();
			i++;
		}
	}
}