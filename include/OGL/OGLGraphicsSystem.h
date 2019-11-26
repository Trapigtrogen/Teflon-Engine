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


namespace engine
{
	class OGLShader : public Shader {
	public:
		OGLShader(const char* strVertexShader, const char* strFragmentShader, const std::vector<std::string>& attribLocations);
		virtual ~OGLShader();

		virtual void useShader();
		virtual GLuint getUniformLocation(const char* const uniformName);

	private:
		GLuint m_programObject;
	};
	
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
		// Creates new OpenGL ES 2.0 Graphics System binded to given window.
		OGLGraphicsSystem(Window* window);
		virtual ~OGLGraphicsSystem();

		virtual void clearScreen(float red, float green, float blue, bool setViewport);

		// Load shaders from file
		virtual std::string loadFile(const std::string fileName);

		
		// Load textures from file
		virtual GLubyte* loadImage(const char* fileName, int &width, int &height, int &bits);
		

		virtual void swapBuffers();

		virtual GLuint createShaderProgram(const std::string vertexShader, const std::string fragmentShader);
		
		void OGLGraphicsSystem::drawTriangles(GLuint shader, Texture2D* texture, float vertices[], float textureCoords[], int numVertices);
		void OGLGraphicsSystem::drawRectangle(GLuint shader, Texture2D* texture, float vertices[], float textureCoords[], int numVertices);

	private:
		engine::Ref<Window> m_window;	// Window where graphics is binded
		bool m_active;					// True-flag if all is okay.
		GLuint programObject;

		// Embedded OpenGLES member variables
		EGLDisplay m_eglDisplay; // Display object
		EGLContext m_eglContext; // Context object
		EGLSurface m_eglSurface; // Surface object
	};

}

#endif


