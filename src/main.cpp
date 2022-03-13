#include "main.h"

#define WINDOW_WIDTH 800

using namespace std;

void init()
{
	cl_init();
	/*
	srand((unsigned int) time(nullptr));
	int num = 250000000;

	auto *a = reinterpret_cast<float *>(malloc(num * sizeof(float)));
	auto *b = reinterpret_cast<float *>(malloc(num * sizeof(float)));
	auto *cl_res = reinterpret_cast<float *>(malloc(num * sizeof(float)));
	auto *cpu_res = reinterpret_cast<float *>(malloc(num * sizeof(float)));

	cout << "allocating " << sizeof(float) * (float) num * ((float) 3 / pow(10, 6)) << "MB" << endl;

	for (int i = 0; i < num; i++) a[num] = b[num] = (float(rand()) / float((RAND_MAX)) * 10);

	cout << endl;
	cl_vadd(a, b, cl_res, num);

	unsigned long cl_hash = boost::hash_range(cl_res, cl_res + num);
	cout << " - CL Hash: " << cl_hash << " at " << cl_res << endl;
	free(cl_res);

	auto start = chrono::steady_clock::now();
	for (int i = 0; i < num; i ++) cpu_res[num] = atan2(sin(a[num]) / cos(a[num]), erf(b[num]) * tanh(b[num]));
	auto end = chrono::steady_clock::now();

	cout << endl;
	cout << " - CPU took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms " << endl;
	unsigned long cpu_hash = boost::hash_range(cpu_res, cpu_res + num);
	cout << " - CPU Hash: " << cpu_hash << " at " << cpu_res << endl;

	cout << endl;
	if(cpu_hash == cl_hash) cout << "HASH MATCH!" << endl;
	else cerr << "WRONG HASH!" << endl;

	_exit(0);
	*/
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
	t.loadDiff("../res/diffuse.png");
	t = t.scaled(200, 200);

	Texture atlas[] = {
		t, t, t, t, t, t
	};

	auto start = chrono::steady_clock::now();
	auto time = chrono::steady_clock::now();
	float rx = 0.5;        // [rad / s]
	float rot = 0;        // [rad]

	while (rot <= M_PI * 2) {
		SDL_Delay(5);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		auto newtime = chrono::steady_clock::now();
		float dt = chrono::duration<float>(newtime - time).count(); // [s]

		if ((*reinterpret_cast<int *>(&dt) >> 10) % 5 == 1) cout << 1 / dt << endl;

		time = newtime;

		rot += rx * dt;

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

		c.rotate(rot, rot, rot, Vector3D((float) WINDOW_WIDTH / 2, (float) WINDOW_WIDTH / 2, (float) WINDOW_WIDTH / 2))
			.cl_draw(render_mutex, renderer, atlas);

		SDL_RenderPresent(renderer);
	}
}
