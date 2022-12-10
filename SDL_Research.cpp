/*
https://lazyfoo.net/tutorials/SDL/index.php
*/

//Lesson 1
/*
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

	SDL_Surface* screenSurface = nullptrptr;

	SDL_Window* window = nullptrptr;

	window = SDL_CreateWindow("Hello, SDL 2!", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Window cannot be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	SDL_FillRect(screenSurface, nullptrptr, SDL_MapRGB(screenSurface->format, 0, 255, 0));

	SDL_UpdateWindowSurface(window);

	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
*/

//Lesson 2
/*
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptrptr;
SDL_Surface* screenSurface = nullptrptr;
SDL_Surface* image = nullptrptr;

int init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL run error! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Getting an Image on the Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Window cannot be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	return 0;
}

int load()
{
	image = SDL_LoadBMP("smile.bmp");

	if (!image)
	{
		std::cout << "File error! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	return 0;
}

void quit()
{
	SDL_FreeSurface(image);
	image = nullptrptr;

	SDL_DestroyWindow(window);

	SDL_Quit();
}

int main(int argc, char** args)
{
	if (init() == 1)
	{
		return 1;
	}

	if (load() == 1)
	{
		return 1;
	}

	SDL_BlitSurface(image, nullptrptr, screenSurface, nullptrptr);

	SDL_UpdateWindowSurface(window);

	SDL_Delay(2000);

	quit();

	return 0;
};
*/

//Lesson 3
/*
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptrptr;
SDL_Surface* screenSurface = nullptrptr;
SDL_Surface* john = nullptrptr;

int init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL run error! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Getting an Image on the Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Window cannot be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	return 0;
}

int load()
{
	john = SDL_LoadBMP("among-us.bmp"); //smile.bmp HelloWorld.png

	if (!john)
	{
		std::cout << "File error! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	return 0;
}

int quit()
{
	SDL_FreeSurface(john);
	john = nullptrptr;

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

int main(int argc, char** args)
{
	if (init() == 1)
	{
		return 1;
	}

	if (load() == 1)
	{
		return 1;
	}

	bool run = true;
	SDL_Event e;
	SDL_Rect r;

	int x = 0;
	int y = 0;

	r.x = x;
	r.y = y;

	while (run)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				run = false;
			}

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_UP)
				{
					y -= 1;
				}
				if (e.key.keysym.sym == SDLK_DOWN)
				{
					y += 1;
				}
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					x += 1;
				}
				if (e.key.keysym.sym == SDLK_LEFT)
				{
					x -= 1;
				}
			}
		}
		r.x = x;
		r.y = y;

		SDL_FillRect(screenSurface, nullptrptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));

		SDL_BlitSurface(john, nullptrptr, screenSurface, &r);

		SDL_UpdateWindowSurface(window);
	}
	return quit();
}
*/

//Lesson 4

/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*//*

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
//#include <stdio.h>
#include <iostream>
//#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = nullptrptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptrptr;

