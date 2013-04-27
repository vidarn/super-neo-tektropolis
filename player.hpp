#ifndef PLAYER_52X2JIYU
#define PLAYER_52X2JIYU
#include "actor.hpp"

class Player : public Actor {
	public:
		Player (int x, int y, int w, int h, b2World &world, SpriteFactory *spriteFactory, boost::random::mt19937 *rng);
		virtual ~Player ();
		void buttonPressed(const std::string &command);
		void update(float dt);
	private:
		bool m_walkingRight;
		bool m_walkingLeft;
		bool m_beginJump;
		bool m_jumpPressed;
		bool m_onGround;
		bool m_flipped;
		Sprite *m_idleSprite;
		Sprite *m_runningSprite;
};

#endif /* end of include guard: PLAYER_52X2JIYU */
