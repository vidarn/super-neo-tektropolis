#include <iostream>
#include "player.hpp"
#include "common.hpp"
#include "camera.hpp"

Player::Player(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world, spriteFactory, rng, level)
{
	m_walkingLeft = m_walkingRight = false;
	m_jumpPressed = m_beginJump = false;
	m_shooting = false;
	m_onGround = m_flipped = false;
	m_idleSprite = m_spriteFactory->getSprite("player/standing.png");
	std::vector<std::string> runningFrames;
	runningFrames.push_back("player/running01.png");
	runningFrames.push_back("player/running02.png");
	runningFrames.push_back("player/running03.png");
	runningFrames.push_back("player/running04.png");
	runningFrames.push_back("player/running05.png");
	runningFrames.push_back("player/running06.png");
	runningFrames.push_back("player/running07.png");
	runningFrames.push_back("player/running08.png");
	runningFrames.push_back("player/running09.png");
	runningFrames.push_back("player/running10.png");
	m_runningSprite = m_spriteFactory->getSprite(runningFrames);
	std::vector<std::string> shootingFrames;
	shootingFrames.push_back("player/shooting01.png");
	shootingFrames.push_back("player/shooting02.png");
	shootingFrames.push_back("player/shooting03.png");
	shootingFrames.push_back("player/shooting04.png");
	shootingFrames.push_back("player/shooting05.png");
	shootingFrames.push_back("player/shooting06.png");
	m_shootingSprite = m_spriteFactory->getSprite(shootingFrames);
	m_shootingSprite->setLoop(false);
	std::vector<std::string> dyingFrames;
	dyingFrames.push_back("player/dying01.png");
	dyingFrames.push_back("player/dying02.png");
	dyingFrames.push_back("player/dying03.png");
	dyingFrames.push_back("player/dying04.png");
	dyingFrames.push_back("player/dying05.png");
	dyingFrames.push_back("player/dying06.png");
	dyingFrames.push_back("player/dying07.png");
	m_dyingSprite = m_spriteFactory->getSprite(dyingFrames);
	m_dyingSprite->setLoop(false);
	m_sprite = m_idleSprite;
	m_camera = 0;
}

Player::~Player()
{
	m_sprite = 0; // Make sure Actor doesn't try to delete it
	delete m_idleSprite;
	delete m_runningSprite;
	delete m_shootingSprite;
	delete m_dyingSprite;
}

void
Player::buttonPressed(const std::string &command)
{
    bool walking = false;
	if(command == "left"){
		m_walkingLeft = true;
		m_flipped = true;
	}
	if(command == "right"){
		m_walkingRight = true;
		m_flipped = false;
	}
	if(command == "start jump"){
		m_beginJump = true;
	}
	if(command == "keep jump"){
		m_jumpPressed = true;
	}
	if(command == "shoot"){
		if(!m_wasShooting){
			m_shootingSprite->restart();
		}
		m_shooting = true;
	}
}

void
Player::update(float dt)
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    vel.x = 0;
	if(m_walkingLeft){
		vel.x -= 5;
	}
	if(m_walkingRight){
		vel.x += 5;
	}
	if(vel.y < 0.0f && ! m_jumpPressed){
		vel.y *= 0.3f;
	}
    m_body->SetLinearVelocity(vel);
	m_onGround = feetOnGround();
	if(m_beginJump && m_onGround){
        m_body->ApplyLinearImpulse(b2Vec2(0.0f,-2.8f), m_body->GetPosition());
	}
	if(m_camera)
		m_camera->setShake(0.0f);
	m_sprite = m_idleSprite;
	m_shooting = m_shooting && m_onGround;
	m_wasShooting = m_shooting;
	if(m_walkingLeft || m_walkingRight){
		m_sprite = m_runningSprite;
		m_wasShooting = false;
	}
	else{
		if(m_shooting){
			m_sprite = m_shootingSprite;
			m_beamW = 600;

			b2Vec2 point1 = m_body->GetPosition();
			point1.y -= screenToWorld(5);
			b2Vec2 point2 = point1;
			if(m_flipped)
				point2.x -= screenToWorld(m_beamW);
			else
				point2.x += screenToWorld(m_beamW);
			BeamCallback callback;
			m_world->RayCast(&callback, point1, point2);
			m_beamW *= callback.m_minFraction;
			if(m_camera && m_sprite->getFrame() == 5){
				Actor *nearest = callback.m_nearestActor;
				if(nearest){
					nearest->getBeamed();
				}
				m_camera->setShake(3.0f);
			}
		}
	}
	if(m_dead){
		m_sprite = m_dyingSprite;
	}
	m_jumpPressed = m_beginJump = false;
	m_walkingLeft = m_walkingRight = false;
	m_shooting = false;
	m_sprite->setFlipped(m_flipped);
	m_sprite->update(dt);
}

void
Player::draw(Camera *cam)
{
	drawActor(cam,this);
	if(m_wasShooting){
		b2Vec2 position = m_body->GetPosition();
		Beam *beam = 0;
		int offsetX = 13 + m_beamW/2;
		if(m_flipped)
			offsetX = -offsetX;
		int offsetY;
		if(m_sprite->getFrame() == 4){
			beam = new Beam(0, 0, m_beamW, 1, *m_world, m_spriteFactory,
					m_rng, false, m_level);
			offsetY = -61;
		}
		if(m_sprite->getFrame() == 5){
			beam = new Beam(0, 0, m_beamW, 1, *m_world, m_spriteFactory,
					m_rng, true, m_level);
			offsetY = -62;
		}
		if(beam){
			drawActor(cam,beam, getX() + offsetX, getY() + offsetY);
			delete beam;
		}
	}
}

void
Player::setCamera(Camera *camera)
{
	m_camera = camera;
}

void
Player::collide(Actor * actor)
{
	if(actor->m_deadly){
		m_dead = true;
	}
}

BeamCallback::BeamCallback():
	m_minFraction(1.0f), m_nearestActor(0)
{
}

float32
BeamCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
{
	if(fraction < m_minFraction && fixture->GetFilterData().categoryBits != 0x002){
		m_minFraction = fraction;
		m_nearestActor = static_cast<Actor *>(fixture->GetUserData());
	}
	return 1.0f;
}

