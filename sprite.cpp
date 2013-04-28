#include <boost/foreach.hpp>
#include <algorithm>
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
	m_layer = LAYER_FOREGROUND;
	m_flipped = false;
	m_frame = 0;
	m_frameTime = 0.08;
	m_t = 0.0f;
	m_loop = true;
}

Sprite::~Sprite()
{
    BOOST_FOREACH(sf::Sprite *sprite, m_sprites){
		delete sprite;
	}
}

void
Sprite::draw(Camera *cam, int x, int y)
{
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
		if(m_loop){
			m_frame %= m_sprites.size();
		}
		else{
			if(m_frame >= m_sprites.size()-1)
				m_frame = m_sprites.size()-1;
		}
		m_t = 0.0f;
	}
}

void
Sprite::restart()
{
	m_frame = 0;
}

void
Sprite::setLoop(bool loop)
{
	m_loop = loop;
}

void
Sprite::setScale(float w, float h)
{
	BOOST_FOREACH(sf::Sprite *sprite, m_sprites){
		sprite->setScale(m_scaling*w,m_scaling*h);
	}
}
