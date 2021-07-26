#include "Image.h"

#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

Image::Image(const char *dataPath)
{
	bitmap_ = al_load_bitmap(dataPath);

	width_ = al_get_bitmap_width(bitmap_);
	height_ = al_get_bitmap_height(bitmap_);

	al_convert_mask_to_alpha(bitmap_, al_map_rgb(255, 0, 255));
}

Image::Image(
	const char *sheetPath,
	unsigned int sheetX, unsigned int sheetY,
	unsigned char width, unsigned char height)
{
	ALLEGRO_BITMAP *sheet = al_load_bitmap(sheetPath);

	*this = Image(sheet, sheetX, sheetY, width, height);

	al_destroy_bitmap(sheet);
	sheet = nullptr;
}

Image::Image(
	ALLEGRO_BITMAP *sheet,
	unsigned int sheetX, unsigned int sheetY,
	unsigned char width, unsigned char height)
{
	bitmap_ = al_create_bitmap(width, height);
	width_ = width;
	height_ = height;

	al_set_target_bitmap(bitmap_);
	al_draw_bitmap_region(sheet, sheetX, sheetY, width, height, 0.0f, 0.0f, 0);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

	al_convert_mask_to_alpha(bitmap_, al_map_rgb(255, 0, 255));
}

Image::Image(unsigned char width, unsigned char height, const ALLEGRO_COLOR &color)
{
	bitmap_ = al_create_bitmap(width, height);
	width_ = width;
	height_ = height;

	al_set_target_bitmap(bitmap_);
	al_clear_to_color(color);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}

Image::Image(const Image &other)
{
	bitmap_ = al_create_bitmap(other.width_, other.height_);
	width_ = other.width_;
	height_ = other.height_;

	al_set_target_bitmap(bitmap_);
	al_draw_bitmap(other.bitmap_, 0.0f, 0.0f, 0);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}

Image &Image::operator=(const Image &other)
{
	al_destroy_bitmap(bitmap_);
	bitmap_ = nullptr;

	bitmap_ = al_create_bitmap(other.width_, other.height_);
	width_ = other.width_;
	height_ = other.height_;

	al_set_target_bitmap(bitmap_);
	al_draw_bitmap(other.bitmap_, 0.0f, 0.0f, 0);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

	return *this;
}

Image::~Image()
{
	al_destroy_bitmap(bitmap_);
	bitmap_ = nullptr;
}

void Image::render(float x, float y, int allegroFlags) const
{
	al_draw_bitmap(bitmap_, x, y, allegroFlags);
}

void Image::render(float x, float y, float scale, int allegroFlags) const
{
	al_draw_scaled_bitmap(
		bitmap_,
		0.0f, 0.0f,
		width_, height_,
		x, y,
		width_ * scale, height_ * scale,
		allegroFlags);
}

void Image::render(float x, float y, float scale, const ALLEGRO_COLOR &tint, int allegroFlags) const
{
	al_draw_tinted_scaled_bitmap(
		bitmap_,
		tint,
		0.0f, 0.0f,
		width_, height_,
		x, y,
		width_ * scale, height_ * scale,
		allegroFlags);
}

void Image::render(float x, float y, float scale, float angleRad, int allegroFlags) const
{
	float centerX = width_ * 0.5f;
	float centerY = height_ * 0.5f;

	al_draw_scaled_rotated_bitmap(
		bitmap_,
		centerX, centerY,
		x + centerX, y + centerY,
		scale, scale,
		angleRad,
		allegroFlags);
}

void Image::render(float x, float y, float sX, float sY, float sWidth, float sHeight, int allegroFlags) const
{
	al_draw_bitmap_region(bitmap_, sX, sY, sWidth, sHeight, x, y, allegroFlags);
}

unsigned char Image::width() const
{
	return width_;
}

unsigned char Image::height() const
{
	return height_;
}