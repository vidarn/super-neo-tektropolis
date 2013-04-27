#ifndef SPRITE_FACTORY_OI750SE4
#define SPRITE_FACTORY_OI750SE4
#include <string>
#include "sprite.hpp"

class SpriteFactory {
	public:
		SpriteFactory ();
		virtual ~SpriteFactory ();
		Sprite *getSprite(const std::string &name);
		Sprite *getSprite(std::vector<std::string> names);
	private:
		std::map<std::string, sf::Texture *> m_textures;
};

#endif /* end of include guard: SPRITE_FACTORY_OI750SE4 */
