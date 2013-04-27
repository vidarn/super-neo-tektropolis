#include <boost/foreach.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"

Level::Level(boost::random::mt19937 *rng):
	m_rng(rng)
{
	b2Vec2 gravity(0.0f, 20.0f);
	m_world = new b2World(gravity);
	generate();
}

Level::~Level()
{
    BOOST_FOREACH(Actor *actor, m_actors){
        delete actor;
    }
	delete m_world;
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		m_player->buttonPressed("right");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		m_player->buttonPressed("left");
    }
    BOOST_FOREACH(Actor *actor, m_actors){
		actor->update(dt);
	}
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
	m_world->Step(dt, velocityIterations, positionIterations);
}

void
Level::generate()
{
	for(int a=0;a<30;a++){
		int x = boost::random::uniform_int_distribution<>(1,700)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(40,500)(*m_rng);
		addActor(new Obstacle(x,y,60,30,*m_world));
		if( a == 0){
			y -= 42;
			m_player = new Player(x,y,20,40,*m_world);
			addActor(m_player);
		}
	}
}
