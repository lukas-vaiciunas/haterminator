#include "Level.h"

#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include "Constants.h"
#include "ParticlePool.h"
#include "FontData.h"
#include "Config.h"
#include "Keyboard.h"
#include "EventQueue.h"
#include "Event.h"

Level::Level(
	const char *dataPath,
	const CharacterAnimations &playerAnimations,
	unsigned int maxNumEnemies)
	:
	Pool(maxNumEnemies),
	Listener({ EventType::Loss, EventType::Win }),
	player_(nullptr),
	bulletPool_(100),
	particlePool_(ParticlePool::instance()),
	camera_(0.0f, 0.0f),
	waveNum_(0)
{
	ALLEGRO_BITMAP *enemySheet = al_load_bitmap("img/enemy-1.png");
	enemyAnimations_ = CharacterAnimations(enemySheet, 0.15f);
	al_destroy_bitmap(enemySheet);
	enemySheet = nullptr;

	this->load(dataPath, playerAnimations);
}

Level::~Level()
{
	delete player_;
	player_ = nullptr;
}

void Level::onEvent(const Event &ev)
{
	switch (ev.eventType())
	{
	case EventType::Loss:
		state_ = State::Loss;
		break;
	case EventType::Win:
		state_ = State::Win;
		break;
	}
}

void Level::load(const char *dataPath, const CharacterAnimations &animations)
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
	unsigned int playerSpawnCol = 0;
	unsigned int playerSpawnRow = 0;
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
			playerSpawnCol = std::stoi(part);

			std::getline(ss, part, ',');
			playerSpawnRow = std::stoi(part);

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

	float trueTileSize = Constants::tileSize * Constants::tileScale;

	player_ = new Player(
		playerSpawnCol * trueTileSize, playerSpawnRow * trueTileSize,
		100.0f,
		3.0f,
		0.2f,
		animations,
		Constants::tileScale);

	map_.load(mapDataPath.c_str());
}

void Level::updateOnTick(const Keyboard &keyboard, const Mouse &mouse)
{
	player_->updateOnTick(keyboard, mouse, map_, camera_, bulletPool_);
	camera_.centerOn(*player_);
	bulletPool_.updateOnTick();
	particlePool_.updateOnTick();

	if (this->empty())
	{
		if (waveNum_ == 5)
		{
			EventQueue::instance().send(new EventWin());
		}
		else
		{
			this->spawnEnemies_(++waveNum_);
		}
	}

	for (unsigned int i = 0; i < numLive_; )
	{
		Enemy *enemy = objects_.at(i);

		enemy->updateOnTick(*player_, map_, bulletPool_);

		if (!enemy->isLive())
		{
			this->removeAt_(i);
		}
		else
		{
			i++;
		}
	}
}

void Level::updateOnKeyPress(const Keyboard &keyboard)
{
	if (state_ == State::Loss || state_ == State::Win)
		if (keyboard.isPressed(Key::Space))
			EventQueue::instance().send(new EventChangeDriverState(DriverState::Menu));
}

void Level::render() const
{
	map_.render(camera_);
	particlePool_.render(camera_);
	bulletPool_.render(camera_);

	for (auto it = this->cbegin(); it != this->cend(); it++)
		(*it)->render(camera_);

	player_->render(camera_);

	switch (state_)
	{
	case State::Win:
		FontData::instance().renderText(
			Config::displayWidth * 0.5f,
			Config::displayHeight * 0.25f,
			"You Win!",
			128,
			al_map_rgb(225, 225, 225),
			ALLEGRO_ALIGN_CENTER,
			FontData::TextFlags::CenterVertically);

		FontData::instance().renderText(
			Config::displayWidth * 0.5f,
			Config::displayHeight * 0.25f + 64.0f,
			"Press [SPACE] to return to the main menu.",
			32,
			al_map_rgb(225, 225, 225),
			ALLEGRO_ALIGN_CENTER,
			FontData::TextFlags::CenterVertically);
		break;
	case State::Loss:
		FontData::instance().renderText(
			Config::displayWidth * 0.5f,
			Config::displayHeight * 0.25f,
			"Game Over.",
			128,
			al_map_rgb(225, 225, 225),
			ALLEGRO_ALIGN_CENTER,
			FontData::TextFlags::CenterVertically);

		FontData::instance().renderText(
			Config::displayWidth * 0.5f,
			Config::displayHeight * 0.25f + 64.0f,
			"Press [SPACE] to return to the main menu.",
			32,
			al_map_rgb(225, 225, 225),
			ALLEGRO_ALIGN_CENTER,
			FontData::TextFlags::CenterVertically);
		break;
	}
}

const Player &Level::player() const
{
	return *player_;
}

void Level::spawnEnemies_(unsigned int numEnemies)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<unsigned int> colDis(1, map_.numCols() - 2);
	std::uniform_int_distribution<unsigned int> rowDis(1, map_.numRows() - 2);

	float trueTileSize = Constants::tileSize * Constants::tileScale;

	

	for (unsigned int i = 0; i < numEnemies; i++)
	{
		unsigned int col = colDis(eng);
		unsigned int row = rowDis(eng);

		float x = col * trueTileSize;
		float y = row * trueTileSize;

		this->add(
			new Enemy(
				x, y,
				512.0f,
				128.0f,
				64.0f,
				1024.0f,
				20.0f,
				3.0f,
				0.5f,
				enemyAnimations_,
				Constants::tileScale));
	}
}