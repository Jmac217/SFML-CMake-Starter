#pragma once

#include "Tile.h"

namespace Mac {

	struct TileMap
	{
		TileMap();
		~TileMap();

		void addTile(unsigned x, unsigned y);
		void removeTile(unsigned x, unsigned y);

		void update();
		void render();

	private:
		std::vector<std::vector<Tile*>> tiles;
	};
}