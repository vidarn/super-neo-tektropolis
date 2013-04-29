#include <algorithm>
#include <boost/random/uniform_real.hpp>
#include "camera.hpp"

Camera::Camera(Actor *target, sf::RenderWindow &window, boost::random::mt19937 *rng):
	m_target(target), m_window(window), m_x(0), m_y(0), m_rng(rng), m_shake(0.0f)
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

	if(m_shake > 0.0f){
		boost::uniform_real<float> shakeDist(-m_shake,m_shake);
		m_shakeX = shakeDist(*m_rng);
		m_shakeY = shakeDist(*m_rng);
	}
	else{
		m_shakeX = 0;
		m_shakeY = 0;
	}
}

void
Camera::draw(sf::Sprite *sprite, int x, int y, int layer, int scaling, bool absolute)
{
	int offsetX = 0;
	int offsetY = 0;
	if(!absolute){
		offsetX = 200 - m_x + m_shakeX;
		offsetY = 150 + m_y + m_shakeY;
		if(layer == LAYER_BACKGROUND){
			offsetX = offsetX*0.5;
			offsetY = offsetY*0.5;
		}
	}
	sprite->setPosition((x + offsetX)*scaling, (y + offsetY)*scaling);
	m_window.draw(*sprite);
}

void
Camera::setShake(float shake)
{
	m_shake = shake;
}
