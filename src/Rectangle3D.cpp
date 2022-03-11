#include "Rectangle3D.h"

#include <cmath>
#include <SDL2/SDL.h>

#include "Vector3D.h"
#include "Texture.h"

Rectangle3D::Rectangle3D() = default;

[[maybe_unused]] Rectangle3D::Rectangle3D(Vector3D a, Vector3D b, Vector3D c, Vector3D d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

[[maybe_unused]] void Rectangle3D::draw(SDL_mutex *mutex, SDL_Renderer *renderer) const
{
	SDL_LockMutex(mutex);
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
	SDL_RenderDrawLines(renderer, new const SDL_Point[]{
		{(int) round(a.x), (int) round(a.y)},
		{(int) round(b.x), (int) round(b.y)},

		{(int) round(b.x), (int) round(b.y)},
		{(int) round(c.x), (int) round(c.y)},

		{(int) round(c.x), (int) round(c.y)},
		{(int) round(d.x), (int) round(d.y)},

		{(int) round(d.x), (int) round(d.y)},
		{(int) round(a.x), (int) round(a.y)}
	}, 8);
	SDL_UnlockMutex(mutex);
}

[[maybe_unused]] [[nodiscard]] Vector3D Rectangle3D::normal() const
{
	return (this->d - this->a).cross(this->b - this->a).unit();
}

[[maybe_unused]] void Rectangle3D::draw(SDL_mutex *mutex, SDL_Renderer *renderer, Texture *texture) const
{

	if (texture == nullptr) {
		/* draw normals
		Vector3D mid = (this->a + this->c) / 2;
		float fac = 30;
		SDL_RenderDrawLine(renderer, (int) round(mid.x), (int) round(mid.y), (int) round(mid.x + (this->normal() * fac).x), (int) round(mid.y + (this->normal() * fac).y));
		 */
		this->draw(mutex, renderer);
		return;
	}

	if (this->normal().angle(Vector3D(0, 0, 1)) <= M_PI_2) return;

	Vector3D xu = (this->b - this->a).unit();
	Vector3D yu = (this->d - this->a).unit();

	float maxx = (this->b - this->a).length();
	float maxy = (this->d - this->a).length();

	if ((int) round(maxx) != texture->width || (int) round(maxy) != texture->height) {
		*texture = texture->scaled((int) round(maxx), (int) round(maxy));
	}

	SDL_LockMutex(mutex);
	for (int y = 0; y < (int) round(maxy); y++) {
		for (int x = 0; x < (int) round(maxx); x++) {
			SDL_Color col = texture->getDiffuse(x, y);
			Vector3D to = this->a + (xu * (float) x) + (yu * (float) y);

			SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 0);
			SDL_RenderDrawPoint(renderer, (int) round(to.x), (int) round(to.y));
		}
	}
	SDL_UnlockMutex(mutex);
}

[[maybe_unused]] [[nodiscard]] Rectangle3D Rectangle3D::rotate(float x, float y, float z)
{
	this->rx += x;
	this->ry += y;
	this->rz += z;

	x = (float) fmod(x, 2 * M_PI);
	y = (float) fmod(y, 2 * M_PI);
	z = (float) fmod(z, 2 * M_PI);

	return {
		a.rotate(x, y, z),
		b.rotate(x, y, z),
		c.rotate(x, y, z),
		d.rotate(x, y, z)
	};
}

Rectangle3D Rectangle3D::operator+(const Vector3D v) const
{
	return {
		this->a + v,
		this->b + v,
		this->c + v,
		this->d + v
	};
}

Rectangle3D Rectangle3D::operator-(const Vector3D v) const
{
	return {
		this->a - v,
		this->b - v,
		this->c - v,
		this->d - v
	};
}
