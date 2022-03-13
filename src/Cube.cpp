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

[[maybe_unused]] void Cube::draw(SDL_mutex *mutex, SDL_Renderer *r, Texture **texture) const
{
	a.draw(mutex, r, texture[0]);
	b.draw(mutex, r, texture[1]);
	c.draw(mutex, r, texture[2]);
	d.draw(mutex, r, texture[3]);
	e.draw(mutex, r, texture[4]);
	f.draw(mutex, r, texture[5]);

}

void Cube::cl_draw(SDL_mutex *mutex, SDL_Renderer *r, Texture *texture) const
{
	/*future<void> at = async(launch::async, [this, mutex, r, texture]() { this->a.cl_draw(mutex, r, texture[0]); });
	future<void> bt = async(launch::async, [this, mutex, r, texture]() { this->b.cl_draw(mutex, r, texture[1]); });
	future<void> ct = async(launch::async, [this, mutex, r, texture]() { this->c.cl_draw(mutex, r, texture[2]); });
	future<void> dt = async(launch::async, [this, mutex, r, texture]() { this->d.cl_draw(mutex, r, texture[3]); });
	future<void> et = async(launch::async, [this, mutex, r, texture]() { this->e.cl_draw(mutex, r, texture[4]); });
	future<void> ft = async(launch::async, [this, mutex, r, texture]() { this->f.cl_draw(mutex, r, texture[5]); });

	at.get();
	bt.get();
	ct.get();
	dt.get();
	et.get();
	ft.get();*/

	a.cl_draw(mutex, r, texture[0]);
	b.cl_draw(mutex, r, texture[1]);
	c.cl_draw(mutex, r, texture[2]);
	d.cl_draw(mutex, r, texture[3]);
	e.cl_draw(mutex, r, texture[4]);
	f.cl_draw(mutex, r, texture[5]);
}
