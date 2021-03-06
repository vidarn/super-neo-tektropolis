#ifndef GAME_76B6OLNJ
#define GAME_76B6OLNJ
#include <string>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "level.hpp"
#include "sprite_factory.hpp"

class Game {
    public:
        Game(const std::string &title, int w, int h);
        virtual ~Game();
        int run();
    private:
        void draw();
        void update(float dt);
        void input();
        void start();
        void end();
        void restart();
        int m_w, m_h;
        sf::RenderWindow *m_window;
        sf::Clock m_clock;
        Level *m_level;
        boost::random::mt19937 *m_rng;
        SpriteFactory *m_spriteFactory;
};

#endif /* end of include guard: GAME_76B6OLNJ */
