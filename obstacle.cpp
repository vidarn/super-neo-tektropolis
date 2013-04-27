#include "obstacle.hpp"

Obstacle::Obstacle(int x, int y, int w, int h, b2World &world):
	Actor(x, y, w, h, ACTOR_STATIC, world)
{
}

Obstacle::~Obstacle()
{
}
