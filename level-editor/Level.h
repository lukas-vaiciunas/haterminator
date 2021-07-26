#pragma once

#include "Map.h"

class Level
{
private:
	const char *savePath_;
	const char *mapSavePath_;
	Map map_;
	unsigned int playerSpawnCol_;
	unsigned int playerSpawnRow_;
public:
	Level(
		const char *savePath,
		const char *mapSavePath,
		unsigned int numCols,
		unsigned int numRows);

	void save();
	void load(const char *dataPath);

	void render(const Camera &camera) const;

	void setPlayerSpawn(unsigned int col, unsigned int row);

	Map &map();
	const Map &map() const;
};