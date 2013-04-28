#ifndef PLAYER_52X2JIYU
#define PLAYER_52X2JIYU
#include "actor.hpp"
#include "beam.hpp"

class Camera;

class BeamCallback : public b2RayCastCallback
{
	public:
		BeamCallback();
		float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction);
		float m_minFraction;
		Actor *m_nearestActor;
};

class Player : public Actor {
	public:
		Player (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactoryj,
				boost::random::mt19937 *rng, Level *level);
		virtual ~Player ();
		void buttonPressed(const std::string &command);
		void update(float dt);
		void draw(Camera *cam);
		void setCamera(Camera *);
		void collide(Actor *);
	private:
		bool m_walkingRight;
		bool m_walkingLeft;
		bool m_beginJump;
		bool m_jumpPressed;
		bool m_shooting;
		bool m_wasShooting;
		bool m_onGround;
		bool m_flipped;
		Sprite *m_idleSprite;
		Sprite *m_runningSprite;
		Sprite *m_shootingSprite;
		Sprite *m_dyingSprite;
		Camera *m_camera;
		int     m_beamW;
};

#endif /* end of include guard: PLAYER_52X2JIYU */
