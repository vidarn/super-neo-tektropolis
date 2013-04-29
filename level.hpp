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
#include "chunk.hpp"

class ObstacleIntersectionCallback: public b2QueryCallback {
    public:
        ObstacleIntersectionCallback(Actor *ignore);
        bool ReportFixture(b2Fixture *fixture);
        bool m_empty;
        Actor *m_ignore;
};

class Level {
	public:
		Level(boost::random::mt19937 *rng, SpriteFactory *spriteFactory, sf::RenderWindow &window);
		virtual ~Level ();
        void addActor(Actor *actor);
		void draw(sf::RenderWindow &window);
		void update(float dt);
		void keyPressed(int key);
		void addScore(int amount);
		void cleanUpActors();
		Actor *getPlayer();
		Player *m_player;
		b2World *m_world;
		SpriteFactory *m_spriteFactory;
		bool m_valid;
	private:
		void generate();
        std::vector<Actor *> m_actors;
        std::vector<Actor *> m_newActors;
        std::vector<Chunk *> m_chunks;
		Sprite *m_numbers[5];
		boost::random::mt19937 *m_rng;
		Camera *m_camera;
		ActorContactListener *m_contactListener;
		int m_score;
};

#endif /* end of include guard: LEVEL_ZR61NK6F */
