#include "Level.h"

#include <allegro5/allegro_primitives.h>
#include <fstream>
#include <string>
#include <sstream>
#include "Constants.h"
#include "Camera.h"

Level::Level(
	const char *savePath,
	const char *mapSavePath,
	unsigned int numCols,
	unsigned int numRows)
	:
	savePath_(savePath),
	mapSavePath_(mapSavePath),
	map_(numCols, numRows),
	playerSpawnCol_(0),
	playerSpawnRow_(0)
{
	this->load(savePath);
}

void Level::save()
{
	std::ofstream out(savePath_);

	if (!out.is_open())
		throw new std::exception("Failed to open level save path!");

	out << "@PLAYER_SPAWN" << std::endl;
	out << playerSpawnCol_ << "," << playerSpawnRow_ << "," << std::endl;
	out << "@MAP_PATH" << std::endl;
	out << mapSavePath_ << ",";

	out.close();

	map_.save(mapSavePath_);
}

void Level::load(const char *dataPath)
{
	std::ifstream in(dataPath);

	if (!in.is_open())
		throw std::exception("Failed to open level data path!");

	enum class State : uint8_t
	{
		None,
		PlayerSpawn,
		MapPath
	};

	State state = State::None;
	std::string line = "";
	std::stringstream ss;
	std::string mapDataPath = "";

	while (!in.eof())
	{
		std::getline(in, line);

		if (line.front() == '@')
		{
			if (line == "@PLAYER_SPAWN")
			{
				state = State::PlayerSpawn;
			}
			else if (line == "@MAP_PATH")
			{
				state = State::MapPath;
			}
			continue;
		}

		switch (state)
		{
		case State::None:
		{
			break;
		}
		case State::PlayerSpawn:
		{
			std::string part = "";

			ss.str(line);

			std::getline(ss, part, ',');
			playerSpawnCol_ = std::stoi(part);

			std::getline(ss, part, ',');
			playerSpawnRow_ = std::stoi(part);

			break;
		}
		case State::MapPath:
		{
			std::string part = "";

			ss.str(line);

			std::getline(ss, part, ',');
			mapDataPath = part;

			break;
		}
		}
	}

	in.close();

	map_.load(mapDataPath.c_str());
}

void Level::render(const Camera &camera) const
{
	map_.render(camera);

	float trueTileSize = Constants::tileSize * Constants::tileScale;
	float playerSpawnX = playerSpawnCol_ * trueTileSize - camera.x();
	float playerSpawnY = playerSpawnRow_ * trueTileSize - camera.y();

	al_draw_rectangle(
		playerSpawnX, playerSpawnY,
		playerSpawnX + trueTileSize, playerSpawnY + trueTileSize,
		al_map_rgb(255, 255, 0),
		2.0f);
}

void Level::setPlayerSpawn(unsigned int col, unsigned int row)
{
	playerSpawnCol_ = col;
	playerSpawnRow_ = row;
}

Map &Level::map()
{
	return map_;
}

const Map &Level::map() const
{
	return map_;
}