#include "Player.h"
#include "Config.h"
#include "Utils.h"
#include "Tiles.h"
#include <SFML/Window/Keyboard.hpp>

namespace gm
{
	Player::Player(float x, float y)
	{
		m_vel = sf::Vector2f(0, 0);
		m_spawn = sf::Vector2f(x, y);
		m_onPlatform = false;
		m_elTime = 0;

		m_prevPos = sf::Vector2f(x, y);

		m_tex.loadFromFile("data/character.png");

		m_spr.setPosition(x, y);
		m_spr.setTexture(m_tex);

		// initialize filter that will handle the collision
		m_onCollision = [&](int id, int x, int y, bool hor, cl::GridWorld* col) {
			if (id == Tiles::BONUS) { // bonus block
				if (m_vel.y < 0 && !hor) { // must be hit from below
					m_currentMap->Set(x, y, 0, Tiles::BONUS_USED); // replace it on tilemap
					col->SetObject(x, y, Tiles::BONUS_USED); // and in our physics world so that it doesnt report this event anymore
				}
			}
			else if (id == Tiles::COIN) {
				m_currentMap->Set(x, y, 0, Tiles::EMPTY_FG); // replace the coing with an empty tile
				col->SetObject(x, y, Tiles::EMPTY_FG);
			}
			else if (id == Tiles::SPIKES) {
				sf::FloatRect pBounds = m_spr.getGlobalBounds();
				if (pBounds.top + pBounds.height >= y * TileSize + TileSize / 2 && // only if we hit the second half of the tile
				   !(pBounds.left >= x*TileSize + TileSize*0.7f || pBounds.left + pBounds.width <= x*TileSize + TileSize*0.3f)) { // allow for some 'error'
					m_spr.setPosition(m_spawn); // return to the spawn
					m_vel.x = 0;
					m_vel.y = 0;
					m_died = true; // dont update players position
				}
			}
		};
	}

	void Player::SetMap(ty::Map & map)
	{
		m_currentMap = &map; // set the current level tilemap
	}

	void Player::Update(float dt, cl::GridWorld& world)
	{
		// update elapsed time
		m_elTime += dt;

		while (m_elTime >= PhysicsStep) // make sure we do physics 60 times in a second
		{
			// check if any movement key is pressed
			int px = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) - (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));

			m_elTime -= PhysicsStep;
			m_prevPos = GetPosition();
			m_died = false;

			if (px == 0) // slow down our player if we are not moving (makes our player slightly slide)
				m_vel.x = m_vel.x - m_vel.x*SlowdownX*PhysicsStep;
			else // update the velocity
				m_vel.x = std::max(-MaxXVelocity, std::min(MaxXVelocity, m_vel.x + px*PhysicsStep*AccelerationX));

			// jump
			if (m_onPlatform && m_vel.y >= 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
				m_vel.y = -JumpVelocity;

			// gravity
			m_vel.y = std::max(-MaxYVelocity, std::min(MaxYVelocity, m_vel.y + PhysicsStep*Gravity));

			// calculate the end position using the velocity
			sf::Vector2f goal(m_prevPos.x + PhysicsStep*m_vel.x, m_prevPos.y + PhysicsStep*m_vel.y);

			// get player position after applying collision
			sf::Vector2f result = Utils::Convert(world.Check(2, Utils::Convert(m_spr.getGlobalBounds()), Utils::Convert(goal), m_onCollision));

			// did we die? if yes, dont update player position
			if (m_died)
				return;

			// stop player from leaving world bounds
			result.x = std::max(0.f, std::min((MapWidth - 1.f)*TileSize, result.x));
			result.y = std::max(0.f, std::min((MapHeight - 1.f)*TileSize, result.y));

			// check if we are standing on the platform
			m_onPlatform = (result.y == m_prevPos.y && m_vel.y > 0);

			// if we are, set the vertical velocity to 0
			if (m_onPlatform)
				m_vel.y = 0;

			// did we just hit the bottom of a tile? set the vertical velocity to 0 - start falling
			if (!m_onPlatform && (int)result.y != (int)goal.y && m_vel.y < 0)
				m_vel.y = 0;

			// horizontal direction change
			if (result.x == m_prevPos.x && Utils::Sign(m_vel.x) != px)
				m_vel.x = 0;

			// update the player position
			m_spr.setPosition(result);
		}
	}

	void Player::Draw(sf::RenderTarget& tgt)
	{
		sf::Vector2f pos = GetPosition();
		sf::Vector2f iPos = GetInterpolationPos();

		m_spr.setPosition(iPos);
		tgt.draw(m_spr);

		m_spr.setPosition(pos);
	}

	sf::Vector2f Player::GetInterpolationPos()
	{
		float alpha = m_elTime / PhysicsStep;
		sf::Vector2f futurePos = GetPosition();

		return futurePos * alpha + m_prevPos * (1.0f - alpha);
	}
}