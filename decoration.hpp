#ifndef DECORATION_QY0Q9VTM
#define DECORATION_QY0Q9VTM
#include "actor.hpp"

class Decoration: public Actor{
public:
	Decoration (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, const std::string &name, boost::random::mt19937 *rng, Level *level);
	virtual ~Decoration ();

private:
	/* data */
};

#endif /* end of include guard: DECORATION_QY0Q9VTM */
