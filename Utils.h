#ifndef __GAME_UTILS_H__
#define __GAME_UTILS_H__

#include "libs/Colly/Colly.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace gm
{
	// convert SFML Rect and Vector2f to Colly Rect and Point (and the other way around)
	class Utils
	{
	public:
		inline static cl::Rect Convert(sf::FloatRect r) { return { r.left, r.top, r.width, r.height }; }
		inline static cl::Point Convert(sf::Vector2f p) { return { p.x, p.y }; }
		inline static sf::Vector2f Convert(cl::Point p) { return sf::Vector2f(p.X, p.Y); }
		inline static int Sign(float x) { return (x < 0) ? -1 : ((x > 0) ? 1 : 0); }
	};
}

#endif