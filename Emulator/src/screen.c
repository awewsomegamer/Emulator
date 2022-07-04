#include <screen.h>
#include <SDL2/SDL.h>
#include <emulator.h>
#include <IO.h>

SDL_AudioDeviceID audio_device;

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

int cursor_x = 0;
int cursor_y = 0;

void clear_screen(){
	for (int i = 0; i < WINDOW_HEIGHT; i++){
		for (int j = 0; j < WINDOW_WIDTH; j++){
			draw_pixel((j << 16) | i, BG);
		}
	}
}

void init_window(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		printf("Failed to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("CPU", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetWindowTitle(window, "CPU");

	SDL_ShowWindow(window);
	
	SDL_AudioSpec audio_spec;
    SDL_zero(audio_spec);
    audio_spec.freq = 44100;
    audio_spec.format = AUDIO_S8;
    audio_spec.channels = 1;
    audio_spec.samples = 2048;
    audio_spec.callback = NULL;

    audio_device = SDL_OpenAudioDevice(NULL, 0, &audio_spec, NULL, 0);

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
		call_hardware_interrupt(KEYBOARD_INT, (0x00) << 16 | event.key.keysym.scancode, 4, 0x0);
		
		break;

	case SDL_KEYUP:
		call_hardware_interrupt(KEYBOARD_INT, (0xFF) << 16 | event.key.keysym.scancode, 4, 0x0);

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

	for (int i = 0; i < GLYPH_HEIGHT; i++){
		for (int j = 0; j < GLYPH_WIDTH; j++){
			draw_pixel(((cursor_x + j) << 16) | (cursor_y + i), ((memory[glyph + i] >> j) & 1) ? FG : BG);
		}
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