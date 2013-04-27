#include "actor.hpp"

Actor::Actor(int x, int y, int w, int h):
	m_x(x), m_y(y), m_w(w), m_h(h)
{
}

Actor::~Actor()
{
}

void
Actor::draw(sf::RenderWindow &window)
{
    sf::RectangleShape bodyShape;
    bodyShape.setPosition(m_x,m_y);
    bodyShape.setSize(sf::Vector2f(m_w,m_h));
	window.draw(bodyShape);
}

void
Actor::update(float dt)
{
}

