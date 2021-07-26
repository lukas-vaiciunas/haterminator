#include "ImagesUI.h"

#include <allegro5/allegro_primitives.h>
#include "Mouse.h"
#include "Keyboard.h"
#include "Constants.h"
#include "Painter.h"
#include "ImageData.h"
#include "Image.h"

ImagesUI::ImagesUI(Key toggleKey) :
	toggleKey_(toggleKey),
	numCols_(0),
	numRows_(0),
	isActive_(false)
{}

ImagesUI::ImagesUI(Key toggleKey, const char *sheetPath) :
	ImagesUI(toggleKey)
{
	this->load(sheetPath);
}

void ImagesUI::load(const char *sheetPath)
{
	ImageData &imageData = ImageData::instance();

	imageData.clear();

	ALLEGRO_BITMAP *sheet = al_load_bitmap(sheetPath);

	unsigned int sheetWidth = al_get_bitmap_width(sheet);
	unsigned int sheetHeight = al_get_bitmap_height(sheet);

	unsigned int tileSize = Constants::tileSize;
	numCols_ = sheetWidth / tileSize;
	numRows_ = sheetHeight / tileSize;

	imageIds_ = std::vector<std::vector<unsigned int>>(numRows_, std::vector<unsigned int>(numCols_, 0));

	for (unsigned int row = 0; row < numRows_; row++)
	{
		for (unsigned int col = 0; col < numCols_; col++)
		{
			unsigned int id = this->spatialHash_(col, row) + 1;
			imageIds_.at(row).at(col) = id;

			imageData.put(
				id,
				new Image(sheet, col * tileSize, row * tileSize, tileSize, tileSize));
		}
	}

	al_destroy_bitmap(sheet);
	sheet = nullptr;
}

void ImagesUI::updateOnMousePress(const Mouse &mouse, Painter &painter)
{
	if (!isActive_)
		return;

	if (mouse.isPressed(Mouse::Button::M1))
	{
		unsigned int col = mouse.x() / Constants::tileSize;
		unsigned int row = mouse.y() / Constants::tileSize;

		if(this->isInBounds_(col, row))
			painter.setImageId(imageIds_.at(row).at(col));
	}
}

void ImagesUI::updateOnKeyPress(const Keyboard &keyboard)
{
	if (keyboard.isPressed(toggleKey_))
		isActive_ = !isActive_;
}

void ImagesUI::render(const Mouse &mouse) const
{
	if (!isActive_)
		return;

	unsigned int tileSize = Constants::tileSize;
	unsigned int mouseCol = mouse.x() / tileSize;
	unsigned int mouseRow = mouse.y() / tileSize;

	for (unsigned int row = 0; row < numRows_; row++)
		for (unsigned int col = 0; col < numCols_; col++)
			ImageData::instance()
			.get(imageIds_.at(row).at(col))
			.render(col * tileSize, row * tileSize);

	if (this->isInBounds_(mouseCol, mouseRow))
	{
		float indicatorX = mouseCol * tileSize;
		float indicatorY = mouseRow * tileSize;

		al_draw_rectangle(
			indicatorX, indicatorY,
			indicatorX + tileSize, indicatorY + tileSize,
			al_map_rgb(255, 0, 255), 2.0f);
	}
}

bool ImagesUI::isActive() const
{
	return isActive_;
}

unsigned int ImagesUI::spatialHash_(unsigned int col, unsigned int row) const
{
	return col + row * numCols_;
}

bool ImagesUI::isInBounds_(unsigned int col, unsigned int row) const
{
	return col >= 0
		&& col < numCols_
		&& row >= 0
		&& row < numRows_;
}