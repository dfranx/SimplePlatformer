#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "libs/Colly.h"
#include "libs/Tily.h"
#include "Player.h"

namespace gm
{
	class Level
	{
	public:
		// set up tily and colly
		Level(sf::RenderWindow& tgt);

		// tells the player that he is currently on this map
		void CreatePlayer(Player& pl);

		// do the physics
		void Update(Player& pl);

		// render the world and the player
		void Draw(Player& pl);

	private:
		void m_load(std::string str); // load tilemap from file

		cl::GridWorld m_world;
		ty::Map m_tmap;

		sf::RenderWindow* m_wnd;
		sf::Texture m_fg, m_dec;

		sf::Texture m_bgTex;
		sf::Sprite m_bg;

		sf::Clock m_clock;
		float m_elTime;
	};
}

#endif