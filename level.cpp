#include <boost/foreach.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"

Level::Level()
{
	generate();
}

Level::~Level()
{
    BOOST_FOREACH(Actor *actor, m_actors){
        delete actor;
    }
}

void 
Level::addActor(Actor *actor)
{
    m_actors.push_back(actor);
}

void
Level::draw(sf::RenderWindow &window)
{
    BOOST_FOREACH(Actor *actor, m_actors){
		actor->draw(window);
	}
}

void
Level::update(float dt)
{
    BOOST_FOREACH(Actor *actor, m_actors){
		actor->update(dt);
	}
}

void
Level::generate()
{
	int x = boost::random::uniform_int_distribution<>(1,700)(RNG);
	int y = boost::random::uniform_int_distribution<>(1,500)(RNG);
	addActor(new Obstacle(x,y,40,40));
}
