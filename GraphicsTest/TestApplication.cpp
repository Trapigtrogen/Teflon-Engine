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

	TestApplication::TestApplication(Window* window, GraphicsSystem* graphics) : GraphicsApplication(window, graphics) , m_totalTime(0.0f) {
		// Load shader files
		std::string vShader = graphics->loadFile("shaders/vertexShader.txt");
		std::string fShader = graphics->loadFile("shaders/fragmentShader.txt");
		
		// Create Shader object
		quadObject = graphics->createShaderProgram(vShader, fShader);
	}

	TestApplication::~TestApplication() {}

	bool TestApplication::update(float deltaTime) {
		m_totalTime += deltaTime;
		return true;
	}

	void TestApplication::render(Window* window, GraphicsSystem* graphics) {
		(void)window;	
		float val = fabsf(sinf(2.0f*m_totalTime));
		float val2 = fabsf(sinf(2.0f*m_totalTime/2));
		float offset = 0.2f;

		// Clear screen with pulsating colour
		graphics->clearScreen(val/4, val, val/1.4, true);
			   
		float size = 1.0f;
		float dx = -0.5f;
		float dy = -0.5f;
		float depth = 0.0f;
		GLfloat quad[] = { 
			dx + 0.0f,  dy + size, depth,
			dx + 0.0f, dy + 0.0f, depth,
			dx + size, dy + 0.0f, depth,

			dx + size, dy + size, depth,
			dx + size, dy + 0.0f, depth,
			dx + 0.0f, dy + size, depth
		};
		
		GLfloat quad2[] = { // quad from four corners only
			dx + 0.0f, dy + size, depth,
			dx + 0.0f, dy + 0.0f, depth,
			dx + size, dy + 0.0f, depth,
			dx + size, dy + size, depth

		};

		GLfloat quadTexCoords[] = {
			0,0,
			0,1,
			1,1,
			1,0,
			1,1,
			0,0
		};

		int width, height, bits;
		GLubyte* texture = graphics->loadImage("textures/texture.jpg", width, height, bits);

		OGLTexture2D quadTexture(width, height, bits, texture);

		//graphics->drawTriangles(quadObject, &quadTexture, quad, quadTexCoords, 6);
		graphics->drawRectangle(quadObject, &quadTexture, quad2, quadTexCoords, 6);

		// Swap buffers
		graphics->swapBuffers();
	}
}