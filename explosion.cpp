#include "explosion.hpp"

Explosion::Explosion(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level,const std::string &name, bool flipped):
	Actor(x,y,w,h,ACTOR_GHOST,world, spriteFactory, rng, level)
{
	std::vector<std::string> frames;
    if(name == "enemy"){
        frames.push_back("enemy/explode01.png");
        frames.push_back("enemy/explode02.png");
        frames.push_back("enemy/explode03.png");
        frames.push_back("enemy/explode04.png");
        frames.push_back("enemy/explode05.png");
        frames.push_back("enemy/explode06.png");
        frames.push_back("enemy/explode07.png");
        frames.push_back("enemy/explode07.png");
    }
    if(name == "flying enemy"){
        frames.push_back("flying_enemy/explode01.png");
        frames.push_back("flying_enemy/explode02.png");
        frames.push_back("flying_enemy/explode03.png");
        frames.push_back("flying_enemy/explode04.png");
        frames.push_back("flying_enemy/explode05.png");
        frames.push_back("flying_enemy/explode06.png");
        frames.push_back("flying_enemy/explode07.png");
        frames.push_back("flying_enemy/explode07.png");
    }
	m_sprite = m_spriteFactory->getSprite(frames);
	m_sprite->setLoop(false);
    m_sprite->setFlipped(flipped);
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
