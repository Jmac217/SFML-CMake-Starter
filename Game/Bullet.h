#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace Mac {

	struct Bullet
	{
		Bullet(sf::Texture* Texture
			, float X_Pos
			, float Y_Pos
			, float X_Vel
			, float Y_Vel
			, float Speed);

		Bullet() = default;
		virtual ~Bullet() = default;

		const sf::FloatRect getBounds() const;

		void Update();
		void Render(sf::RenderTarget* target);
	private:
		sf::Sprite shape;

		sf::Vector2f direction;
		float speed;
	};
}