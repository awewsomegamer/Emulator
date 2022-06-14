#include <screen.h>
#include <SDL2/SDL.h>
#include <emulator.h>
#include <IO.h>

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

int cursor_x = 0;
int cursor_y = 0;

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

void clear_screen(){
	for (int i = 0; i < WINDOW_HEIGHT; i++){
		for (int j = 0; j < WINDOW_WIDTH; j++){
			draw_pixel((j << 16) | i, BG);
		}
	}
}

void init_window(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Failed to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("CPU", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetWindowTitle(window, "CPU");

	SDL_ShowWindow(window);

	clear_screen();
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
		call_hardware_interrupt(3, (0x00) << 16 | event.key.keysym.scancode, 4, 0x0);
		
		break;

	case SDL_KEYUP:
		call_hardware_interrupt(3, (0xFF) << 16 | event.key.keysym.scancode, 4, 0x0);

		break;
	}

	SDL_RenderPresent(renderer);
}

// Position: uint16_t x, uint16_t y
void draw_pixel(uint32_t position, int rgba){
	SDL_SetRenderDrawColor(renderer, (rgba >> 24) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 8) & 0xFF, rgba & 0xFF);
	SDL_RenderDrawPoint(renderer, (position >> 16) & 0xFFFF, position & 0xFFFF);
}

void sputc(char c){
	int glyph = FONT_ADDRESS + (c * GLYPH_HEIGHT);

	int jj = 0;

	for (int i = 0; i < GLYPH_HEIGHT; i++){
		for (int j = GLYPH_WIDTH-1; j >= 0; j--){
			draw_pixel(((cursor_x + jj) << 16) | (cursor_y + i), ((memory[glyph + i] >> j) & 1) ? FG : BG);

			jj++;
		}

		jj = 0;
	}

	cursor_x += GLYPH_WIDTH;

	if (cursor_x >= WINDOW_WIDTH){
		cursor_x = 0;
		cursor_y += GLYPH_HEIGHT;
	}

}

void set_cursor_position(int x, int y){
	cursor_x = x;
	cursor_y = y;
}

int get_cursor_position(){
	return (cursor_x << 16) | cursor_y;
}