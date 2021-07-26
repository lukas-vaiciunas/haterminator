#pragma once

#include <allegro5/allegro_font.h>
#include <unordered_map>

class FontData
{
private:
	std::unordered_map<unsigned int, ALLEGRO_FONT *> fonts_;

	FontData();
	~FontData();
public:
	FontData(const FontData &) = delete;
	const FontData &operator=(const FontData &) = delete;

	static FontData &instance();

	void renderText(
		float x, float y,
		const char *text,
		unsigned int size,
		const ALLEGRO_COLOR &color,
		int allegroFlags) const;

	void renderText(
		float x, float y,
		const std::string &text,
		unsigned int size,
		const ALLEGRO_COLOR &color,
		int allegroFlags) const;

	ALLEGRO_FONT *get(unsigned int size);
};