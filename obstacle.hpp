#ifndef OBSTACLE_WW1Z91LE
#define OBSTACLE_WW1Z91LE
#include "actor.hpp"

class Obstacle : public Actor{
	public:
		Obstacle (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
		virtual ~Obstacle ();
};

#endif /* end of include guard: OBSTACLE_WW1Z91LE */
