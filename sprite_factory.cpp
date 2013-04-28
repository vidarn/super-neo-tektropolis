#include <boost/foreach.hpp>
#include <iostream>
#include <stdexcept>
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
		sf::Texture *tex;
        try{
            tex = m_textures.at(name);
        }
        catch(std::out_of_range &oor){
            std::cout << "loading " << name << std::endl;
            tex = new sf::Texture;
            tex->loadFromFile("data/sprites/" + name);
            m_textures[name] = tex;
        }
        textures.push_back(tex);
    }
	return new Sprite(textures);
}
