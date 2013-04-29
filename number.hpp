#ifndef NUMBER_21PRE6KW
#define NUMBER_21PRE6KW
#include "actor.hpp"

class Number: public Actor {
	public:
		Number(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
		~Number();
		void set(int number);
};

#endif /* end of include guard: NUMBER_21PRE6KW */
