/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <win32/Win32Window.h>
#include <core/Ref.h>
#include <OGL/OGLGraphicsSystem.h>
#include <DemoGame.h>
#include <core/ElapsedTimer.h>
#include <stdio.h>
#include <stdlib.h>
#include <core/Log.h>

int main(int argc, char* argv[]) {
	//fclose(stdout);
	int w = 1800;
	int h = 1000;
	wchar_t buffer[150];
	LOGI("Application create window (%d, %d)\n", w, h );
	//fopen(stdout);

	engine::Ref<engine::Win32Window> window = new engine::Win32Window( w, h, L"Engine test application" );

	engine::Ref<engine::OGLGraphicsSystem> graphics = new engine::OGLGraphicsSystem(window);
	window->setGraphics(graphics); // Set graphics for window
	engine::Ref<engine::GraphicsApplication> application = new engine::DemoGame(window, graphics);
	window->setApplication(application); // Set application for window
	
	engine::ElapsedTimer frameTimer;
	frameTimer.reset();
	while (window->updateMessages())
	{
		// updateMessages palautta true. P�ivit� peli�.
		float deltaTime = frameTimer.getTime();
		frameTimer.reset();
		application->update(deltaTime);

		swprintf(buffer, 150, L"FPS: %d", (int)(1.0f / deltaTime));
		SetWindowText(window->getNativeWindow(), (LPCTSTR)buffer);
	}

	LOGI("Application done!\n");
	return 0;
}





