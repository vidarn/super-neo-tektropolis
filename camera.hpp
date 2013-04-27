#ifndef CAMERA_EUR3YBLD
#define CAMERA_EUR3YBLD
#include "actor.hpp"

enum {
	LAYER_FOREGROUND,
	LAYER_BACKGROUND
};

class Camera {
	public:
		Camera (Actor *target, sf::RenderWindow &window);
		virtual ~Camera ();
		void update(float dt);
		void draw(sf::Sprite *sprite, int x, int y, int layer, int scaling);
	private:
		Actor *m_target;
		sf::RenderWindow &m_window;
		float m_x, m_y;
};

#endif /* end of include guard: CAMERA_EUR3YBLD */
