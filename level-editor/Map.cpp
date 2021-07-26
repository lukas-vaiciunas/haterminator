#include "Map.h"

#include <allegro5/allegro_primitives.h>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>
#include "ImageData.h"
#include "Image.h"
#include "Camera.h"
#include "Constants.h"

Map::Map(unsigned int numCols, unsigned int numRows) :
	tiles_(std::vector<std::vector<Tile *>>(numRows, std::vector<Tile *>(numCols, nullptr))),
	numCols_(numCols),
	numRows_(numRows)
{}

Map::Map(const char *dataPath)
{
	this->load(dataPath);
}

Map::~Map()
{
	for (auto rowIt = tiles_.begin(); rowIt != tiles_.end(); rowIt++)
	{
		for (auto colIt = rowIt->begin(); colIt != rowIt->end(); colIt++)
		{
			if (*colIt != nullptr)
			{
				delete *colIt;
				*colIt = nullptr;
			}
		}
	}
}

void Map::save(const char *dataPath)
{
	std::ofstream out(dataPath);

	if (!out.is_open())
		throw new std::exception("Failed to open map save path!");

	const ImageData &imageData = ImageData::instance();
	std::unordered_set<unsigned int> imageIds;
	std::vector<std::pair<unsigned int, bool>> tilePrefab;

	for (unsigned int row = 0; row < numRows_; row++)
	{
		for (unsigned int col = 0; col < numCols_; col++)
		{
			Tile *tile = tiles_.at(row).at(col);

			if (tile)
			{
				unsigned int imageId = tile->imageId();

				if (imageIds.find(imageId) == imageIds.cend())
				{
					imageIds.emplace(imageId);

					tilePrefab.push_back(std::make_pair(imageId, tile->isCollidable()));
				}
			}
		}
	}

	out << "@PREFAB_IMAGE" << std::endl;
	for (auto it = imageIds.cbegin(); it != imageIds.cend(); it++)
	{
		out
			<< *it << ","
			<< imageData.get(*it).sourceX() << ","
			<< imageData.get(*it).sourceY() << ","
			<< std::endl;
	}

	out << "@PREFAB_TILE" << std::endl;
	for (auto it = tilePrefab.cbegin(); it != tilePrefab.cend(); it++)
	{
		out
			<< it->first << ","
			<< it->first << ","
			<< it->second << ","
			<< std::endl;
	}

	out << "@MAP" << std::endl;
	out << numCols_ << "," << numRows_ << ",";
	for (unsigned int row = 0; row < numRows_; row++)
	{
		out << std::endl;

		for (unsigned int col = 0; col < numCols_; col++)
		{
			Tile *tile = tiles_.at(row).at(col);

			out << (tile ? tiles_.at(row).at(col)->imageId() : 0) << ",";
		}
	}

	out.close();
}

void Map::load(const char *dataPath)
{
	std::ifstream in(dataPath);

	if (!in.is_open())
		throw new std::exception("Failed to load map data file!");

	ImageData::instance().clear();

	enum class LoadState : uint8_t
	{
		None,
		PrefabImage,
		PrefabTile,
		Map
	};

	const std::unordered_map<std::string, LoadState> directors = {
		{ "@PREFAB_IMAGE", LoadState::PrefabImage },
		{ "@PREFAB_TILE", LoadState::PrefabTile },
		{ "@MAP", LoadState::Map }
	};

	std::unordered_map<unsigned int, Tile> tilePrefab;

	ALLEGRO_BITMAP *tileSheet = al_load_bitmap("img/tilesheet.png");
	LoadState loadState = LoadState::None;
	std::string line = "";
	std::stringstream ss;

	while (!in.eof())
	{
		std::getline(in, line);

		if (line.front() == '#')
			continue;

		if (line.front() == '@')
		{
			auto it = directors.find(line);

			if (it != directors.cend())
				loadState = it->second;

			continue;
		}

		switch (loadState)
		{
		case LoadState::None:
		{
			continue;
		}
		case LoadState::PrefabImage:
		{
			std::string part = "";
			unsigned int imageId = 0;
			unsigned int sourceX = 0;
			unsigned int sourceY = 0;

			ss.str(line);

			std::getline(ss, part, ',');
			imageId = std::stoi(part);

			std::getline(ss, part, ',');
			sourceX = std::stoi(part);

			std::getline(ss, part, ',');
			sourceY = std::stoi(part);

			ImageData::instance().put(
				imageId,
				new Image(
					tileSheet,
					sourceX, sourceY,
					Constants::tileSize, Constants::tileSize));
			break;
		}
		case LoadState::PrefabTile:
		{
			std::string part = "";
			unsigned int tileId = 0;
			unsigned int imageId = 0;
			bool isCollidable = false;

			ss.str(line);

			std::getline(ss, part, ',');
			tileId = std::stoi(part);

			std::getline(ss, part, ',');
			imageId = std::stoi(part);

			std::getline(ss, part, ',');
			isCollidable = std::stoi(part);

			tilePrefab.emplace(tileId, Tile(0.0f, 0.0f, imageId, Constants::tileScale, isCollidable));

			break;
		}
		case LoadState::Map:
		{
			std::string part = "";
			unsigned int tileId = 0;
			unsigned int row = 0;
			unsigned int col = 0;

			float trueTileSize = Constants::tileSize * Constants::tileScale;

			ss.str(line);

			std::getline(ss, part, ',');
			numCols_ = std::stoi(part);

			std::getline(ss, part, ',');
			numRows_ = std::stoi(part);

			tiles_ = std::vector<std::vector<Tile *>>(numRows_, std::vector<Tile *>(numCols_, nullptr));

			while (row < numRows_)
			{
				std::getline(in, line);
				ss.str(line);

				col = 0;
				while (col < numCols_)
				{
					std::getline(ss, part, ',');
					tileId = std::stoi(part);

					tiles_.at(row).at(col) = tilePrefab.at(tileId).clone(col * trueTileSize, row * trueTileSize);

					col++;
				}

				row++;
			}
			break;
		}
		}
	}

	in.close();

	al_destroy_bitmap(tileSheet);
	tileSheet = nullptr;
}

