#include "number.hpp"

Number::Number(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world, spriteFactory, rng, level)
{
	std::vector<std::string> frames;
	frames.push_back("number/01.png");
	frames.push_back("number/02.png");
	frames.push_back("number/03.png");
	frames.push_back("number/04.png");
	frames.push_back("number/05.png");
	frames.push_back("number/06.png");
	frames.push_back("number/07.png");
	frames.push_back("number/08.png");
	frames.push_back("number/09.png");
	frames.push_back("number/10.png");
	m_sprite = m_spriteFactory->getSprite(frames);
}

Number::~Number()
{
}

void
Number::set(int number)
{
	m_sprite->setFrame(number);
}
