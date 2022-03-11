#include "main.h"

#define WINDOW_WIDTH 800

using namespace std;

void init()
{
	cl_test();
	_exit(0);

	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO);

	SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "opengl");
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	window = SDL_CreateWindow("Fetz Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_WIDTH, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	render_mutex = SDL_CreateMutex();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void cleanup()
{
	waiter.detach();
	SDL_LockMutex(render_mutex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

void loop()
{
	while (waiter.joinable()) {
		SDL_Delay(5);
		SDL_Event event;
		if (SDL_PollEvent(&event) != 0 && event.type == SDL_QUIT) _exit(0);
	}
}

int main()
{
	init();
	waiter = thread(ref(loop));
	atexit(&cleanup);

	int width = 200;

	Cube c(Vector3D(
			   (float) (WINDOW_WIDTH - width) / 2,
			   (float) (WINDOW_WIDTH - width) / 2,
			   (float) (WINDOW_WIDTH - width) / 2),
		   (float) width);

	Texture t;
	t.loadDiff("res/diffuse.png");
	t = t.scaled(200, 200);

	Texture *atlas[] = {
		&t, &t, &t, &t, &t, &t
	};

	auto start = chrono::steady_clock::now();
	auto time = chrono::steady_clock::now();
	float rx = 0.5;        // [rad / s]
	float rot = 0;        // [rad]

	while (rot <= M_PI) {
		SDL_Delay(5);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		auto newtime = chrono::steady_clock::now();
		float dt = chrono::duration<float>(newtime - time).count(); // [s]

		if ((*reinterpret_cast<int *>(&dt) >> 10) % 5 == 1) cout << 1 / dt << endl;

		time = newtime;

		rot += rx * dt;

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

		c.rotate(rot, rot, rot, Vector3D((float) WINDOW_WIDTH / 2, (float) WINDOW_WIDTH / 2, (float) WINDOW_WIDTH / 2)).draw(render_mutex, renderer, atlas);

		SDL_RenderPresent(renderer);
	}
}
