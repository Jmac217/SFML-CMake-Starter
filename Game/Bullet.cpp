#include "Bullet.h"

namespace Mac {

	Bullet::Bullet(sf::Texture* Texture, float X_Pos, float Y_Pos, float X_Vel, float Y_Vel, float Speed)
	{
		this->shape.setTexture(*Texture);
		this->shape.setPosition(X_Pos, Y_Pos);
		this->direction.x = X_Vel;
		this->direction.y = Y_Vel;
		this->speed = Speed;
	}

	const sf::FloatRect Bullet::getBounds() const
	{
		return this->shape.getGlobalBounds();
	}

	void Bullet::Update()
	{
		this->shape.move(this->speed * this->direction);
	}

	void Bullet::Render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
	}

}