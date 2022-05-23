#include <screen.h>
#include <SDL2/SDL.h>
#include <emulator.h>
#include <IO.h>

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
	case SDL_KEYDOWN:
		call_hardware_interrupt(2, (0x00) << 16 | event.key.keysym.scancode, 4, 0x0);
		
		break;

	case SDL_KEYUP:
		call_hardware_interrupt(2, (0xFF) << 16 | event.key.keysym.scancode, 4, 0x0);

		break;
	}

	SDL_RenderPresent(renderer);
}

// Position: uint16_t x, uint16_t y
void draw_pixel(uint32_t position, int rgba){
	SDL_SetRenderDrawColor(renderer, (rgba >> 24) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 8) & 0xFF, rgba & 0xFF);
	SDL_RenderDrawPoint(renderer, (position >> 16) & 0xFFFF, position & 0xFFFF);
}