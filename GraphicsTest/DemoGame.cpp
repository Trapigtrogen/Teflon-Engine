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

	DemoGame::DemoGame(Window* window, GraphicsSystem* graphics) : GraphicsApplication(window, graphics), m_totalTime(0.0f), m_windowHandle(window->getNativeWindow()) {
		// Create Shader object
		quadObject = graphics->createShaderProgram();

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

		losingScreen = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/notePink.png", width, height, bits));

		playAreaColumns[0] = window->getWidth() / 7;			 // Blue
		playAreaColumns[1] = playAreaColumns[0] + columnPadding; // Red
		playAreaColumns[2] = playAreaColumns[1] + columnPadding; // Green
		playAreaColumns[3] = playAreaColumns[2] + columnPadding; // Yellow
		goal = window->getHeight() - 500.0f;
	}

	DemoGame::~DemoGame() {}

	bool DemoGame::update(float deltaTime) {
		m_totalTime += deltaTime;

		// KEYBOARD INPUT
		// Close app with ESC
		if (getWindow()->input->getKey(VK_ESCAPE) == 1) {
			SendMessage(m_windowHandle, WM_CLOSE, 0, 0);
		}
		// other keys
		keyPressed[0] = getWindow()->input->getKey(WM_KEY_Z);
		keyPressed[1] = getWindow()->input->getKey(WM_KEY_X);
		keyPressed[2] = getWindow()->input->getKey(VK_OEM_COMMA);
		keyPressed[3] = getWindow()->input->getKey(VK_OEM_PERIOD);
		for (int i = 0; i < 4; i++) {
			if (keyPressed[i] == false) {
				keyReleased[i] = true;
			}
		}

		// Note spawner
		if (spawnTimer < m_totalTime * 5 + (speed/5) && !hasLost) {
			int id = getWindow()->functions->getRandomInt(0, 4);
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
		score1 = combo % 10;
		score10 = combo / 10 % 10;
		score100 = combo / 100 % 10;
		score1000 = combo / 1000 % 10;

		return true;
	}

	void DemoGame::render(Window* window, GraphicsSystem* graphics) {
		// FPS CAP
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
			
		GLfloat quad2[] = {
			dx + 0.0f,  dy + size, depth,
			dx + 0.0, dy + 0.0f, depth,
			dx + (size*2), dy + 0.0f, depth,
			dx + (size*2), dy + size, depth
		};
			
		// Note remover
		it = notes.begin();
		while(it != notes.end()){
			int index = std::distance(notes.begin(), it);
			notes[index]->location += speed;
			graphics->transform(quadObject, 0, playAreaColumns[notes[index]->id], notes[index]->location, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
			graphics->drawRectangle(quadObject, (notesTextures[notes[index]->id]), quad, quadTexCoords, 6);

			// Remove notes that are out of screen
			if (notes[index]->location > (goal + treshold + 30.0f)) {
				hasLost = true;
				notes.clear();
				it = notes.begin();
			}

			// Remove notes when they are hit
			if (keyPressed[0] && notes[index]->id == 0 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold/2 && keyReleased[0] == true) {
				combo++;
				keyReleased[0] = false;
				it = notes.erase(it);
			}
			if (keyPressed[1] && notes[index]->id == 1 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold/2 && keyReleased[1] == true) {
				combo++;
				keyReleased[1] = false;
				it = notes.erase(it);
			}
			if (keyPressed[2] && notes[index]->id == 2 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold/2 && keyReleased[2] == true) {
				combo++;
				keyReleased[2] = false;
				it = notes.erase(it);
			}
			if (keyPressed[3] && notes[index]->id == 3 && notes[index]->location < goal + treshold && notes[index]->location > goal - treshold/2 && keyReleased[3] == true) {
				combo++;
				keyReleased[3] = false;
				it = notes.erase(it);
			}
			else if (!hasLost) {
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
		if (!keyPressed[0] && !hasLost) {
			graphics->transform(quadObject, 0, playAreaColumns[0], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 20);
		}
		else {
			graphics->transform(quadObject, 0, playAreaColumns[0], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
		}
		graphics->drawRectangle(quadObject, notesTextures[0], quad, quadTexCoords, 6);
		if (!keyPressed[1] && !hasLost) {
			graphics->transform(quadObject, 0, playAreaColumns[1], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 20);
		}
		else {
			graphics->transform(quadObject, 0, playAreaColumns[1], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
		}
		graphics->drawRectangle(quadObject, notesTextures[1], quad, quadTexCoords, 6);
		if (!keyPressed[2] && !hasLost) {
			graphics->transform(quadObject, 0, playAreaColumns[2], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 20);
		}
		else {
			graphics->transform(quadObject, 0, playAreaColumns[2], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
		}
		graphics->drawRectangle(quadObject, notesTextures[2], quad, quadTexCoords, 6);
		if (!keyPressed[3] && !hasLost) {
			graphics->transform(quadObject, 0, playAreaColumns[3], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize + 20);
		}
		else {
			graphics->transform(quadObject, 0, playAreaColumns[3], goal, 0.0f, 0.0f, 0.0f, 1.0f, noteSize);
		}
		graphics->drawRectangle(quadObject, notesTextures[3], quad, quadTexCoords, 6);

		if (hasLost) {
			graphics->transform(quadObject, 0, 300, 200, 0.0f, 0.0f, 0.0f, 1.0f, 100);
			graphics->drawRectangle(quadObject, losingScreen, quad2, quadTexCoords, 6);
			if (keyPressed[0] || keyPressed[1] || keyPressed[2] || keyPressed[3]) {
				combo = 0;
				hasLost = false;
				spawnTimer = 0;
				m_totalTime = 0;
				it = notes.begin();
			}
		}


		// DAFUQ BUG FIX: For some reason on my laptop hte program ignores the last draw call.
		//                This is to fix that untill I figure out why it happens in the first place.
		graphics->drawRectangle(quadObject, notesTextures[3], quad, quadTexCoords, 6);

		// Swap buffers
		graphics->swapBuffers();
	}
}