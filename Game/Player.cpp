#include "Player.h"

namespace Mac {
	Player::Player(float x, float y)
	{
		this->shape.setPosition(x, y);
		this->movementSpeed = 10.0f;

		this->initVariables();
		this->initShape();
	}

	Player::~Player()
	{

	}

	const sf::RectangleShape& Player::getShape() const
	{
		return this->shape;
	}

	void Player::update(const sf::RenderTarget* target)
	{
		this->updateInput();

		this->updateWindowBoundsCollission(target);
	}

	void Player::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
	}

	void Player::updateInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->shape.move(-this->movementSpeed, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->shape.move(this->movementSpeed, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->shape.move(0.0f, -this->movementSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->shape.move(0.0f, this->movementSpeed);
		}
	}

	void Player::updateWindowBoundsCollission(const sf::RenderTarget* target)
	{
		if (this->shape.getGlobalBounds().left <= 0.0f)
			this->shape.setPosition(0.0f, this->shape.getGlobalBounds().top);
		else if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
			this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
		if (this->shape.getGlobalBounds().top <= 0.0f)
			this->shape.setPosition(this->shape.getGlobalBounds().left, 0.0f);
		else if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
			this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}

	const int& Player::getHP() const
	{
		return this->hp;
	}

	const int& Player::getHPMax() const
	{
		return this->hpMax;
	}

	void Player::takeDamage(const int damage)
	{
		if (this->hp > 0)
			this->hp -= damage;

		if (this->hp < 0)
			this->hp = 0;
	}

	void Player::gainHealth(const int health)
	{
		if (this->hp < this->hpMax)
			this->hp += health;

		if (this->hp > this->hpMax)
			this->hp = this->hpMax;
	}

	void Player::initVariables()
	{
		this->movementSpeed = 5.0f;
		this->hpMax = 10;
		this->hp = hpMax;
	}

	void Player::initShape()
	{
		this->shape.setFillColor(sf::Color::Yellow);
		this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
	}

}
