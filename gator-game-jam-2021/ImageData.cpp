#include "ImageData.h"
#include "Image.h"

ImageData::~ImageData()
{
	this->clear();
}

ImageData &ImageData::instance()
{
	static ImageData imageData;
	return imageData;
}

void ImageData::put(unsigned int id, Image *image)
{
	images_.emplace(id, image);
}

void ImageData::clear()
{
	for (auto it = images_.begin(); it != images_.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}

	images_.clear();
}

const Image &ImageData::get(unsigned int id) const
{
	return *images_.at(id);
}