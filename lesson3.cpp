#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

// Loads an image as a texture on the given renderer
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
		logSDLError(std::cout, "LoadTexture");
	return texture;
}

// Draw a texture to the renderer at x, y, with a given width and height
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	SDL_Rect dst;
	dst.x = x; dst.y = y; dst.w = w; dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

// Draws a texture to the renderer at x, y, without scaling
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

int main(int argc, char** argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		return 2;
	}

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	window = SDL_CreateWindow("Lesson 3", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 4;
	}

	SDL_Texture *background = loadTexture("./res/background.png", renderer);
	SDL_Texture *image = loadTexture("./res/image.png", renderer);
	if (background == nullptr || image == nullptr)
		return 5;

	int xTiles = SCREEN_WIDTH/TILE_SIZE;
	int yTiles = SCREEN_HEIGHT/TILE_SIZE;

	for (int i = 0; i < xTiles * yTiles; i++){
		int x = i % xTiles;
		int y = i / xTiles;
		renderTexture(background, renderer, x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}

	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW/2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(image, renderer, x, y);

	SDL_RenderPresent(renderer);
	SDL_Delay(20000);

	SDL_DestroyTexture(background);
	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}