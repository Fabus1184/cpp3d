#pragma once

#include <SDL2/SDL.h>

#include "Rectangle3D.h"
#include "Texture.h"

class Cube
{
public:
	Rectangle3D a{}, b{}, c{}, d{}, e{}, f{};

	Cube();

	Cube(Vector3D lower_left_front, float width);

	[[maybe_unused]] Cube(Rectangle3D a, Rectangle3D b, Rectangle3D c, Rectangle3D d, Rectangle3D e, Rectangle3D f);

	[[maybe_unused]] [[nodiscard]] Cube rotate(float x, float y, float z);

	[[nodiscard]] Cube rotate(float x, float y, float z, Vector3D pivot) const;

	void draw(SDL_mutex *mutex, SDL_Renderer *r, Texture **texture = nullptr) const;
};