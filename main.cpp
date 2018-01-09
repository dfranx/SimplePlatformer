#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Level.h"

int main()
{
	// create window
	sf::RenderWindow wnd;
	wnd.create(sf::VideoMode(800, 600), "TileTest");
	wnd.setFramerateLimit(60);

	// load a level and spawn the player
	gm::Level lvl(wnd);
	gm::Player pl(140, 70);

	// pass the map to the player class
	lvl.CreatePlayer(pl);

	sf::Clock clock;
	sf::Event event;

	while (wnd.isOpen()) {
		while (wnd.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				wnd.close();
			else if (event.type == sf::Event::Resized) {
				sf::View view(sf::FloatRect(0, 0, wnd.getSize().x, wnd.getSize().y));
				view.setCenter(wnd.getView().getCenter());
				wnd.setView(view);
			}
		}

		// physics
		lvl.Update(pl);

		// update view
		float elTime = clock.restart().asSeconds();
		sf::Vector2f pos = pl.GetInterpolationPos() + sf::Vector2f(32, 32);
		sf::View v = wnd.getView();
		v.setCenter(v.getCenter() + (pos - v.getCenter())*0.1f*(elTime / (1 / 60.f))); // asymptotic averaging
		wnd.setView(v);

		// render
		wnd.clear();
		lvl.Draw(pl);
		wnd.display();
	}

	return 0;
}

