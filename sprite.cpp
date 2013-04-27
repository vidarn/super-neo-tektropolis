#include <boost/foreach.hpp>
#include "sprite.hpp"
#include "camera.hpp"

Sprite::Sprite(std::vector<sf::Texture *> textures)
{
	m_scaling = 2;
    BOOST_FOREACH(sf::Texture *tex, textures){
		sf::Sprite *sprite = new sf::Sprite(*tex);
		sf::FloatRect r = sprite->getLocalBounds();
		sprite->setOrigin(r.width*0.5f, r.height);
		sprite->scale(m_scaling, m_scaling);
		m_sprites.push_back(sprite);
	}
	std::cout << m_sprites.size() << std::endl;
	m_layer = LAYER_FOREGROUND;
	m_flipped = false;
	m_frame = 0;
	m_frameTime = 0.08;
	m_t = 0.0f;
}

Sprite::~Sprite()
{
    BOOST_FOREACH(sf::Sprite *sprite, m_sprites){
		delete sprite;
	}
}

void
Sprite::draw(Camera *cam, float x, float y)
{
	int ix = x + 0.5f;
	int iy = y + 0.5f;
	cam->draw(m_sprites[m_frame], x, y, m_layer, m_scaling);
}

void
Sprite::setBackground(){
	m_layer = LAYER_BACKGROUND;
}

void
Sprite::setFlipped(bool state)
{
	if(state != m_flipped){
		BOOST_FOREACH(sf::Sprite *sprite, m_sprites){
			sprite->scale(-1.0f, 1.0f);
		}
		m_flipped = state;
	}
}

void
Sprite::update(float dt)
{
	m_t += dt;
	if(m_t > m_frameTime){
		m_frame += 1;
		m_frame %= m_sprites.size();
		if(m_sprites.size() != 1)
			std::cout << m_sprites.size() << std::endl;
		m_t = 0.0f;
	}
}
