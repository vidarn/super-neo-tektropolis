#include <boost/foreach.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"
#include "decoration.hpp"

Level::Level(boost::random::mt19937 *rng, SpriteFactory *spriteFactory, sf::RenderWindow &window):
	m_rng(rng), m_spriteFactory(spriteFactory)
{
	b2Vec2 gravity(0.0f, 55.0f);
	m_world = new b2World(gravity);
	generate();
	m_camera = new Camera(m_player, window);
}

Level::~Level()
{
    BOOST_FOREACH(Actor *actor, m_actors){
        delete actor;
    }
	delete m_world;
	delete m_camera;
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
		actor->draw(m_camera);
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
		m_player->buttonPressed("keep jump");
    }
    BOOST_FOREACH(Actor *actor, m_actors){
		actor->update(dt);
	}
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
	m_world->Step(dt, velocityIterations, positionIterations);
	m_camera->update(dt);
}

void
Level::generate()
{
	for(int a=0;a<5;a++){
		int x = boost::random::uniform_int_distribution<>(1,350)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(40,250)(*m_rng);
		addActor(new Decoration(x,y,85,30,*m_world,m_spriteFactory,"cloud",m_rng));
	}
	for(int a=0;a<5;a++){
		int x = boost::random::uniform_int_distribution<>(1,350)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(40,250)(*m_rng);
		addActor(new Obstacle(x,y,85,30,*m_world,m_spriteFactory,m_rng));
		if( a == 0){
			y -= 42;
			m_player = new Player(x,y,15,39,*m_world,m_spriteFactory,m_rng);
			addActor(m_player);
		}
	}
}

void
Level::keyPressed(int key)
{
	switch(key){
		case sf::Keyboard::J:
			m_player->buttonPressed("start jump");
			break;
	}
}
