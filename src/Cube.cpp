#include "Cube.h"

using namespace std;

Cube::Cube() = default;

Cube::Cube(Vector3D lower_left_front, float width)
{
	this->a = {
		lower_left_front, lower_left_front + Vector3D(width, 0, 0),
		lower_left_front + Vector3D(width, width, 0), lower_left_front + Vector3D(0, width, 0)
	};

	this->b = {
		lower_left_front + Vector3D(width, 0, 0), lower_left_front + Vector3D(width, 0, width),
		lower_left_front + Vector3D(width, width, width), lower_left_front + Vector3D(width, width, 0)
	};

	this->c = {
		lower_left_front + Vector3D(0, 0, width), lower_left_front,
		lower_left_front + Vector3D(0, width, 0), lower_left_front + Vector3D(0, width, width)
	};

	this->d = {
		lower_left_front + Vector3D(0, 0, width), lower_left_front + Vector3D(width, 0, width),
		lower_left_front + Vector3D(width, 0, 0), lower_left_front + Vector3D(0, 0, 0)

	};

	this->e = {
		lower_left_front + Vector3D(width, 0, width), lower_left_front + Vector3D(0, 0, width),
		lower_left_front + Vector3D(0, width, width), lower_left_front + Vector3D(width, width, width)
	};

	this->f = {
		lower_left_front + Vector3D(width, width, 0), lower_left_front + Vector3D(width, width, width),
		lower_left_front + Vector3D(0, width, width), lower_left_front + Vector3D(0, width, 0)
	};
}

[[maybe_unused]] Cube::Cube(Rectangle3D a, Rectangle3D b, Rectangle3D c, Rectangle3D d, Rectangle3D e, Rectangle3D f)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->e = e;
	this->f = f;
}

[[maybe_unused]] [[nodiscard]] Cube Cube::rotate(float x, float y, float z)
{
	return {
		this->a.rotate(x, y, z),
		this->b.rotate(x, y, z),
		this->c.rotate(x, y, z),
		this->d.rotate(x, y, z),
		this->e.rotate(x, y, z),
		this->f.rotate(x, y, z)
	};
}

[[nodiscard]] Cube Cube::rotate(float x, float y, float z, Vector3D pivot) const
{
	return {
		(this->b - pivot).rotate(x, y, z) + pivot,
		(this->c - pivot).rotate(x, y, z) + pivot,
		(this->a - pivot).rotate(x, y, z) + pivot,
		(this->d - pivot).rotate(x, y, z) + pivot,
		(this->e - pivot).rotate(x, y, z) + pivot,
		(this->f - pivot).rotate(x, y, z) + pivot
	};
}

void Cube::draw(SDL_mutex *mutex, SDL_Renderer *r, Texture **texture) const
{
	/*thread at([this, r, texture, mutex]() { a.draw(mutex, r, texture[0]); });
	thread bt([this, r, texture, mutex]() { b.draw(mutex, r, texture[1]); });
	thread ct([this, r, texture, mutex]() { c.draw(mutex, r, texture[2]); });
	thread dt([this, r, texture, mutex]() { d.draw(mutex, r, texture[3]); });
	thread et([this, r, texture, mutex]() { e.draw(mutex, r, texture[4]); });
	thread ft([this, r, texture, mutex]() { f.draw(mutex, r, texture[5]); });

	at.join();
	bt.join();
	ct.join();
	dt.join();
	et.join();
	ft.join();*/

	a.draw(mutex, r, texture[0]);
	b.draw(mutex, r, texture[1]);
	c.draw(mutex, r, texture[2]);
	d.draw(mutex, r, texture[3]);
	e.draw(mutex, r, texture[4]);
	f.draw(mutex, r, texture[5]);

}
