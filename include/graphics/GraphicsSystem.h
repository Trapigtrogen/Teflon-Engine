/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_GRAPHICSSYSTEM_H_
#define _ENGINE_GRAPHICSSYSTEM_H_

#include <core/Object.h>
#include <stdint.h>
#include <string>
#include <OGL/OGL.h>

namespace engine
{
	class Texture2D {
	public:
		Texture2D() {}
		virtual ~Texture2D() {}
		virtual GLuint getTextureId() = 0;
	};

	class GraphicsSystem : public Object {
	public:
		GraphicsSystem();
		virtual ~GraphicsSystem();

		// Clears the screen using given color
		virtual void clearScreen(float red, float green, float blue, bool setViewport) = 0;

		// Load shaders from file
		virtual std::string loadFile(const std::string fileName) = 0;

		// Load texture from file
		virtual GLubyte* loadImage(const char* fileName, int &width, int &height, int &bits) = 0;

		// Translate Object
		virtual void transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ) = 0;
		virtual void transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale) = 0;

		// Method for swapping backbuffer to screen.
		virtual void swapBuffers() = 0;

		virtual GLuint createShaderProgram(const std::string vertexShader, const std::string fragmentShader) = 0;
		virtual GLuint createShaderProgram() = 0;

		virtual void drawTriangles(GLuint shader, Texture2D* texture, float vertices[], float textureCoords[], int numVertices) = 0;
		virtual void drawRectangle(GLuint shader, Texture2D* texture, float vertices[], float textureCoords[], int numVertices) = 0;
		virtual void drawSprite(GLuint shader, Texture2D* texture) = 0;
		virtual void drawSprite(GLuint shader, Texture2D* texture, float vertices[]) = 0;
	};

}

#endif

