#include "Map.h"

#include <fstream>
#include <string>
#include <sstream>
#include "ImageData.h"
#include "Image.h"
#include "Constants.h"

Map::Map() :
	numCols_(0),
	numRows_(0)
{}

Map::Map(const char *dataPath) :
	numCols_(0),
	numRows_(0)
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

		if (line.front() ==  '#')
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

			tilePrefab.emplace(tileId, Tile(0.0f, 0.0f, imageId, 4.0f, isCollidable));

			break;
		}
		case LoadState::Map:
		{
			std::string part = "";
			unsigned int tileId = 0;
			unsigned int row = 0;
			unsigned int col = 0;

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

					tiles_.at(row).at(col) = tilePrefab.at(tileId).clone(col * 64.0f, row * 64.0f);

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
	for (auto rowIt = tiles_.cbegin(); rowIt != tiles_.cend(); rowIt++)
		for (auto colIt = rowIt->cbegin(); colIt != rowIt->cend(); colIt++)
			if (*colIt != nullptr)
				(*colIt)->render(camera);
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

unsigned int Map::numCols() const
{
	return numCols_;
}

unsigned int Map::numRows() const
{
	return numRows_;
}