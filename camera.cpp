#include <algorithm>
#include "camera.hpp"

Camera::Camera(Actor *target, sf::RenderWindow &window):
	m_target(target), m_window(window), m_x(0), m_y(0)
{
}

Camera::~Camera()
{
}

void
Camera::update(float dt)
{
	int border = 70;
	int x = m_target->getX();
	int leftBorder  = x - border;
	int rightBorder = x + border;
	m_x = std::min(rightBorder,std::max(leftBorder,int(m_x)));

	border = 20;
	int y = -m_target->getY();
	leftBorder  = y - border;
	rightBorder = y + border;
	m_y = std::min(rightBorder,std::max(leftBorder,int(m_y)));
}

void
Camera::draw(sf::Sprite *sprite, int x, int y, int layer, int scaling)
{
	int offsetX = 200 - m_x;
	int offsetY = 150 + m_y;
	if(layer == LAYER_BACKGROUND){
		offsetX = offsetX*0.5;
		offsetY = offsetY*0.5;
	}
	sprite->setPosition((x + offsetX)*scaling, (y + offsetY)*scaling);
	m_window.draw(*sprite);
}

