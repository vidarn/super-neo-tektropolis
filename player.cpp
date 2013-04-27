#include "player.hpp"

Player::Player(int x, int y, int w, int h, b2World &world):
	Actor(x,y,w,h,ACTOR_DYNAMIC,world)
{
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
	if(command == "jump"){
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
    m_body->SetLinearVelocity(vel);
	m_walkingLeft = m_walkingRight = false;
}
