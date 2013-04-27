#ifndef ACTOR_Z8AAEZ5W
#define ACTOR_Z8AAEZ5W
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <boost/random/mersenne_twister.hpp>
#include "sprite_factory.hpp"

enum
{
	ACTOR_STATIC,
	ACTOR_GHOST,
	ACTOR_DYNAMIC
};

class Camera;

class FloorFeetCallback : public b2RayCastCallback
{
	public:
		FloorFeetCallback();
		float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction);
		bool m_hit;
};

class Actor {
	public:
		Actor(int x, int y, int w, int h, int type, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng);
		virtual ~Actor();
		void draw(Camera *cam);
		virtual void update(float dt);
		bool feetOnGround();
		int getX();
		int getY();
	protected:
		int m_w, m_h;
		b2Body*   m_body;
		b2World  *m_world;
		Sprite   *m_sprite;
		SpriteFactory   *m_spriteFactory;
		boost::random::mt19937 *m_rng;
};

#endif /* end of include guard: ACTOR_Z8AAEZ5W */
