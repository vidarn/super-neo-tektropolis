#include "orb.hpp"
#include "level.hpp"

Orb::Orb(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h,ACTOR_GHOST,world, spriteFactory, rng, level)
{
	std::vector<std::string> frames;
	frames.push_back("orb/orb01.png");
	frames.push_back("orb/orb02.png");
	frames.push_back("orb/orb03.png");
	frames.push_back("orb/orb04.png");
	frames.push_back("orb/orb05.png");
	m_sprite = m_spriteFactory->getSprite(frames);
}

Orb::~Orb()
{
}

void
Orb::collide(Actor *actor)
{
	if(actor == m_level->getPlayer()){
		m_dead = true;
        m_level->addScore(470);
	}
}
