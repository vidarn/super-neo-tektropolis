#include <boost/foreach.hpp>
#include <iostream>
#include "sprite_factory.hpp"

SpriteFactory::SpriteFactory()
{
}

SpriteFactory::~SpriteFactory()
{
}

Sprite *
SpriteFactory::getSprite(const std::string &name)
{
	std::vector<std::string> names;
	names.push_back(name);
	return getSprite(names);
}

Sprite *
SpriteFactory::getSprite(std::vector<std::string> names)
{
	std::vector<sf::Texture *> textures;
    BOOST_FOREACH(std::string name, names){
		std::cout << name << std::endl;
		sf::Texture *tex = new sf::Texture;
		textures.push_back(tex);
		tex->loadFromFile("data/sprites/" + name);
		m_textures[name] = tex;
	}
	return new Sprite(textures);
}
