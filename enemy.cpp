#include "enemy.hpp"
#include "explosion.hpp"
#include "level.hpp"

Enemy::Enemy(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world, spriteFactory, rng, level)
{
	std::vector<std::string> frames;
	frames.push_back("enemy/enemy01.png");
	frames.push_back("enemy/enemy02.png");
	frames.push_back("enemy/enemy03.png");
	frames.push_back("enemy/enemy04.png");
	frames.push_back("enemy/enemy05.png");
	m_sprite = m_spriteFactory->getSprite(frames);
	m_flipped = false;
	m_speed = 1.4;
	m_deadly = true;
}

Enemy::~Enemy()
{
}

void
Enemy::update(float dt)
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    vel.x = 0;
	if(m_flipped)
		m_onGround = feetOnGround(-15);
	else
		m_onGround = feetOnGround( 15);
	if(m_onGround){
		if(m_flipped)
			vel.x += m_speed;
		else
			vel.x -= m_speed;
	}
	else{
		m_flipped = !m_flipped;
	}
    m_body->SetLinearVelocity(vel);
	m_sprite->setFlipped(m_flipped);
	m_sprite->update(dt);
}

void
Enemy::getBeamed(){
	m_dead = true;
	m_level->addActor(new Explosion(getX(), getY()-16, 10, 10, *m_world, m_spriteFactory, m_rng, m_level, "enemy", m_flipped));
}

