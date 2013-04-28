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
class Level;

class FloorFeetCallback : public b2RayCastCallback
{
	public:
		FloorFeetCallback();
		float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction);
		bool m_hit;
};

class ActorContactListener : public b2ContactListener
{
	public:
		ActorContactListener();
		void BeginContact(b2Contact * contact);
		void EndContact(b2Contact * contact);
};

class Actor {
	public:
		Actor(int x, int y, int w, int h, int type, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
		virtual ~Actor();
		virtual void draw(Camera *cam);
		virtual void update(float dt);
		bool feetOnGround();
		bool feetOnGround(int offset);
		int getX();
		int getY();
		void setX(float x);
		void setY(float y);
		virtual void getBeamed();
		virtual void collide(Actor *);
		bool m_dead;
		bool m_deadly;
	protected:
		void drawActor(Camera *cam, Actor *act);
		void drawActor(Camera *cam, Actor *act, int x, int y);
		int m_w, m_h;
		b2Body*   m_body;
		b2World  *m_world;
		Sprite   *m_sprite;
		Level    *m_level;
		SpriteFactory   *m_spriteFactory;
		boost::random::mt19937 *m_rng;
};

#endif /* end of include guard: ACTOR_Z8AAEZ5W */
