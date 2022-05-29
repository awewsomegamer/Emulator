#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 8
#define FONT_ADDRESS 0x5000

extern bool running;
extern SDL_Window* window;

void init_window();
void update();
void draw_pixel(uint32_t position, int rgba);
void sputc(char c);

#endif