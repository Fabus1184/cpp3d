#pragma once

#define cimg_display 0
#include <CImg.h>
#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
	cimg_library::CImg<float> diffuse{};
	int width = 0, height = 0;

	Texture();

	void loadDiff(const std::string &path);

	[[nodiscard]] Texture scaled(int nw, int nh) const;

	[[maybe_unused]] [[nodiscard]] SDL_Color getDiffuse(int x, int y) const;

	[[maybe_unused]] [[nodiscard]] std::string toString() const;
};
