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
	float numCols_;
	float numRows_;
public:
	Map(unsigned int numCols, unsigned int numRows);
	Map(const char *dataPath);
	~Map();

	void save(const char *dataPath);
	void load(const char *dataPath);

	void render(const Camera &camera) const;

	void put(unsigned int col, unsigned int row, unsigned int imageId, bool isCollidable);

	unsigned int calcCol(float x) const;
	unsigned int calcRow(float y) const;
	bool isInBounds(float x, float y) const;
	bool isInBounds(unsigned int col, unsigned int row) const;

	const std::vector<Tile *> getTilesTouching(const AABB &aabb) const;
	const std::vector<Tile *> getCollidableTilesTouching(const AABB &aabb) const;
};