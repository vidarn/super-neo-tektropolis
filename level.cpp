#include <boost/foreach.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"
#include "decoration.hpp"
#include "enemy.hpp"

Level::Level(boost::random::mt19937 *rng, SpriteFactory *spriteFactory, sf::RenderWindow &window):
	m_rng(rng), m_spriteFactory(spriteFactory), m_valid(true)
{
	b2Vec2 gravity(0.0f, 35.0f);
	m_world = new b2World(gravity);
	generate();
	m_camera = new Camera(m_player, window, m_rng);
	m_player->setCamera(m_camera);
	m_contactListener = new ActorContactListener();
	m_world->SetContactListener(m_contactListener);
}

Level::~Level()
{
    BOOST_FOREACH(Actor *actor, m_actors){
        delete actor;
    }
	delete m_world;
	delete m_camera;
	delete m_contactListener;
}

void 
Level::addActor(Actor *actor)
{
    m_newActors.push_back(actor);
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
	if(m_valid){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			m_player->buttonPressed("right");
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			m_player->buttonPressed("left");
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
			m_player->buttonPressed("keep jump");
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
			m_player->buttonPressed("shoot");
		}
		BOOST_FOREACH(Actor *actor, m_actors){
			actor->update(dt);
		}
	}
	else{
		m_player->update(dt);
	}
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
	if(m_valid){
		m_world->Step(dt, velocityIterations, positionIterations);
	}
	m_camera->update(dt);
	cleanUpActors();
}

void
Level::generate()
{
	for(int a=0;a<35;a++){
		int x = boost::random::uniform_int_distribution<>(1,450)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(40,2050)(*m_rng);
		addActor(new Obstacle(x,y,85,30,*m_world,m_spriteFactory,m_rng, this));
		if( a == 0){
			y -= 42;
			m_player = new Player(x,y,15,39,*m_world,m_spriteFactory,m_rng, this);
			addActor(m_player);
		}
		else{
			y -= 40;
			addActor(new Enemy(x,y,17,37,*m_world,m_spriteFactory,m_rng, this));
		}
	}
	for(int a=0;a<15;a++){
		int x = boost::random::uniform_int_distribution<>(1,950)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(40,950)(*m_rng);
		addActor(new Decoration(x,y,85,30,*m_world,m_spriteFactory,"cloud",m_rng, this));
	}
	cleanUpActors();
}

void
Level::keyPressed(int key)
{
	if(m_valid){
		switch(key){
			case sf::Keyboard::J:
				m_player->buttonPressed("start jump");
				break;
		}
	}
}

void
Level::cleanUpActors()
{
	for(int i=m_actors.size()-1;i>=0;i--){
		Actor *actor = m_actors[i];
		if(actor->m_dead){
			if(actor == m_player){
				m_valid = false;
			}
			else{
				m_actors.erase(m_actors.begin()+i);
				delete actor;
			}
		}
	}
	for(int i=m_newActors.size()-1;i>=0;i--){
		m_actors.push_back(m_newActors[i]);
	}
	m_newActors.clear();
}
