#pragma once

#include <allegro5/bitmap.h>
#include <allegro5/allegro_color.h>

class Image
{
private:
	ALLEGRO_BITMAP *bitmap_;
	unsigned int sourceX_;
	unsigned int sourceY_;
	unsigned char width_;
	unsigned char height_;
public:
	Image(
		ALLEGRO_BITMAP *sheet,
		unsigned int sheetX, unsigned int sheetY,
		unsigned char width, unsigned char height);
	Image(const Image &other);
	Image &operator=(const Image &other);
	~Image();

	void render(float x, float y, int allegroFlags = 0) const;
	void render(float x, float y, float scale, int allegroFlags = 0) const;
	void render(float x, float y, float scale, float angleRad, int allegroFlags = 0) const;
	void render(float x, float y, float sX, float sY, float sWidth, float sHeight, int allegroFlags = 0) const;

	const Image cutOut(float x, float y, float width, float height) const;

	unsigned int sourceX() const;
	unsigned int sourceY() const;
	unsigned char width() const;
	unsigned char height() const;
};