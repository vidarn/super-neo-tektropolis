#include <iostream>
#include "actor.hpp"
#include "common.hpp"

Actor::Actor(int x, int y, int w, int h, int type, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng):
	m_w(w), m_h(h), m_world(&world), m_spriteFactory(spriteFactory), m_rng(rng)
{
	b2BodyDef bodyDef;
	switch(type){
		case ACTOR_STATIC:
			bodyDef.type = b2_staticBody;
			break;
		case ACTOR_DYNAMIC:
			bodyDef.type = b2_dynamicBody;
			break;
		case ACTOR_GHOST:
			bodyDef.type = b2_staticBody;
			break;
	}
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(screenToWorld(x), screenToWorld(y));
	m_body = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(screenToWorld(m_w)*0.5,screenToWorld(m_h)*0.5);
	b2FixtureDef fixtureDef;
	fixtureDef.shape       = &shape;
	fixtureDef.density     = 1.0f;
	fixtureDef.friction    = 0.0f;
	fixtureDef.restitution = 0.0f;
	if(type == ACTOR_GHOST){
		fixtureDef.isSensor = true;
		fixtureDef.filter.categoryBits = 0x002;
	}
	m_body->CreateFixture(&fixtureDef);
	m_sprite = 0;
}

Actor::~Actor()
{
	if(m_sprite !=0){
		delete m_sprite;
	}
}

void
Actor::draw(Camera *cam)
{
	b2Vec2 position = m_body->GetPosition();
	int x = worldToScreen(position.x);
	int y = worldToScreen(position.y);
    sf::RectangleShape bodyRect;
    bodyRect.setPosition(x-m_w*0.5,y-m_h);
    bodyRect.setSize(sf::Vector2f(m_w,m_h));
	bodyRect.setFillColor(sf::Color(255,255,0,128));
	if(m_sprite != 0){
		m_sprite->draw(cam, x, y-m_h);
	}
	//window.draw(bodyRect);
}

void
Actor::update(float dt)
{
	if(m_sprite != 0){
		m_sprite->update(dt);
	}
}

bool
Actor::feetOnGround()
{
	bool onGround = false;
	b2Vec2 feetPos = m_body->GetPosition();
	feetPos.y += screenToWorld(m_h)*0.5;
	feetPos.x -= screenToWorld(m_w)*0.5;
	for(int i=0;i<2;i++){
		b2Vec2 point1 = feetPos;
		b2Vec2 point2 = point1;
		point2.y += screenToWorld(10);
		FloorFeetCallback callback;
		m_world->RayCast(&callback, point1, point2);
		onGround |= callback.m_hit;
		feetPos.x += screenToWorld(m_w);
	}
	return onGround;
}

int
Actor::getX(){
	b2Vec2 position = m_body->GetPosition();
	return worldToScreen(position.x);
}

int
Actor::getY(){
	b2Vec2 position = m_body->GetPosition();
	return worldToScreen(position.y);
}

FloorFeetCallback::FloorFeetCallback():
	m_hit(false)
{
}

float32
FloorFeetCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
{
	if(fixture->GetFilterData().categoryBits != 0x002){
		m_hit = true;
	}
	return 1.0f;
}