void Map::render(const Camera &camera) const
{
	unsigned int trueTileSize = Constants::tileSize * Constants::tileScale;

	float dX = 0.0f - camera.x();
	float dY = 0.0f - camera.y();
	float width = numCols_ * trueTileSize;
	float height = numRows_ * trueTileSize;

	for (auto rowIt = tiles_.cbegin(); rowIt != tiles_.cend(); rowIt++)
		for (auto colIt = rowIt->cbegin(); colIt != rowIt->cend(); colIt++)
			if (*colIt != nullptr)
				(*colIt)->render(camera);

	al_draw_rectangle(dX, dY, dX + width, dY + height, al_map_rgb(255, 0, 255), 2.0f);
}

void Map::put(unsigned int col, unsigned int row, unsigned int imageId, bool isCollidable)
{
	if (tiles_.at(row).at(col))
	{
		delete tiles_.at(row).at(col);
		tiles_.at(row).at(col) = nullptr;
	}

	if(imageId != 0)
	{
		tiles_.at(row).at(col) = new Tile(
			col * Constants::tileSize * Constants::tileScale,
			row * Constants::tileSize * Constants::tileScale,
			imageId,
			Constants::tileScale,
			isCollidable);
	}
}

unsigned int Map::calcCol(float x) const
{
	float trueTileSize = Constants::tileSize * Constants::tileScale;

	return x / trueTileSize;
}

unsigned int Map::calcRow(float y) const
{
	float trueTileSize = Constants::tileSize * Constants::tileScale;

	return y / trueTileSize;
}

bool Map::isInBounds(float x, float y) const
{
	float trueTileSize = Constants::tileSize * Constants::tileScale;

	unsigned int col = x / trueTileSize;
	unsigned int row = y / trueTileSize;

	return this->isInBounds(col, row);
}

bool Map::isInBounds(unsigned int col, unsigned int row) const
{
	return col >= 0
		&& col < numCols_
		&&row >= 0
		&& row < numRows_;
}

const std::vector<Tile *> Map::getTilesTouching(const AABB &aabb) const
{
	std::vector<Tile *> tiles;

	float tileSize = 16 * 4.0f;

	unsigned int minCol = aabb.x() / tileSize;
	unsigned int maxCol = (aabb.x() + aabb.width()) / tileSize;

	unsigned int minRow = aabb.y() / tileSize;
	unsigned int maxRow = (aabb.y() + aabb.height()) / tileSize;

	for (unsigned int row = minRow; row <= maxRow; row++)
		for (unsigned int col = minCol; col <= maxCol; col++)
			tiles.push_back(tiles_.at(row).at(col));

	return tiles;
}

const std::vector<Tile *> Map::getCollidableTilesTouching(const AABB &aabb) const
{
	std::vector<Tile *> tiles;

	float tileSize = 16 * 4.0f;

	unsigned int minCol = aabb.x() / tileSize;
	unsigned int maxCol = (aabb.x() + aabb.width()) / tileSize;

	unsigned int minRow = aabb.y() / tileSize;
	unsigned int maxRow = (aabb.y() + aabb.height()) / tileSize;

	for (unsigned int row = minRow; row <= maxRow; row++)
	{
		for (unsigned int col = minCol; col <= maxCol; col++)
		{
			Tile *suspect = tiles_.at(row).at(col);

			if (suspect && suspect->isCollidable())
				tiles.push_back(suspect);
		}
	}

	return tiles;
}