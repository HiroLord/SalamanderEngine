#include <iostream>

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>

int main(int argc, char *argv[]) {
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init SDL" << std::endl;
		SDL_Quit();
		return -1;
	}
	//GL Version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	//Double buffering with 24bit Z buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//Create window
	mainWindow = SDL_CreateWindow(
						"SalamanderEngine",
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						512,
						512,
						SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!mainWindow) {
		std::cout << "Failed to create window" << std::endl;
		SDL_Quit();
		return -1;
	}

	mainContext = SDL_GL_CreateContext(mainWindow);

	//Buffer swap synced with monitor referesh
	SDL_GL_SetSwapInterval(1);

	/* WOO GL TIME */
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mainWindow);
	SDL_Delay(2000);

	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mainWindow);
	SDL_Delay(2000);

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mainWindow);
	SDL_Delay(2000);

	/* Clean up! */
	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}