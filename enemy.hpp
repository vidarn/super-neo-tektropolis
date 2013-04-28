#ifndef ENEMY_ILU1WUZM
#define ENEMY_ILU1WUZM
#include "actor.hpp"

class Enemy : public Actor {
	public:
		Enemy(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
		virtual ~Enemy();
		void update(float dt);
		void getBeamed();
	private:
		bool  m_onGround;
		bool  m_flipped;
		float m_speed;
};

#endif /* end of include guard: ENEMY_ILU1WUZM */
