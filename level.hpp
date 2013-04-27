#ifndef LEVEL_ZR61NK6F
#define LEVEL_ZR61NK6F
#include <boost/random/mersenne_twister.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "actor.hpp"
#include "player.hpp"

class Level {
	public:
		Level(boost::random::mt19937 *rng);
		virtual ~Level ();
        void addActor(Actor *actor);
		void draw(sf::RenderWindow &window);
		void update(float dt);
	private:
		void generate();
        std::vector<Actor *> m_actors;
		Player *m_player;
		b2World *m_world;
		boost::random::mt19937 *m_rng;
};

#endif /* end of include guard: LEVEL_ZR61NK6F */
