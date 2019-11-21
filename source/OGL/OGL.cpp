/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <OGL/OGL.h>
#include <core/Log.h>
#include <assert.h>

namespace engine
{
	void checkOpenGL()
	{
#if defined(_DEBUG) || defined(ANDROID)
		GLenum test = glGetError();
		if (test != GL_NO_ERROR)
		{
			switch (test)
			{
			case GL_INVALID_ENUM:
				LOGE("gl error: GL_INVALID_ENUM\n");
				break;

			case GL_INVALID_VALUE:
				LOGE("gl error: GL_INVALID_VALUE\n");
				break;

			case GL_INVALID_OPERATION:
				LOGE("gl error: GL_INVALID_OPERATION\n");
				break;

			case GL_OUT_OF_MEMORY:
				LOGE("gl error: GL_OUT_OF_MEMORY\n");
				break;

			default:
			{
				LOGE("gl error: %X\n", test);
			}
			}
		}
		assert(test == GL_NO_ERROR);
#endif
	}

}



