#ifndef LEVEL_ZR61NK6F
#define LEVEL_ZR61NK6F
#include <vector>
#include <SFML/Graphics.hpp>
#include "actor.hpp"

class Level {
	public:
		Level();
		virtual ~Level ();
        void addActor(Actor *actor);
		void draw(sf::RenderWindow &window);
		void update(float dt);
	private:
		void generate();
        std::vector<Actor *> m_actors;
		Actor *m_player;
};

#endif /* end of include guard: LEVEL_ZR61NK6F */
