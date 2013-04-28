#include "obstacle.hpp"

Obstacle::Obstacle(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x, y, w, h, ACTOR_STATIC, world, spriteFactory, rng, level)
{
	m_sprite = m_spriteFactory->getSprite("platform/medium_tech01.png");
}

Obstacle::~Obstacle()
{
}
