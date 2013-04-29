#ifndef SPRITE_CB66XGPY
#define SPRITE_CB66XGPY
#include <string>
#include <SFML/Graphics.hpp>

class Camera;

class Sprite {
	public:
		Sprite (std::vector<sf::Texture *> textures);
		virtual ~Sprite ();
		void draw(Camera *cam, int x, int y, bool absolute = false);
		void setBackground();
		void setFlipped(bool state);
		void update(float dt);
		void restart();
		void setLoop(bool loop);
		void setScale(float w, float h);
		int  getFrame(){return m_frame;};
		void setFrame(int f){m_frame = f;};
	private:
		std::vector<sf::Sprite  *> m_sprites;
		int m_scaling;
		int m_layer;
		int m_frame;
		bool m_flipped;
		bool m_loop;
		float m_frameTime;
		float m_t;
};


#endif /* end of include guard: SPRITE_CB66XGPY */
