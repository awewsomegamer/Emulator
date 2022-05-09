#include <screen.h>
#include <SDL2/SDL.h>
#include <emulator.h>

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer;

// typedef enum {
// 	BLACK = 0,
// 	BLUE,
// 	GREEN,
// 	LIGHT_BLUE,
// 	RED,
// 	PURPLE,
// 	BROWN,
// 	GREY,
// 	DARK_GREY,
// 	LIGHT_DARK_BLUE,
// 	CYAN,
// 	LIGHT_RED,
// 	PINK,
// 	YELLOW,
// 	WHITE
// } COLORS;

void init_window(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Failed to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

	SDL_SetWindowTitle(window, "CPU");

	SDL_ShowWindow(window);
}

void update(){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
	case SDL_WINDOWEVENT:
		switch(event.window.event){
			case SDL_WINDOWEVENT_CLOSE:
				running = false;
				break;
		}

		break;
	}
}

void render(){
	for (int i = 0; i < 480; i++){
		for (int j = 0; j < 640; j++){
			uint8_t r = memory[((i * 640 + j) * 4 + 0) + (0xB8000)];
			uint8_t g = memory[((i * 640 + j) * 4 + 1) + (0xB8000)];
			uint8_t b = memory[((i * 640 + j) * 4 + 2) + (0xB8000)];
			uint8_t a = memory[((i * 640 + j) * 4 + 3) + (0xB8000)];

			// printf("%08X %08X\n", registers[B], (memory[0xB8000] | (memory[0xB8001] << 8) | (memory[0xB8002] << 16)));

			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			SDL_RenderDrawPoint(renderer, j, i);

			// printf("%d (%d, %d)\n", color & 0xFF, j, i);

			/*
			// switch(color){
			// case BLACK:
			// 	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
			// 	break;

			// case BLUE:
			// 	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);
			// 	break;

			// case GREEN:
			// 	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
			// 	break;

			// case LIGHT_BLUE:
			// 	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 1);
			// 	break;

			// case RED:
			// 	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
			// 	break;

			// case PURPLE:
			// 	SDL_SetRenderDrawColor(renderer, 102, 0, 102, 1);
			// 	break;

			// case BROWN:
			// 	SDL_SetRenderDrawColor(renderer, 139, 69, 19, 1);
			// 	break;

			// case GREY:
			// 	SDL_SetRenderDrawColor(renderer, 127, 127, 127, 1);
			// 	break;

			// case DARK_GREY:
			// 	SDL_SetRenderDrawColor(renderer, 27, 27, 27, 1);
			// 	break;

			// case LIGHT_DARK_BLUE:
			// 	SDL_SetRenderDrawColor(renderer, 0, 0, 205, 1);
			// 	break;

			// case CYAN:
			// 	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 1);
			// 	break;

			// case LIGHT_RED:
			// 	SDL_SetRenderDrawColor(renderer, 255, 204, 203, 1);
			// 	break;
				
			// case PINK:
			// 	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 1);
			// 	break;

			// case YELLOW:
			// 	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);
			// 	break;

			// case WHITE:
			// 	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
			// 	break;
			// }
			*/
		}
	}


	SDL_RenderPresent(renderer);
}