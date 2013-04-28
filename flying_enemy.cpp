#include <boost/random/uniform_real.hpp>
#include "flying_enemy.hpp"
#include "explosion.hpp"
#include "bullet.hpp"
#include "level.hpp"

FlyingEnemy::FlyingEnemy(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world, spriteFactory, rng, level)
{
	m_sprite = m_spriteFactory->getSprite("enemy/enemy03.png");
    m_deadly = true;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_bulletCooldown = 0.0f;
}

FlyingEnemy::~FlyingEnemy()
{
}

void
FlyingEnemy::update(float dt)
{
    boost::uniform_real<float> velDist(-1.0f,1.0f);
    b2Vec2 dVel;
    dVel.x = velDist(*m_rng);
    dVel.y = velDist(*m_rng);
    m_vel += 0.3 * dVel;
    m_vel.Normalize();
    m_body->SetLinearVelocity(m_vel);

    if(m_bulletCooldown <= 0.0f){
        Actor *player = m_level->getPlayer();
        int dx = player->getX() - getX();
        int dy = player->getY() - getY();
        b2Vec2 vel(dx,dy);
        vel.Normalize();
        vel *= 3.0f;
        b2Vec2 point1 = m_body->GetPosition();
        b2Vec2 point2 = player->m_body->GetPosition();
        LOSCallback callback(player);
        m_world->RayCast(&callback, point1, point2);
        if(!callback.m_blocked){
            m_sprite->setFlipped(dx > 0);
            m_level->addActor(new Bullet(getX(), getY()-16, 3, 3, *m_world, m_spriteFactory, m_rng, m_level, vel));
            m_bulletCooldown = 2.0f;
        }
    }

    m_bulletCooldown = std::max(0.0f, m_bulletCooldown - dt);
}

void
FlyingEnemy::getBeamed(){
	m_dead = true;
	m_level->addActor(new Explosion(getX(), getY()-16, 10, 10, *m_world, m_spriteFactory, m_rng, m_level));
}

void
FlyingEnemy::collide(Actor * actor)
{
    boost::uniform_real<float> velDist(-1.0f,1.0f);
    m_vel.x = velDist(*m_rng);
    m_vel.y = velDist(*m_rng);
    m_vel.Normalize();
}

LOSCallback::LOSCallback(Actor *target):
    m_target(target), m_blocked(false)
{
}

float32
LOSCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
{
	if(static_cast<Actor *>(fixture->GetUserData()) != m_target)
    {
        m_blocked = true;
        return 0.0f;
    }
	return 1.0f;
}

