#ifndef BULLET_YXIA2IQ4
#define BULLET_YXIA2IQ4
#include "actor.hpp"

class Bullet: public Actor {
	public:
		Bullet(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level, b2Vec2 vel);
		virtual ~Bullet();
		void update(float dt);
		void collide(Actor *actor);
	private:
		b2Vec2 m_vel;
};

#endif /* end of include guard: BULLET_YXIA2IQ4 */
