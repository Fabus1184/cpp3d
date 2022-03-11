#include "Texture.h"

using namespace std;
using namespace cimg_library;

Texture::Texture() = default;

void Texture::loadDiff(const string& path)
{
	diffuse = cimg_library::CImg(path.c_str());
	this->width = diffuse.width();
	this->height = diffuse.height();
}

[[nodiscard]] Texture Texture::scaled(int nw, int nh) const
{
	Texture t;
	t.width = nw;
	t.height = nh;
	t.diffuse = CImg<float>(diffuse).resize(nw, nh);
	return t;
}

[[maybe_unused]] [[nodiscard]] SDL_Color Texture::getDiffuse(int x, int y) const
{
	return {
		static_cast<Uint8>((int) diffuse(x, y, 0, 0)),
		static_cast<Uint8>((int) diffuse(x, y, 0, 1)),
		static_cast<Uint8>((int) diffuse(x, y, 0, 2))
	};
}

[[maybe_unused]] [[nodiscard]] string Texture::toString() const
{
	return "Texture with size (" + to_string(width) + "x" + to_string(height) + ")";
}