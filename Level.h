#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Colly/GridWorld.h>
#include <Tily/Map.h>
#include "Player.h"

namespace gm
{
	class Level
	{
	public:
		Level(sf::RenderWindow& tgt);

		void CreatePlayer(Player& pl);

		void Update(Player& pl);

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