#include "Enemy.h"

namespace Mac {

	Enemy::Enemy(float X_Pos, float Y_Pos)
	{
		this->initVariables();
		this->initShape();
		this->shape.setPosition(X_Pos, Y_Pos);
	}

	const sf::FloatRect Enemy::getBounds() const
	{
		return this->shape.getGlobalBounds();
	}

	const int& Enemy::getPoints() const
	{
		return this->points;
	}

	const int& Enemy::getDamage() const
	{
		return this->damage;
	}

	void Enemy::update()
	{
		this->shape.move(0.0f, this->speed);
	}

	void Enemy::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
	}

	void Enemy::initShape()
	{
		this->shape.setRadius(this->complexity * 5);
		this->shape.setPointCount(this->complexity);
		this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	}

	void Enemy::initVariables()
	{
		complexity = rand() % 8 + 3;
		type = 0;
		hpMax = static_cast<int>(this->complexity);
		hp = this->hpMax;
		damage = this->complexity;
		points = this->complexity * 2;
		speed = static_cast<float>(this->complexity / 3);
	}

}