#include <screen.h>
#include <SDL2/SDL.h>
#include <emulator.h>

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

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

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	SDL_SetWindowTitle(window, "CPU");

	SDL_ShowWindow(window);
}

void update(){
	SDL_PollEvent(&event);

	switch(event.type){
	case SDL_QUIT:
		running = false;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		break;

	}
}

// void render(){
// 	for (int i = 0; i < 480; i++){
// 		for (int j = 0; j < 640; j++){
// 			uint8_t r = memory[((i * 640 + j) * 4 + 0) + (0xB8000)];
// 			uint8_t g = memory[((i * 640 + j) * 4 + 1) + (0xB8000)];
// 			uint8_t b = memory[((i * 640 + j) * 4 + 2) + (0xB8000)];
// 			uint8_t a = memory[((i * 640 + j) * 4 + 3) + (0xB8000)];

// 			SDL_SetRenderDrawColor(renderer, r, g, b, a);
// 			SDL_RenderDrawPoint(renderer, j, i); // Causes window closing to be slow
// 		}
// 	}


// 	SDL_RenderPresent(renderer);
// }

void draw_pixel(int position, int abgr){
	SDL_SetRenderDrawColor(renderer, abgr & 0xFF, (abgr >> 8) & 0xFF, (abgr >> 16) & 0xFF, (abgr >> 24) & 0xFF);
	SDL_RenderDrawPoint(renderer, position % WINDOW_WIDTH,  position / WINDOW_WIDTH); // Causes window closing to be slow
}