#include <iostream>
#include "player.hpp"
#include "common.hpp"

Player::Player(int x, int y, int w, int h, b2World &world):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world)
{
	m_walkingLeft = m_walkingRight = false;
	m_jumpPressed = m_beginJump = false;
	m_onGround    = false;
}

Player::~Player()
{
}

void
Player::buttonPressed(const std::string &command)
{
    bool walking = false;
	if(command == "left"){
		m_walkingLeft = true;
	}
	if(command == "right"){
		m_walkingRight = true;
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
		vel.x -= 10;
	}
	if(m_walkingRight){
		vel.x += 10;
	}
	if(vel.y < 0.0f && ! m_jumpPressed){
		vel.y *= 0.2f;
	}
    m_body->SetLinearVelocity(vel);
	m_onGround = feetOnGround();
	if(m_beginJump && m_onGround){
        m_body->ApplyLinearImpulse(b2Vec2(0.0f,-5.0f), m_body->GetPosition());
	}
	m_jumpPressed = m_beginJump = false;
	m_walkingLeft = m_walkingRight = false;
}
