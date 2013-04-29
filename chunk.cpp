#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp>
#include "chunk.hpp"
#include "level.hpp"
#include "common.hpp"
#include "obstacle.hpp"
#include "decoration.hpp"
#include "enemy.hpp"
#include "flying_enemy.hpp"
#include "orb.hpp"

Chunk::Chunk(int x, int y, Level *level, boost::random::mt19937 *rng, const std::string &type):
	 m_level(level), m_rng(rng), m_type(type)
{
	m_w = 600;
	m_h = 600;
	m_x = x*m_w;
	m_y = y*m_h;
	m_iX = x;
	m_iY = y;
}

Chunk::~Chunk()
{
}

void
Chunk::generate()
{
	bool first = true;
	for(int a=0;a<30;a++){
		int x = boost::random::uniform_int_distribution<>(m_x,m_x+m_w)(*m_rng);
		int y = boost::random::uniform_int_distribution<>(m_y,m_y+m_h)(*m_rng);
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
				obstacle = new Obstacle(x,y,w,h,*m_level->m_world,m_level->m_spriteFactory,m_rng, m_level, "medium");
				break;
			case 1:
                w = 160;
                h = 30;
				obstacle = new Obstacle(x,y,w,h,*m_level->m_world,m_level->m_spriteFactory,m_rng, m_level, "large");
				break;
		}
        ObstacleIntersectionCallback callback(obstacle);
        b2Vec2 tmp;
        b2AABB bb = obstacle->getFixture()->GetAABB(0);
        bb.lowerBound.y -= screenToWorld(2*h);
        m_level->m_world->QueryAABB(&callback, bb);
        if(callback.m_empty){
            m_level->addActor(obstacle);
            if( first && m_type == "start"){
                y -= 42;
                m_level->m_player = new Player(x,y,15,39,*m_level->m_world,m_level->m_spriteFactory,m_rng, m_level);
                m_level->addActor(m_level->m_player);
            }
            else{
                y -= 40;
				double enemyProbs[] = {
					0.6, 0.8, 0.3, 0.2
				};
				if(m_type == "easy"){
					enemyProbs[0] = 1.0;
					enemyProbs[2] = 0.0;
				}
				int enemyType = boost::random::discrete_distribution<>(enemyProbs)(*m_rng);
				Actor *enemy = 0;
				switch(enemyType){
					case 1:
						x += boost::random::uniform_int_distribution<>(-w*0.5,w*0.5)(*m_rng);
						enemy = new Enemy(x,y,17,37,*m_level->m_world,m_level->m_spriteFactory,m_rng, m_level);
						break;
					case 2:
						enemy = new FlyingEnemy(x,y-40,17,37,*m_level->m_world,m_level->m_spriteFactory,m_rng, m_level);
						break;
					case 3:
						enemy = new Orb(x,y,17,37,*m_level->m_world,m_level->m_spriteFactory,m_rng, m_level);
						break;
				}
                if(enemy){
					m_level->addActor(enemy);
				}
            }
			first = false;
        }
        else{
            delete obstacle;
        }
	}
	m_level->cleanUpActors();
}

bool
Chunk::actorInside(Actor *actor)
{
	int x = actor->getX();
	int y = actor->getY();
	return !(x<m_x || x > m_x+m_w) && !(y<m_y || y>m_y+m_h);
}

bool
Chunk::actorCloseEnough(Actor *actor, int *x, int *y)
{
	bool valid = true;
	int dx = m_iX - *x;
	int dy = m_iY - *y;
	if(dy < -1){
		*y += 1;
		valid = false;
	}
	if(dy >  1){
		*y -= 1;
		valid = false;
	}
	if(dx < -1){
		*x += 1;
		valid = false;
	}
	if(dx >  1){
		*x -= 1;
		valid = false;
	}
	return valid;
}

