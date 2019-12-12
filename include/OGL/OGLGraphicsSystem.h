/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_OGLGRAPHICSSYSTEM_H_
#define _ENGINE_OGLGRAPHICSSYSTEM_H_

#include <graphics/GraphicsSystem.h>
#include <core/Ref.h>
#include <EGL/egl.h>
#include <OGL/OGL.h>
#include <vector> // std::vector
#include <stdint.h>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace engine
{
	class OGLTexture2D : public Texture2D, Object {
	public:
		OGLTexture2D(int width, int height, int bytesPerPixel, const GLubyte* pixels);
		virtual ~OGLTexture2D();

		GLuint getTextureId();

	private:
		GLuint m_textureId;
	};

	// Forward declare Window-class
	class Window;

	class OGLGraphicsSystem : public GraphicsSystem {
	public:
		// Creates new OpenGL ES Graphics System binded to given window.
		OGLGraphicsSystem(Window* window);
		virtual ~OGLGraphicsSystem();

		virtual void clearScreen(float red, float green, float blue, bool setViewport);

		// Load shaders from file
		virtual std::string loadFile(const std::string fileName);

		
		// Load textures from file
		virtual GLubyte* loadImage(const char* fileName, int &width, int &height, int &bits);

		virtual void transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
		virtual void transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale);
		
		virtual void swapBuffers();

		virtual GLuint createShaderProgram(const std::string vertexShader, const std::string fragmentShader);
		virtual GLuint createShaderProgram();
		
		virtual void drawTriangles(GLuint shader, Texture2D* texture, float vertices[], float textureCoords[], int numVertices);
		virtual void drawRectangle(GLuint shader, Texture2D* texture, float vertices[], float textureCoords[], int numVertices);
		virtual void drawSprite(GLuint shader, Texture2D* texture);
		virtual void drawSprite(GLuint shader, Texture2D* texture, float vertices[12]);

	private:
		engine::Ref<Window> m_window;	// Window where graphics is binded
		bool m_active;					// True-flag if all is okay.
		GLuint programObject;

		// Default shaders
		const char shaderFDefault[198] =
			"precision mediump float;\n"
			"uniform sampler2D texture;\n"
			"varying vec2 texCoord;\n"
			"void main() {\n"
				"vec4 color = texture2D(texture, texCoord);\n"
				"if (color.w < 0.9) {\n"
					"discard;\n"
					"}\n"
					"else {\n"
					"gl_FragColor = color;\n"
				"}\n"
			"}\n";

		const char shaderVDefault[162] =
			"attribute vec4 vPosition;\n"
			"uniform mat4 MVP;\n"
			"attribute vec2 vTexCoord;\n"
			"varying vec2 texCoord;\n"
			"void main() {\n"
				"gl_Position = MVP * vPosition;\n"
				"texCoord = vTexCoord;\n"
			"}";

		// Default texture coordinates for sprites
		GLfloat spriteTexCoords[12] = {
			0,1,
			0,0,
			1,0,
			1,1,
			1,0,
			0,1
		};

		// Default sprite information
		float size = 1.0f;
		float dx = -0.5f; //starting corner X
		float dy = -0.5f; //starting corner Y
		float depth = 0.0f; // Z-index

		// Default sprite vertice coordinates
		GLfloat spriteVertices[12] = {
			dx + 0.0f,  dy + size, depth,
			dx + 0.0f, dy + 0.0f, depth,
			dx + size, dy + 0.0f, depth,
			dx + size, dy + size, depth
		};

		// Embedded OpenGLES member variables
		EGLDisplay m_eglDisplay; // Display object
		EGLContext m_eglContext; // Context object
		EGLSurface m_eglSurface; // Surface object

		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_model;
	};

}

#endif


