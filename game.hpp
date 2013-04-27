#ifndef GAME_76B6OLNJ
#define GAME_76B6OLNJ
#include <string>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "actor.hpp"

class Game {
    public:
        Game(const std::string &title, int w, int h);
        virtual ~Game();
        int run();
    private:
        void draw();
        void update(float dt);
        void input();
        void addActor(Actor *actor);
        int m_w, m_h;
        sf::RenderWindow *m_window;
        sf::Clock m_clock;
        std::vector<Actor *> m_actors;
};

#endif /* end of include guard: GAME_76B6OLNJ */
