#ifndef BEAM_67W2WMFQ
#define BEAM_67W2WMFQ
#include "actor.hpp"

class Beam: public Actor{
	public:
		Beam (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory,
			boost::random::mt19937 *rng, bool large);
		virtual ~Beam ();
	private:
};

#endif /* end of include guard: BEAM_67W2WMFQ */
