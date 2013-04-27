#include "actor.hpp"
#include "common.hpp"

Actor::Actor(int x, int y, int w, int h, int type, b2World &world):
	m_x(x), m_y(y), m_w(w), m_h(h)
{
	b2BodyDef bodyDef;
	switch(type){
		case ACTOR_STATIC:
			bodyDef.type = b2_staticBody;
			break;
		case ACTOR_DYNAMIC:
			bodyDef.type = b2_dynamicBody;
			break;
	}
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(screenToWorld(m_x), screenToWorld(m_y));
	m_body = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(screenToWorld(m_w)*0.5,screenToWorld(m_h)*0.5);
	b2FixtureDef fixtureDef;
	fixtureDef.shape       = &shape;
	fixtureDef.density     = 1.0f;
	fixtureDef.friction    = 0.0f;
	fixtureDef.restitution = 0.0f;
	m_body->CreateFixture(&fixtureDef);
}

Actor::~Actor()
{
}

void
Actor::draw(sf::RenderWindow &window)
{
	b2Vec2 position = m_body->GetPosition();
	int x = worldToScreen(position.x);
	int y = worldToScreen(position.y);
    sf::RectangleShape bodyRect;
    bodyRect.setPosition(x-m_w/2,y-m_h);
    bodyRect.setSize(sf::Vector2f(m_w,m_h));
	window.draw(bodyRect);
}

void
Actor::update(float dt)
{
}

