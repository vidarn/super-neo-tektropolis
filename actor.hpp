#ifndef ACTOR_Z8AAEZ5W
#define ACTOR_Z8AAEZ5W
#include <SFML/Graphics.hpp>

class Actor {
	public:
		Actor(int x, int y, int w, int h);
		virtual ~Actor();
		void draw(sf::RenderWindow &window);
		void update(float dt);
	protected:
		int m_x, m_y;
		int m_w, m_h;
};

#endif /* end of include guard: ACTOR_Z8AAEZ5W */
