#include "Player.h"

namespace Mac {

	Player::Player()
	{
		this->initVariables();
		this->initTexture();
		this->initSprite();
	}

	const sf::Vector2f& Player::getPos() const
	{
		return this->sprite.getPosition();
	}

	const sf::FloatRect Player::getBounds() const
	{
		return this->sprite.getGlobalBounds();
	}

	const int& Player::getHP() const
	{
		return this->hp;
	}

	const int& Player::getHPMax() const
	{
		return this->hpMax;
	}

	void Player::setPosition(sf::Vector2f pos)
	{
		this->sprite.setPosition(pos);
	}

	void Player::setPosition(float X, float Y)
	{
		this->sprite.setPosition(X, Y);
	}

	void Player::setHP(const int HP)
	{
		this->hp = HP;
	}

	void Player::loseHP(const int HP)
	{
		this->hp -= HP;
		if (this->hp < 0)
			this->hp = 0;
	}

	void Player::Move(const float X, const float Y)
	{
		this->sprite.move(this->Speed * X, this->Speed * Y);
	}

	const bool Player::canAttack()
	{
		if (this->attackCooldown >= this->attackCooldownMax)
		{
			this->attackCooldown = 0.0f;
			return true;
		}
		return false;
	}

	void Player::Update()
	{
		this->updateAttack();
	}

	void Player::updateAttack()
	{
		if (this->attackCooldown < this->attackCooldownMax)
			this->attackCooldown += 0.8f;
	}

	void Player::Render(sf::RenderTarget& target)
	{
		target.draw(this->sprite);
	}

	void Player::initVariables()
	{
		this->Speed = 5.0f;
		this->attackCooldownMax = 10.0f;
		this->attackCooldown = this->attackCooldownMax;
		this->hpMax = 100;
		this->hp = 100;
	}

	void Player::initTexture()
	{
		// Texture From File
		if (!this->texture.loadFromFile("Textures/ship.png"))
		{
			std::cout << "No Texture" << std::endl;
		}
	}

	void Player::initSprite()
	{
		// Sprite from Texture
		this->sprite.setTexture(this->texture);
		this->sprite.scale(1.0f, 1.0f);
	}
}