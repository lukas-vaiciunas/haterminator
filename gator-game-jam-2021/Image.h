#pragma once

#include <allegro5/bitmap.h>
#include <allegro5/allegro_color.h>

class Image
{
private:
	ALLEGRO_BITMAP *bitmap_;
	unsigned char width_;
	unsigned char height_;
public:
	Image(const char *dataPath);
	Image(
		const char *sheetPath,
		unsigned int sheetX, unsigned int sheetY,
		unsigned char width, unsigned char height);
	Image(
		ALLEGRO_BITMAP *sheet,
		unsigned int sheetX, unsigned int sheetY,
		unsigned char width, unsigned char height);
	Image(unsigned char width, unsigned char height, const ALLEGRO_COLOR &color);
	Image(const Image &other);
	Image &operator=(const Image &other);
	~Image();

	void render(float x, float y, int allegroFlags = 0) const;
	void render(float x, float y, float scale, int allegroFlags = 0) const;
	void render(float x, float y, float scale, const ALLEGRO_COLOR &tint, int allegroFlags = 0) const;
	void render(float x, float y, float scale, float angleRad, int allegroFlags = 0) const;
	void render(float x, float y, float sX, float sY, float sWidth, float sHeight, int allegroFlags = 0) const;

	unsigned char width() const;
	unsigned char height() const;
};