#include "game.hpp"
#include <iostream>
#include <boost/foreach.hpp>

Game::Game(const std::string &title, int w, int h):
    m_w(w), m_h(h)
{
    m_window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Close);
}

Game::~Game()
{
    BOOST_FOREACH(Actor *actor, m_actors){
        delete actor;
    }
}

int
Game::run()
{
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
}

void
Game::draw()
{
    m_window->clear();
    m_window->display();
}

void
Game::update(float dt)
{
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
             if(event.key.code == sf::Keyboard::J)
                 std::cout << "J!" << std::endl;
         }
    }
}

void 
Game::addActor(Actor *actor)
{
    m_actors.push_back(actor);
}
