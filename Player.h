#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <Colly/GridWorld.h>
#include <Tily/Map.h>

namespace gm
{
	class Player
	{
	public:
		Player(float x, float y);

		void SetMap(ty::Map& map);

		void Update(float dt, cl::GridWorld& world);

		void Draw(sf::RenderTarget& tgt);

		sf::Vector2f GetInterpolationPos();

		inline sf::Vector2f GetPosition() { return m_spr.getPosition(); }

	private:
		ty::Map* m_currentMap;	// the map we are currently playing on
		sf::Vector2f m_vel;		// velocity
		sf::Vector2f m_prevPos;	// previous position (used for interpolation)
		sf::Vector2f m_spawn;	// spawn position
		bool m_onPlatform;		// are we standing or falling?
		bool m_died;			// did we just die?
		float m_elTime;			// used for smooth physics on all FPS
		
		std::function<void(int, int, int, bool, cl::GridWorld*)> m_onCollision; // handles the collision (for example, when user hits the coin)

		sf::Texture m_tex;	// player texture
		sf::Sprite m_spr;	// player sprite
	};
}

#endif