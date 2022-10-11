#include "pch.h"
#include "Tile.h"

namespace Mac {

	

	Tile::Tile(sf::Texture& textureSheet, sf::IntRect textureRect, bool damaging /*= false*/)
		: damaging(damaging)
	{
		this->sprite.setTexture(textureSheet);
		this->sprite.setTextureRect(textureRect);
	}

	const sf::FloatRect Tile::getGlobalBounds() const
	{
		return this->sprite.getGlobalBounds();
	}

	void Tile::update()
	{

	}

	void Tile::render(sf::RenderTarget& target)
	{
		target.draw(this->sprite);
	}

}