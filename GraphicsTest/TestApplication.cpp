/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <TestApplication.h>
#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <math.h>

namespace engine
{

	TestApplication::TestApplication(Window* window, GraphicsSystem* graphics) : GraphicsApplication(window, graphics) , m_totalTime(0.0f), m_windowHandle(window->getNativeWindow()) {
		// Load shader files
		std::string vShader = window->functions->loadFile("shaders/vertexShader.txt");
		std::string fShader = window->functions->loadFile("shaders/fragmentShader.txt");
		
		// Create Shader object
		quadObject = graphics->createShaderProgram(vShader, fShader);

		// CREATE TEXTURE FROM IMAGE FILE
		int width, height, bits;
		quadTexture = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/blue.png", width, height, bits));
		quadTexture2 = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/green.png", width, height, bits));
		quadTexture3 = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/red.png", width, height, bits));
		quadTexture4 = new OGLTexture2D(width, height, bits, graphics->loadImage("textures/yellow.png", width, height, bits));
	}

	TestApplication::~TestApplication() {}

	bool TestApplication::update(float deltaTime) {
		m_totalTime += deltaTime;

		// MOUSE INPUT
		posX = getWindow()->input->getMousePosX();
		posY = getWindow()->input->getMousePosY();
		clicked = getWindow()->input->getButton();
		//std::cout << posX << " - " << posY << " - " << clicked << std::endl;

		// KEYBOARD INPUT
		// Close app with ESC
		if(getWindow()->input->getKey(VK_ESCAPE) == 1) {
			SendMessage(m_windowHandle, WM_CLOSE, 0, 0);
		}
		// other keys
		keyPressedX = getWindow()->input->getKey(WM_KEY_X);
		keyPressedZ = getWindow()->input->getKey(WM_KEY_Z);

		return true;
	}

	void TestApplication::render(Window* window, GraphicsSystem* graphics) {
		(void)window;	
		float wave = fabsf(sinf(2.0f*m_totalTime));

		// Clear screen with pulsating colour
		graphics->clearScreen(wave/4, wave, wave/1.4, true);

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

		// Vertices for quad
		GLfloat quad[] = {
			dx + 0.0f,  dy + size, depth,
			dx + 0.0f, dy + 0.0f, depth,
			dx + size, dy + 0.0f, depth,

			dx + size, dy + size, depth,
			dx + size, dy + 0.0f, depth,
			dx + 0.0f, dy + size, depth
		};

		// User friendly quad
		GLfloat quad2[] = {
			dx + 0.0f,  dy + size, depth,
			dx + 0.0f, dy + 0.0f, depth,
			dx + size, dy + 0.0f, depth,
			dx + size, dy + size, depth
		};

		if (clicked && posX < window->getWidth()*0.5 && posY < window->getHeight()*0.5) {
			graphics->transform(quadObject, m_totalTime, 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 300.0f);
			graphics->drawRectangle(quadObject, quadTexture2, quad2, quadTexCoords, 6);
		}
		else {
			graphics->transform(quadObject, m_totalTime, 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 200.0f);
			graphics->drawRectangle(quadObject, quadTexture, quad2, quadTexCoords, 6);
		}
		graphics->transform(quadObject, m_totalTime, 400.0f, (600 + 300 * -wave), 0.0f, 0.0f, 0.0f, -0.5f, 100.0f);
		graphics->drawRectangle(quadObject, quadTexture3, quad2, quadTexCoords, 6);

		if (keyPressedX || keyPressedZ) {
			graphics->transform(quadObject, m_totalTime, 600.0f, (300 * wave), 0.0f, 0.0f, 0.0f, -0.5f, 100.0f);
			graphics->drawRectangle(quadObject, quadTexture4, quad2, quadTexCoords, 6);
		}


		// DAFUQ BUG FIX
		graphics->drawRectangle(quadObject, quadTexture3, quad2, quadTexCoords, 6);

		// Swap buffers
		graphics->swapBuffers();
	}
}