#include "beam.hpp"

Beam::Beam(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, bool large):
	Actor(x,y,w,h,ACTOR_GHOST,world, spriteFactory, rng)
{
	if(large)
		m_sprite = m_spriteFactory->getSprite("player/large_beam.png");
	else
		m_sprite = m_spriteFactory->getSprite("player/small_beam.png");
	m_sprite->setScale(w,1.0f);
}

Beam::~Beam()
{
}
