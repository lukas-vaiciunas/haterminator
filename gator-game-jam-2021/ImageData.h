#pragma once

class Image;

#include <unordered_map>

class ImageData
{
private:
	std::unordered_map<unsigned int, Image *> images_;

	ImageData() {}
	~ImageData();
public:
	ImageData(const ImageData &) = delete;
	ImageData &operator=(const ImageData &) = delete;

	static ImageData &instance();

	void put(unsigned int id, Image *image);
	void clear();

	const Image &get(unsigned int id) const;
};