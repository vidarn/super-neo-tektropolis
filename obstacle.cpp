#include "obstacle.hpp"

Obstacle::Obstacle(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level, const  std::string &size):
	Actor(x, y, w, h, ACTOR_STATIC, world, spriteFactory, rng, level)
{
	if(size == "medium"){
		m_sprite = m_spriteFactory->getSprite("platform/medium_tech01.png");
	}
	if(size == "large"){
		m_sprite = m_spriteFactory->getSprite("platform/large_tech01.png");
	}
}

Obstacle::~Obstacle()
{
}
