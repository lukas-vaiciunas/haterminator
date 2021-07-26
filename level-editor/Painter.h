#pragma once

class Mouse;
class Level;
class Camera;

class Painter
{
private:
	unsigned int imageId_;
	bool isCollidable_;
	bool isPlacingSpawn_;
public:
	Painter();

	void updateOnMousePress(const Mouse &mouse, Level &level, const Camera &camera);

	void render(const Mouse &mouse, const Level &level, const Camera &camera) const;

	void setImageId(unsigned int imageId);
	void setIsCollidable(bool isCollidable);
	void setIsPlacingSpawn(bool isPlacingSpawn);

	unsigned int imageId() const;
	bool isCollidable() const;
	bool isPlacingSpawn() const;
};