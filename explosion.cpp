#include "explosion.hpp"

Explosion::Explosion(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h,ACTOR_GHOST,world, spriteFactory, rng, level)
{
	std::vector<std::string> frames;
	frames.push_back("enemy/explode01.png");
	frames.push_back("enemy/explode02.png");
	frames.push_back("enemy/explode03.png");
	frames.push_back("enemy/explode04.png");
	frames.push_back("enemy/explode05.png");
	frames.push_back("enemy/explode06.png");
	frames.push_back("enemy/explode07.png");
	frames.push_back("enemy/explode07.png");
	m_sprite = m_spriteFactory->getSprite(frames);
	m_sprite->setLoop(false);
}

Explosion::~Explosion()
{
}

void
Explosion::update(float dt)
{
	m_sprite->update(dt);
	if(m_sprite->getFrame() == 7){
		m_dead = true;
	}
}
