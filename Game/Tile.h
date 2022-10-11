#pragma once

namespace Mac {

	struct Tile
	{

		Tile(sf::Texture& textureSheet, sf::IntRect textureRect, bool damaging = false);
		~Tile() = default;

		const sf::FloatRect getGlobalBounds() const;

		void update();
		void render(sf::RenderTarget& target);

	private:
		sf::Sprite sprite;
		const bool damaging;
	};
}