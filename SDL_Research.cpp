/*
How to add SDL to VSCode http://grafika.me/node/493
*/

#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL run error! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* screenSurface = nullptr;

	SDL_Window* window = nullptr;

	window = SDL_CreateWindow("Hello, SDL 2!", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Window cannot be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 255, 0));

	SDL_UpdateWindowSurface(window);

	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}