//Current displayed PNG image
SDL_Surface* gPNGSurface = nullptrptr;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL run error! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!gWindow)
		{
			std::cout << "Window cannot be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = loadSurface("loaded.png");
	if (!gPNGSurface)
	{
		std::cout << "Failed to load PNG image!" << std::endl;
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = nullptrptr;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptrptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = nullptrptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
	{
		std::cout << "Unable to load image: "  << path << std::endl;
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (!optimizedSurface)
		{
			std::cout << "Unable to optimize image: " << path << std::endl;
			std::cout << "SDL Error: "<< SDL_GetError() << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//Apply the PNG image
				SDL_BlitSurface(gPNGSurface, nullptrptr, gScreenSurface, nullptrptr);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
*/

//Lesson 4(2)

/*
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = nullptr;
SDL_Surface* scr = nullptr;
SDL_Surface* flower = nullptr;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Can't init video: " << SDL_GetError() << std::endl;
		return false;
	}

	int flags = IMG_INIT_PNG;
	/*
	SDL_INIT_PNG;
	SDL_INIT_JPG;
	SDL_INIT_TIF;
	*//*
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "Can't init image: " << IMG_GetError() << std::endl;
		return false;
	}

	win = SDL_CreateWindow("Displaying PNG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!win)
	{
		std::cout << "Can't create window: " << SDL_GetError() << std::endl;
		return false;
	}

	scr = SDL_GetWindowSurface(win);

	return true;
}

bool load()
{
	flower = IMG_Load("flower.png");
	if (flower == nullptr)
	{
		std::cout << "Can't load: " << IMG_GetError() << std::endl;
		return false;
	}

	flower = SDL_ConvertSurface(flower, scr->format, 0);
	if (flower == nullptr)
	{
		std::cout << "Can't convert: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void quit()
{
	SDL_FreeSurface(flower);

	SDL_FreeSurface(scr);
	SDL_DestroyWindow(win);

	SDL_Quit();
	IMG_Quit();
}

int main(int argc, char** args)
{
	if (!init())
	{
		system("pause");
		quit();
		return 1;
	}

	if (!load())
	{
		system("pause");
		quit();
		return 1;
	}

	SDL_Rect bg_flower;
	bg_flower.w = SCREEN_WIDTH;
	bg_flower.h = SCREEN_HEIGHT;
	bg_flower.x = 0;
	bg_flower.y = 0;

	SDL_BlitScaled(flower, NULL, scr, &bg_flower);

	SDL_UpdateWindowSurface(win);

	SDL_Delay(2000);

	quit();

	return 0;
}
*/

//Lesson 5
/*
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture* flower = NULL;

bool init()
{
	bool ok = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "Can't init: " << SDL_GetError() << endl;
		ok = false;
	}

	win = SDL_CreateWindow("Текстуры", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		cout << "Can't create window: " << SDL_GetError() << endl;
		ok = false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/*
	SDL_RENDERER_SOFTWARE;
	SDL_RENDERER_ACCELERATED;
	SDL_RENDERER_PRESENTVSYNC;
	SDL_RENDERER_TARGETTEXTURE.
	*//*
	if (ren == NULL)
	{
		cout << "Can't create renderer: " << SDL_GetError() << endl;
		ok = false;
	}
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		cout << "Can't init image: " << IMG_GetError() << endl;
		ok = false;
	}

	return ok;
}

bool load()
{
	bool ok = true;
	SDL_Surface* temp_surf = NULL;
	temp_surf = IMG_Load("flower.png");
	if (temp_surf == NULL)
	{
		cout << "Can't load image: " << IMG_GetError() << endl;
		ok = false;
	}

	flower = SDL_CreateTextureFromSurface(ren, temp_surf);
	if (flower == NULL)
	{
		cout << "Can't create texture from surface: " << SDL_GetError() << endl;
		ok = false;
	}

	return ok;
}

void quit()
{
	SDL_DestroyWindow(win);
	win = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	SDL_DestroyTexture(flower);
	flower = NULL;

	SDL_Quit();
	IMG_Quit();
}

int main(int argc, char** argv)
{

	if (!init())
	{
		quit();
		return 1;
	}
	if (!load())
	{
		quit();
		return 1;
	}

	bool run = true;
	SDL_Event e;

	while (run)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				run = false;
			}
		}
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, flower, NULL, NULL);
		SDL_RenderPresent(ren);
	}
	quit();
	return 0;
}
*/

//Lesson 6
/*
#include <SDL.h>
#include <iostream>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

bool init()
{
	bool ok = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
	}

	win = SDL_CreateWindow("Primitives", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		std::cout << "Can't create window: " << SDL_GetError() << std::endl;
		ok = false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
		ok = false;
	}
	return ok;
}

void quit()
{
	SDL_DestroyWindow(win);
	win = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	SDL_Quit;
}

int main(int arhc, char** argv)
{
	if (!init())
	{
		quit();
		system("pause");
		return 1;
	}
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_Rect rect1 = { 10, 10, 50, 50 };
	SDL_RenderFillRect(ren, &rect1);

	SDL_Rect rect2 = { 70, 10, 50, 50 };
	SDL_RenderDrawRect(ren, &rect2);

	SDL_RenderDrawLine(ren, 10, 70, 640 - 10, 70);

	for (int i = 10; i <= 640 - 10; i += 4)
	{
		SDL_RenderDrawPoint(ren, i, 90);
	}

	SDL_RenderPresent(ren);

	SDL_Delay(5000);

	quit();
	return 0;
}
*/

//Lesson 7
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_SIZE[2] = { 640, 480 };

SDL_Window* window = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture* flower = NULL;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "Can't init IMG: " << IMG_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow("VIEWPORT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE[0], SCREEN_SIZE[1], SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Can't create window: " << SDL_GetError() << std::endl;
		return false;
	}
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool load()
{
	SDL_Surface* temp_surf = NULL;
	temp_surf = IMG_Load("flower.png");
	if (temp_surf == NULL)
	{
		std::cout << "Can't load image: " << IMG_GetError() << std::endl;
		return false;
	}
	flower = SDL_CreateTextureFromSurface(ren, temp_surf);
	if (flower == NULL)
	{
		std::cout << "Can't create texture from surface: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(temp_surf);
		temp_surf = NULL;
		return false;
	}
	return true;
}

void quit()
{
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	SDL_DestroyTexture(flower);
	flower = NULL;

	SDL_Quit();
	IMG_Quit();
}

int main(int arhc, char** argv)
{
	if (!init())
	{
		quit();
		return 1;
	}
	if (!load())
	{
		quit();
		return 1;
	}

	SDL_Rect top_vp = { 0, 0, SCREEN_SIZE[0], SCREEN_SIZE[1] / 2 };
	SDL_Rect bottom_vp = { 0, SCREEN_SIZE[1] / 2, SCREEN_SIZE[0], SCREEN_SIZE[1] / 2 };

	SDL_RenderSetViewport(ren, &top_vp);
	SDL_RenderCopy(ren, flower, NULL, NULL);

	SDL_RenderSetViewport(ren, &bottom_vp);
	SDL_RenderCopy(ren, flower, NULL, NULL);

	SDL_RenderPresent(ren);
	SDL_Delay(2000);

	quit();
	return 0;
}
