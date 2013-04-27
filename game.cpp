#include "game.hpp"
#include <iostream>

Game::Game(const std::string &title, int w, int h):
    m_w(w), m_h(h)
{
    m_window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Close);
    m_rng = new boost::random::mt19937();
    m_spriteFactory = new SpriteFactory();
}

Game::~Game()
{
}

int
Game::run()
{
    start();
    m_clock.restart();
    std::cout << "Hello world" << std::endl;
    while (m_window->isOpen())
    {
        sf::Time time = m_clock.getElapsedTime();
        m_clock.restart();
        float dt = time.asSeconds();
        input();
        update(dt);
        draw();
    }
    end();
}

void
Game::draw()
{
    m_window->clear(sf::Color(59,134,134));
    m_level->draw(*m_window);
    m_window->display();
}

void
Game::update(float dt)
{
    m_level->update(dt);
}

void
Game::input()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
         if (event.type == sf::Event::Closed)
             m_window->close();
         if (event.type == sf::Event::KeyPressed){
             bool handled = false;
             switch(event.key.code){
                 case sf::Keyboard::R:
                     restart();
                     handled = true;
                     break;
             }
             if(!handled){
                 m_level->keyPressed(event.key.code);
             }
         }
    }
}


void
Game::start()
{
    m_level = new Level(m_rng, m_spriteFactory, *m_window);
}

void
Game::end()
{
    delete m_level;
}

void
Game::restart()
{
    end();
    start();
}

