#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

extern bool running;
extern SDL_Window* window;

void init_window();
void update();
void render();

#endif