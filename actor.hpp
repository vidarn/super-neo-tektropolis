#ifndef ACTOR_Z8AAEZ5W
#define ACTOR_Z8AAEZ5W
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

enum
{
	ACTOR_STATIC,
	ACTOR_DYNAMIC
};

class FloorFeetCallback : public b2RayCastCallback
{
	public:
		FloorFeetCallback();
		float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction);
		bool m_hit;
};

class Actor {
	public:
		Actor(int x, int y, int w, int h, int type, b2World &world);
		virtual ~Actor();
		void draw(sf::RenderWindow &window);
		virtual void update(float dt);
		bool feetOnGround();
	protected:
		int m_x, m_y;
		int m_w, m_h;
		b2Body*   m_body;
		b2World  *m_world;
};

#endif /* end of include guard: ACTOR_Z8AAEZ5W */
