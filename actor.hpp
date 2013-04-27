#ifndef ACTOR_Z8AAEZ5W
#define ACTOR_Z8AAEZ5W
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

enum
{
	ACTOR_STATIC,
	ACTOR_DYNAMIC
};

class Actor {
	public:
		Actor(int x, int y, int w, int h, int type, b2World &world);
		virtual ~Actor();
		void draw(sf::RenderWindow &window);
		virtual void update(float dt);
	protected:
		int m_x, m_y;
		int m_w, m_h;
		b2Body*     m_body;
};

#endif /* end of include guard: ACTOR_Z8AAEZ5W */
