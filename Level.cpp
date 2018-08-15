#include "Level.h"
#include "Tiles.h"
#include "Config.h"
#include "libs/Tily.h"
#include <fstream>

namespace gm
{
	Level::Level(sf::RenderWindow & tgt)
	{
		m_wnd = &tgt;

		ty::Settings::TileSize = TileSize;
		ty::Settings::TextureSize = MaxTextureSize;
		ty::Settings::ChunkWidth = ChunkWidth;
		ty::Settings::ChunkHeight = ChunkHeight;

		m_fg.loadFromFile("data/tileset1.png");
		m_dec.loadFromFile("data/tileset2.png");

		m_bgTex.loadFromFile("data/bg.png");
		m_bg.setTexture(m_bgTex);

		m_load("data/level.bin");

		// set our filter that will decide if a tile is solid or not
		m_world.GetCollisionType = [](int id) -> cl::CollisionType {
			if (id == Tiles::COIN || id == Tiles::SPIKES)
				return cl::CollisionType::Cross;
			if (id >= Tiles::EMPTY_DEC || id == Tiles::EMPTY_FG)
				return cl::CollisionType::None;
			return cl::CollisionType::Solid;
		};

		m_clock.restart();
	}
	void Level::CreatePlayer(Player & pl)
	{
		pl.SetMap(m_tmap);
	}
	void Level::Update(Player & pl)
	{
		m_elTime = m_clock.restart().asSeconds();

		pl.Update(m_elTime, m_world);
	}
	void Level::Draw(Player& pl)
	{
		// render the background that follows the camera 
		m_bg.setPosition(m_wnd->mapPixelToCoords(sf::Vector2i(0, 0)));
		m_wnd->draw(m_bg);

		m_tmap.DrawLayer(0, *m_wnd, sf::RenderStates(&m_fg)); // render the foreground layer - blocks
		pl.Draw(*m_wnd); // draw the player
		m_tmap.DrawLayer(1, *m_wnd, sf::RenderStates(&m_dec)); // render all the decorations
	}
	void Level::m_load(std::string filename)
	{
		std::streampos size;
		char * memblock;

		std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			memblock = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(memblock, size);
			file.close();

			if (size < 1)
				return;

			// first two bytes tell us the size
			int width = memblock[0];
			int height = memblock[1];

			// check if the size is valid
			if (size < width*height * 2 + 2)
				return;

			m_tmap.Create(width, height, 2);
			m_world.Create(width, height, TileSize, TileSize);

			// read 1 byte for layer, one byte for id
			for (int i = 0; i < width*height * 2; i += 2) {
				int ai = i / 2;
				int ri = i + 2;

				int bx = ai % width;
				int by = ai / width;

				int layer = memblock[ri];
				int id = memblock[ri + 1];

				m_tmap.Set(bx, by, layer, id);
				m_world.SetObject(bx, by, (layer*Tiles::EMPTY_DEC) + id);
			}

			delete[] memblock;
		}
	}
}