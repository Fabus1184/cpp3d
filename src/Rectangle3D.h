#pragma once

#include <cmath>
#include <SDL2/SDL.h>

#include "Texture.h"
#include "Vector3D.h"

class Rectangle3D
{
public:
	Vector3D a{}, b{}, c{}, d{};
	float rx{}, ry{}, rz{};

	Rectangle3D();

	[[maybe_unused]] Rectangle3D(Vector3D a, Vector3D b, Vector3D c, Vector3D d);

	[[maybe_unused]] void draw(SDL_mutex *mutex, SDL_Renderer *renderer) const;

	[[maybe_unused]] [[nodiscard]] Vector3D normal() const;

	[[maybe_unused]] void draw(SDL_mutex *mutex, SDL_Renderer *renderer, Texture *texture) const;

	[[maybe_unused]] [[nodiscard]] Rectangle3D rotate(float x, float y, float z);

	Rectangle3D operator+(Vector3D v) const;

	Rectangle3D operator-(Vector3D v) const;
};

