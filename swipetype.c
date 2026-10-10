#include <stdio.h>
#include <stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TITLE "swipe type"
#define HEIGHT 360
#define WIDTH 720
#define FPS 16

struct Raw_word{
	char word[10];
};

struct Screen{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
};

bool load(struct Screen *screen);
bool init(struct Screen *screen);
void delete(struct Screen *screen, int exit_status);

int main(void){
	struct Screen screen={0};
	if(init(&screen)){
		printf("initialisation error\n");
		delete(&screen, EXIT_FAILURE);
	}
	if(load(&screen)){
		printf("loading error \n");
		delete(&screen, EXIT_FAILURE);
	}
	while(true){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					delete(&screen, EXIT_SUCCESS);
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.scancode){
						case SDL_SCANCODE_ESCAPE:
							delete(&screen,EXIT_SUCCESS);
							break;
						default:
							break;
					}
				default:
					break;
			}
			SDL_RenderClear(screen.renderer);
			SDL_Rect back_ground_rect = {0,0,WIDTH,HEIGHT};
			SDL_RenderCopy(screen.renderer, screen.background, NULL, &back_ground_rect);
			SDL_RenderPresent(screen.renderer);
			SDL_Delay(FPS);
		}
	}
	delete(&screen, EXIT_SUCCESS);
	printf("test");
	return 0;
}

void delete(struct Screen *screen,int exit_status){
	if(screen->background) SDL_DestroyTexture(screen->background);
	SDL_DestroyRenderer(screen->renderer);
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
	IMG_Quit();
	exit(exit_status);
}

bool init(struct Screen *screen){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "error initialising: %s \n", SDL_GetError());
		return true;
	}
	
    screen -> window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
	if(!screen->window){
		fprintf(stderr, "error creating window: %s \n", SDL_GetError());
		return true;
	}
	screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
	if (!screen->renderer){
		fprintf(stderr, "error creating renderer: %s \n", SDL_GetError());
		return true;
	}
	return false;
}

bool load(struct Screen *screen){
	screen->background=IMG_LoadTexture(screen->renderer, "image.png");
	if(!screen->background){
		fprintf(stderr,"error creating background image: %s \n", SDL_GetError());
		return true;
	}
	return false;
}
