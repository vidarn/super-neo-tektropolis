#ifndef EXPLOSION_NWFY6AWN
#define EXPLOSION_NWFY6AWN
#include "actor.hpp"

class Explosion:public Actor{
	public:
		Explosion (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
		virtual ~Explosion ();
		void update(float dt);
	private:
};

#endif /* end of include guard: EXPLOSION_NWFY6AWN */
