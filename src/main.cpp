#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>

#include "Rectangle3D.cpp"

#define WINDOW_WIDTH 800

using namespace std;

void loop(SDL_Renderer* renderer, SDL_Window* window){
	SDL_Event *event;
	while(true){
		if (SDL_PollEvent(event)){
			if(event->type == SDL_QUIT) break;
		}
	}
  	SDL_DestroyRenderer(renderer);
  	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0){
        cout << "Failed to initialize the SDL2 library" << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Fetz Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_WIDTH, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Font* font = TTF_OpenFont("res/Chalkboard.ttf", 20);

	if (font == nullptr){
		cout << "ERROR: font not found" << endl;
		exit(1);
	}

	thread thread(loop, renderer, window);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	int width = 100;

	Point3D a(-width, -width,  width);
	Point3D b( width, -width,  width);
	Point3D c( width,  width,  width);
	Point3D d(-width,  width,  width);

	Point3D e(-width,   -100, -width);
	Point3D f( width,   -100, -width);
	Point3D g( width,    100, -width);
	Point3D h(-width,    100, -width);

	Rectangle3D rs[] = {
		Rectangle3D(a, b, c, d),
		Rectangle3D(d, c, g, h),
		Rectangle3D(e, f, g, h),
		Rectangle3D(a, b, f, e),
		Rectangle3D(e, a, d, h),
		Rectangle3D(b, f, g, c)
	};


	auto start = chrono::steady_clock::now();
	auto time = chrono::steady_clock::now();
	double rx = 0.5;	// [rad / s]
	double rot = 0;		// [rad]
	string fps = "0";

	while(true){
		SDL_Delay(5);

		auto newtime = chrono::steady_clock::now();
		double dt = chrono::duration<double>(newtime - time).count(); // [s]
		time = newtime;

		rot += rx * dt;
		
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

		for(Rectangle3D r : rs) r.rotate(rot, rot, rot).draw(Point3D(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, 0), renderer);

		double dur = chrono::duration<double>(time - start).count();

		if (fmod(round((dur - floor(dur)) * 100.0) / 10, 2) == 0) fps = to_string((int) round(1 / dt));
		
		SDL_Surface* surface = TTF_RenderText_Blended(font, fps.c_str(), {0, 255, 0, 0});
	
		if (surface == nullptr) {
			cout << "Error: SDL_Surface TTF_RenderText_Blended" << endl;
			exit(1);
		}

		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

		if (surface == nullptr) {
			cout << "Error: SDL_Texture SDL_CreateTextureFromSurface" << endl;
			exit(1);
		}

		SDL_FreeSurface(surface);
				
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		
		SDL_QueryTexture(message, NULL, NULL, &rect.w, &rect.h);

		SDL_RenderCopy(renderer, message, NULL, &rect);
		SDL_DestroyTexture(message);
		
		SDL_RenderPresent(renderer);
    	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

  	SDL_DestroyRenderer(renderer);
  	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	exit(0);
}
