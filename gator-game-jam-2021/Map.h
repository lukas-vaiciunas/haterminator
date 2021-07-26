#pragma once

class Tile;
class Camera;
class AABB;

#include <unordered_map>
#include <vector>
#include "Tile.h"

class Map
{
private:
	std::vector<std::vector<Tile *>> tiles_;
	unsigned int numCols_;
	unsigned int numRows_;
public:
	Map();
	Map(const char *dataPath);
	~Map();

	void load(const char *dataPath);

	void render(const Camera &camera) const;

	const std::vector<Tile *> getTilesTouching(const AABB &aabb) const;
	const std::vector<Tile *> getCollidableTilesTouching(const AABB &aabb) const;

	unsigned int numCols() const;
	unsigned int numRows() const;
};