#include "game.hpp"
#include <iostream>

Game::Game(const std::string &title, int w, int h):
    m_w(w), m_h(h)
{
    m_window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Close);
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
    m_window->clear();
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
             switch(event.key.code){
                 case sf::Keyboard::J:
                     std::cout << "J!" << std::endl;
                     break;
                 case sf::Keyboard::R:
                     restart();
                     break;
             }
         }
    }
}


void
Game::start()
{
    m_level = new Level();
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

