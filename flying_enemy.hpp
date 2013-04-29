#ifndef FLYING_ENEMY_VPSSX0K7
#define FLYING_ENEMY_VPSSX0K7
#include "actor.hpp"

class LOSCallback : public b2RayCastCallback
{
	public:
		LOSCallback(Actor *actor);
		float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction);
		Actor *m_target;
		bool   m_blocked;
};

class FlyingEnemy:public Actor{
    public:
        FlyingEnemy (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
        virtual ~FlyingEnemy ();
        void update(float dt);
        void getBeamed();
        void collide(Actor *actor);
    private:
        b2Vec2 m_vel;
        float m_bulletCooldown;
        float m_dirCooldown;
        bool  m_flipped;
};

#endif /* end of include guard: FLYING_ENEMY_VPSSX0K7 */
