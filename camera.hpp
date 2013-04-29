#ifndef CAMERA_EUR3YBLD
#define CAMERA_EUR3YBLD
#include "actor.hpp"

enum {
	LAYER_FOREGROUND,
	LAYER_BACKGROUND
};

class Camera {
	public:
		Camera (Actor *target, sf::RenderWindow &window, boost::random::mt19937 *rng);
		virtual ~Camera ();
		void update(float dt);
		void draw(sf::Sprite *sprite, int x, int y, int layer, int scaling, bool absolute);
		void setShake(float shake);
	private:
		Actor *m_target;
		sf::RenderWindow &m_window;
		float m_x, m_y;
		float m_shake;
		float m_shakeX, m_shakeY;
		boost::random::mt19937 *m_rng;
};

#endif /* end of include guard: CAMERA_EUR3YBLD */
