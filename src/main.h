#pragma once

#include <cmath>
#include <thread>
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>

#include "OpenCL.h"
#include "Cube.h"
#include "Texture.h"
#include "Vector3D.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_mutex *render_mutex;
std::thread waiter;

void init();

void cleanup();

void loop();

int main();