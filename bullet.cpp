#include "bullet.hpp"
#include "level.hpp"

Bullet::Bullet(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level, b2Vec2 vel):
	Actor(x,y,w,h,ACTOR_BULLET,world, spriteFactory, rng, level)
{
	m_sprite = m_spriteFactory->getSprite("flying_enemy/bullet01.png");
	m_vel = vel;
	m_deadly = true;
}

Bullet::~Bullet()
{
}

void
Bullet::update(float dt)
{
    m_body->SetLinearVelocity(m_vel);
}

void
Bullet::collide(Actor * actor)
{
	if(!actor->m_deadly){
		m_dead = true;
	}
}
