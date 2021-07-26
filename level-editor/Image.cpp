#include "Image.h"

#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

Image::Image(
	ALLEGRO_BITMAP *sheet,
	unsigned int sheetX, unsigned int sheetY,
	unsigned char width, unsigned char height)
{
	bitmap_ = al_create_bitmap(width, height);
	sourceX_ = sheetX;
	sourceY_ = sheetY;
	width_ = width;
	height_ = height;

	al_set_target_bitmap(bitmap_);
	al_draw_bitmap_region(sheet, sheetX, sheetY, width, height, 0.0f, 0.0f, 0);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

	al_convert_mask_to_alpha(bitmap_, al_map_rgb(255, 0, 255));
}

Image::Image(const Image &other)
{
	bitmap_ = al_create_bitmap(other.width_, other.height_);
	sourceX_ = other.sourceX_;
	sourceY_ = other.sourceY_;
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
	sourceX_ = other.sourceX_;
	sourceY_ = other.sourceY_;
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

const Image Image::cutOut(float x, float y, float width, float height) const
{
	return Image(bitmap_, x, y, width, height);
}

unsigned int Image::sourceX() const
{
	return sourceX_;
}

unsigned int Image::sourceY() const
{
	return sourceY_;
}

unsigned char Image::width() const
{
	return width_;
}

unsigned char Image::height() const
{
	return height_;
}