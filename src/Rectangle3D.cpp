#include <graphics.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "Point3D.cpp"

using namespace std;

class Rectangle3D {

private:
	Point3D a, b, c, d;

public:

	Rectangle3D(Point3D a, Point3D b, Point3D c, Point3D d){
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}

	void draw(Point3D origin, SDL_Renderer* renderer){
		SDL_RenderDrawLines(renderer, new const SDL_Point[] {
			{(int) round(a.X() + origin.X()), (int) round(a.Y() + origin.Y())},
			{(int) round(b.X() + origin.X()), (int) round(b.Y() + origin.Y())},
			
			{(int) round(b.X() + origin.X()), (int) round(b.Y() + origin.Y())},
			{(int) round(c.X() + origin.X()), (int) round(c.Y() + origin.Y())},
			 
			{(int) round(c.X() + origin.X()), (int) round(c.Y() + origin.Y())},
			{(int) round(d.X() + origin.X()), (int) round(d.Y() + origin.Y())},

			{(int) round(d.X() + origin.X()), (int) round(d.Y() + origin.Y())},
			{(int) round(a.X() + origin.X()), (int) round(a.Y() + origin.Y())}
		}, 8);
	}

	Rectangle3D rotate(double x, double y, double z){
		x = fmod(x, 2 * M_PI);
		y = fmod(y, 2 * M_PI);
		z = fmod(z, 2 * M_PI);

		return Rectangle3D(
			a.rotate(x, y, z),
			b.rotate(x, y, z),
			c.rotate(x, y, z),
			d.rotate(x, y, z)
		);
	}
};
