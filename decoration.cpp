#include <boost/random/uniform_int_distribution.hpp>
#include "decoration.hpp"

Decoration::Decoration(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, const std::string &name, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h, ACTOR_GHOST, world, spriteFactory, rng, level)
{
	if(name == "cloud"){
		int variant = boost::random::uniform_int_distribution<>(0,1)(*m_rng);
		switch(variant){
			case 0: m_sprite = m_spriteFactory->getSprite("cloud/cloud01.png"); break;
			case 1: m_sprite = m_spriteFactory->getSprite("cloud/cloud02.png"); break;
			case 2: m_sprite = m_spriteFactory->getSprite("cloud/cloud03.png"); break;
		}
		m_sprite->setBackground();
	}
}

Decoration::~Decoration()
{
}
