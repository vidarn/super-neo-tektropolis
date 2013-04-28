#include <boost/foreach.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp>
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"
#include "decoration.hpp"
#include "enemy.hpp"
#include "flying_enemy.hpp"

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
	for(int a=0;a<100;a++){
		int x = boost::random::uniform_int_distribution<>(1,450)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(40,2050)(*m_rng);
        int w = 1;
        int h = 1;
		double obstacleProbs[] = {
			0.3, 0.7
		};
		int obstacleType = boost::random::discrete_distribution<>(obstacleProbs)(*m_rng);
        Actor *obstacle;
		switch(obstacleType){
			case 0:
                w = 85;
                h = 30;
				obstacle = new Obstacle(x,y,w,h,*m_world,m_spriteFactory,m_rng, this, "medium");
				break;
			case 1:
                w = 160;
                h = 30;
				obstacle = new Obstacle(x,y,w,h,*m_world,m_spriteFactory,m_rng, this, "large");
				break;
		}
        ObstacleIntersectionCallback callback(obstacle);
        b2Vec2 tmp;
        b2AABB bb = obstacle->getFixture()->GetAABB(0);
        bb.lowerBound.y -= screenToWorld(h);
        m_world->QueryAABB(&callback, bb);
        if(callback.m_empty){
            addActor(obstacle);
            if( a == 0){
                y -= 42;
                m_player = new Player(x,y,15,39,*m_world,m_spriteFactory,m_rng, this);
                addActor(m_player);
            }
            else{
                y -= 40;
				double enemyProbs[] = {
					0.0, 0.6, 0.4
				};
				int enemyType = boost::random::discrete_distribution<>(enemyProbs)(*m_rng);
				Actor *enemy = 0;
				switch(enemyType){
					case 1:
						x += boost::random::uniform_int_distribution<>(-w*0.5,w*0.5)(*m_rng);
						enemy = new Enemy(x,y,17,37,*m_world,m_spriteFactory,m_rng, this);
						break;
					case 2:
						enemy = new FlyingEnemy(x,y-40,17,37,*m_world,m_spriteFactory,m_rng, this);
						break;
				}
                if(enemy){
					addActor(enemy);
				}
            }
        }
        else{
            delete obstacle;
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

Actor *
Level::getPlayer()
{
	return m_player;
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

ObstacleIntersectionCallback::ObstacleIntersectionCallback(Actor *ignore):
    m_empty(true), m_ignore(ignore)
{
}

bool
ObstacleIntersectionCallback::ReportFixture(b2Fixture *fixture)
{
    if(static_cast<Actor *>(fixture->GetUserData()) != m_ignore){
        m_empty = false;
        return false;
    }
    return true;
}
