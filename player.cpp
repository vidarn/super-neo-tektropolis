#include <iostream>
#include "player.hpp"
#include "common.hpp"

Player::Player(int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world, spriteFactory, rng)
{
	m_walkingLeft = m_walkingRight = false;
	m_jumpPressed = m_beginJump = false;
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
	m_sprite = m_runningSprite;
}

Player::~Player()
{
	m_sprite = 0; // Make sure Actor doesn't delete it
	delete m_idleSprite;
	delete m_runningSprite;
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
	}
}

void
Player::update(float dt)
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    vel.x = 0;
	if(m_walkingLeft){
		vel.x -= 7;
	}
	if(m_walkingRight){
		vel.x += 7;
	}
	if(vel.y < 0.0f && ! m_jumpPressed){
		vel.y *= 0.3f;
	}
    m_body->SetLinearVelocity(vel);
	m_onGround = feetOnGround();
	if(m_beginJump && m_onGround){
        m_body->ApplyLinearImpulse(b2Vec2(0.0f,-2.8f), m_body->GetPosition());
	}
	if(m_walkingLeft || m_walkingRight){
		m_sprite = m_runningSprite;
	}
	else{
		m_sprite = m_idleSprite;
	}
	m_jumpPressed = m_beginJump = false;
	m_walkingLeft = m_walkingRight = false;
	m_sprite->setFlipped(m_flipped);
	m_sprite->update(dt);
}
