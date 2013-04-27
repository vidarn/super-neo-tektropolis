#ifndef SPRITE_CB66XGPY
#define SPRITE_CB66XGPY
#include <string>
#include <SFML/Graphics.hpp>

class Camera;

class Sprite {
	public:
		Sprite (std::vector<sf::Texture *> textures);
		virtual ~Sprite ();
		void draw(Camera *cam, float x, float y);
		void setBackground();
		float getW();
		float getH();
		void setFlipped(bool state);
		void update(float dt);
	private:
		std::vector<sf::Sprite  *> m_sprites;
		int m_scaling;
		int m_layer;
		int m_frame;
		bool m_flipped;
		float m_frameTime;
		float m_t;
};


#endif /* end of include guard: SPRITE_CB66XGPY */
