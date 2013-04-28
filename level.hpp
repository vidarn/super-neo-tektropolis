#ifndef LEVEL_ZR61NK6F
#define LEVEL_ZR61NK6F
#include <boost/random/mersenne_twister.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "actor.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "sprite_factory.hpp"

class Level {
	public:
		Level(boost::random::mt19937 *rng, SpriteFactory *spriteFactory, sf::RenderWindow &window);
		virtual ~Level ();
        void addActor(Actor *actor);
		void draw(sf::RenderWindow &window);
		void update(float dt);
		void keyPressed(int key);
	private:
		void generate();
		void cleanUpActors();
        std::vector<Actor *> m_actors;
        std::vector<Actor *> m_newActors;
		Player *m_player;
		b2World *m_world;
		boost::random::mt19937 *m_rng;
		SpriteFactory *m_spriteFactory;
		Camera *m_camera;
		ActorContactListener *m_contactListener;
		bool m_valid;
};

#endif /* end of include guard: LEVEL_ZR61NK6F */
