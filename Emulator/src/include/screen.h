#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

extern bool running;
extern SDL_Window* window;

void init_window();
void update();
// void render();
void draw_pixel(int position, int rgba);

#endif