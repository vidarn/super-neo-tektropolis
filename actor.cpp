#include <iostream>
#include "actor.hpp"
#include "common.hpp"
#include "level.hpp"

Actor::Actor(int x, int y, int w, int h, int type, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng, Level *level):
	m_w(w), m_h(h), m_world(&world), m_level(level), m_spriteFactory(spriteFactory), m_rng(rng), m_dead(false), m_deadly(false)
{
	b2BodyDef bodyDef;
	switch(type){
		case ACTOR_STATIC:
		case ACTOR_GHOST:
			bodyDef.type = b2_staticBody;
			break;
		case ACTOR_DYNAMIC:
		case ACTOR_BULLET:
			bodyDef.type = b2_dynamicBody;
			break;
		case ACTOR_KINEMATIC:
			bodyDef.type = b2_kinematicBody;
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
	if(type == ACTOR_GHOST || type == ACTOR_BULLET){
		fixtureDef.isSensor = true;
		fixtureDef.filter.categoryBits = 0x002;
	}
	m_body->CreateFixture(&fixtureDef);
	b2Fixture *f = m_body->GetFixtureList();
	f->SetUserData((void*)this);
	m_sprite = 0;
}

Actor::~Actor()
{
	if(m_sprite !=0){
		delete m_sprite;
	}
	m_world->DestroyBody(m_body);
}

void
Actor::draw(Camera *cam)
{
	drawActor(cam,this);
}

void
Actor::drawActor(Camera *cam, Actor *act)
{
	int x = act->getX();
	int y = act->getY();
    sf::RectangleShape bodyRect;
	if(act->m_sprite != 0){
		act->m_sprite->draw(cam, x, y-act->m_h);
	}
}

void
Actor::drawActor(Camera *cam, Actor *act, int x, int y)
{
    sf::RectangleShape bodyRect;
	if(act->m_sprite != 0){
		act->m_sprite->draw(cam, x, y-act->m_h);
	}
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
	feetOnGround(0);
}

bool
Actor::feetOnGround(int offset)
{
	bool onGround = false;
	b2Vec2 feetPos = m_body->GetPosition();
	feetPos.y += screenToWorld(m_h)*0.5;
	feetPos.x -= screenToWorld(m_w+2*offset)*0.5;
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

void
Actor::setX(float x){
	b2Vec2 position = m_body->GetPosition();
	position.x =  x;
	m_body->SetTransform(position, m_body->GetAngle());
}

void
Actor::setY(float y){
	b2Vec2 position = m_body->GetPosition();
	position.y =  y;
	m_body->SetTransform(position, m_body->GetAngle());
}

void
Actor::getBeamed(){
}

void
Actor::collide(Actor *)
{
}

b2Fixture *
Actor::getFixture()
{
	return m_body->GetFixtureList();
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

ActorContactListener::ActorContactListener()
{
}

void
ActorContactListener::BeginContact(b2Contact *contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	Actor *actorA = static_cast<Actor *>(fixtureA->GetUserData());
	Actor *actorB = static_cast<Actor *>(fixtureB->GetUserData());
	actorA->collide(actorB);
	actorB->collide(actorA);
}

void
ActorContactListener::EndContact(b2Contact *contact)
{
}

