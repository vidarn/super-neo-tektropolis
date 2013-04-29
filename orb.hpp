#ifndef ORB_V0DQAFOK
#define ORB_V0DQAFOK
#include "actor.hpp"

class Orb: public Actor {
    public:
        Orb(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level);
        ~Orb();
        void collide(Actor *actor);
};

#endif /* end of include guard: ORB_V0DQAFOK */
