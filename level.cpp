#include <boost/foreach.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp>
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"
#include "decoration.hpp"
#include "enemy.hpp"
#include "flying_enemy.hpp"
#include "orb.hpp"

Level::Level(boost::random::mt19937 *rng, SpriteFactory *spriteFactory, sf::RenderWindow &window):
	m_rng(rng), m_spriteFactory(spriteFactory), m_valid(true), m_score(0)
{
	b2Vec2 gravity(0.0f, 35.0f);
	m_world = new b2World(gravity);
    m_player = 0;
    for(int x=-1;x<2;x++){
        for(int y=-1;y<2;y++){
            std::string chunkType = "easy";
            if(x==0 && y==0){
                chunkType = "start";
            }
            Chunk *chunk = new Chunk(x,y,this,m_rng,chunkType);
            chunk->generate();
            m_chunks.push_back(chunk);
        }
    }
    m_valid = m_player != 0;
	m_camera = new Camera(m_player, window, m_rng);
	m_player->setCamera(m_camera);
	m_contactListener = new ActorContactListener();
	m_world->SetContactListener(m_contactListener);

	std::vector<std::string> frames;
	frames.push_back("number/00.png");
	frames.push_back("number/01.png");
	frames.push_back("number/02.png");
	frames.push_back("number/03.png");
	frames.push_back("number/04.png");
	frames.push_back("number/05.png");
	frames.push_back("number/06.png");
	frames.push_back("number/07.png");
	frames.push_back("number/08.png");
	frames.push_back("number/09.png");
    for(int i=0;i<5;i++){
        m_numbers[i] = m_spriteFactory->getSprite(frames);
    }
}

Level::~Level()
{
    BOOST_FOREACH(Chunk *chunk, m_chunks){
        delete chunk;
    }
    BOOST_FOREACH(Actor *actor, m_actors){
        delete actor;
    }
    for(int i=0;i<5;i++){
        delete m_numbers[i];
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
    for(int i=0;i<5;i++){
        m_numbers[i]->draw(m_camera, 10+8*i, 10, true);
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


    BOOST_FOREACH(Chunk *chunk, m_chunks){
        chunk->m_useless = true;
    }
    int x = m_player->getX()/m_chunks[0]->m_w;
    int y = m_player->getY()/m_chunks[0]->m_h;
    std::vector<Chunk *>newChunks;
    for(int yy=-2;yy<=1;yy++){
        for(int xx=-2;xx<=1;xx++){
            bool exists = false;
            BOOST_FOREACH(Chunk *chunk, m_chunks){
                if(chunk->m_iX == x+xx && chunk->m_iY == y+yy){
                    exists = true;
                    chunk->m_useless = false;
                }
            }
            if(!exists){
                Chunk *newChunk = new Chunk(x+xx,y+yy,this,m_rng,"standard");
                newChunks.push_back(newChunk);
            }
        }
    }

    BOOST_FOREACH(Actor *actor, m_actors){
        actor->m_useless = true;
    }
    for(int i=m_chunks.size()-1;i>=0;i--){
        Chunk *chunk = m_chunks[i];
        if(chunk->m_useless){
            m_chunks.erase(m_chunks.begin()+i);
            delete chunk;
        }
        else{
            BOOST_FOREACH(Actor *actor, m_actors){
                if(chunk->actorInside(actor)){
                    actor->m_useless = false;
                }
            }
        }
    }
    BOOST_FOREACH(Actor *actor, m_actors){
        if(actor->m_useless){
            actor->m_dead = true;
        }
    }

    BOOST_FOREACH(Chunk *chunk, newChunks){
        chunk->generate();
        m_chunks.push_back(chunk);
    }


	cleanUpActors();
    
    int tmp = 1;
    for(int i=4;i>=0;i--){
        int val = (m_score/tmp)%10;
        m_numbers[i]->setFrame(val);
        tmp *= 10;
    }
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
Level::addScore(int amount)
{
    m_score += amount;
    m_score = std::min(m_score,99999);
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
                addActor(new Decoration(m_player->getX(),m_player->getY()-70,17,37,*m_world,m_spriteFactory, "restart", m_rng, this));
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
