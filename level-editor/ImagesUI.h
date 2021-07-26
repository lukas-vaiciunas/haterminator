#pragma once

class Mouse;
class Keyboard;
class Painter;

#include <vector>
#include "Key.h"

class ImagesUI
{
private:
	std::vector<std::vector<unsigned int>> imageIds_;
	unsigned int numCols_;
	unsigned int numRows_;
	bool isActive_;
	Key toggleKey_;

	unsigned int spatialHash_(unsigned int col, unsigned int row) const;
	bool isInBounds_(unsigned int col, unsigned int row) const;
public:
	ImagesUI(Key toggleKey);
	ImagesUI(Key toggleKey, const char *sheetPath);

	void load(const char *sheetPath);

	void updateOnMousePress(const Mouse &mouse, Painter &painter);
	void updateOnKeyPress(const Keyboard &keyboard);

	void render(const Mouse &mouse) const;

	bool isActive() const;
};