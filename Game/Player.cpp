#include "pch.h"
#include "player.h"

namespace Mac {

	Player::Player()
	{
		this->initVariables();
		this->initTexture();
		this->initSprite();
		this->initAnimations();
		this->initPhysics();
	}

	Player::~Player()
	{

	}

	const bool& Player::getAnimationSwitch()
	{
		bool t_animationSwitch = this->animationSwitch;

		if (this->animationSwitch)
			this->animationSwitch = false;

		return t_animationSwitch;
	}

	const sf::FloatRect Player::getGlobalBounds() const
	{
		return this->sprite.getGlobalBounds();
	}

	const sf::Vector2f Player::getPosition() const
	{
		return this->sprite.getPosition();
	}

	void Player::setPosition(const float x, const float y)
	{
		this->sprite.setPosition(x, y);
	}

	void Player::resetVelocityY()
	{
		this->velocity.y = 0.0f;
	}

	void Player::resetAnimationTimer()
	{
		this->animationTimer.restart();
		this->animationSwitch = true;
	}

	void Player::move(const float dir_x, const float dir_y)
	{
		//Acceleration
		this->velocity.x += dir_x * this->acceleration;

		//Limit velocity
		if (std::abs(this->velocity.x) > this->velocityMax)
		{
			this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
		}
	}

	void Player::updatePhysics()
	{
		this->velocity.y += 1.0f * this->gravity;
		if (std::abs(this->velocity.x) > this->velocityMaxY)
		{
			this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.0f) ? -1.0f : 1.0f);
		}

		this->velocity *= this->drag;

		if (std::abs(this->velocity.x) < this->velocityMin)
			this->velocity.x = 0.0f;
		if (std::abs(this->velocity.y) < this->velocityMin)
			this->velocity.y = 0.0f;

		this->sprite.move(this->velocity);
	}

	void Player::updateMovement()
	{
		this->animationState = PLAYER_STATE::IDLE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->move(-1.0f, 0.0f);
			this->animationState = PLAYER_STATE::MOVING_LEFT;
		}
		else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->move(1.0f, 0.0f);
			this->animationState = PLAYER_STATE::MOVING_RIGHT;
		}
	}

	void Player::updateAnimations()
	{
		if (this->animationState == PLAYER_STATE::IDLE)
		{
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f
				|| this->getAnimationSwitch())
			{
				this->currentFrame.top = 0.0f;
				this->currentFrame.left += 40.0f;
				if (this->currentFrame.left >= 160.0f)
					this->currentFrame.left = 0.0f;

				this->animationTimer.restart();
				this->sprite.setTextureRect(this->currentFrame);
			}
			this->sprite.setScale(7, 7);
			this->sprite.setOrigin(0.0f, 0.0f);
		}
		else
		if (this->animationState == PLAYER_STATE::MOVING_RIGHT)
		{
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f
				|| this->getAnimationSwitch())
			{
				this->currentFrame.top = 50.0f;
				this->currentFrame.left += 40.0f;
				if (this->currentFrame.left >= 360.0f)
					this->currentFrame.left = 0.0f;

				this->animationTimer.restart();
				this->sprite.setTextureRect(this->currentFrame);
			}
				this->sprite.setScale(7, 7);
				this->sprite.setOrigin(0.0f, 0.0f);
		}
		else
		if (this->animationState == PLAYER_STATE::MOVING_LEFT)
		{
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f
				|| this->getAnimationSwitch())
			{
				this->currentFrame.top = 50.0f;
				this->currentFrame.left += 40.0f;
				if (this->currentFrame.left >= 360.0f)
					this->currentFrame.left = 0.0f;

				this->animationTimer.restart();
				this->sprite.setTextureRect(this->currentFrame);
			}
			this->sprite.setScale(-7, 7);
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 7.0f, 0.0f);
		}
		else
			this->animationTimer.restart();
	}

	void Player::update()
	{
		this->updateMovement();
		this->updateAnimations();
		this->updatePhysics();
	}

	void Player::render(sf::RenderTarget& target)
	{
		target.draw(this->sprite);
	}

	void Player::initVariables()
	{
		this->animationState = PLAYER_STATE::IDLE;
	}

	void Player::initTexture()
	{
		this->textureSheet.loadFromFile("Textures/player_sheet.png");
	}

	void Player::initSprite()
	{
		this->sprite.setTexture(this->textureSheet);
		this->currentFrame = sf::IntRect(0, 0, 40, 50);
		this->sprite.setTextureRect(this->currentFrame);
		this->sprite.setScale(7, 7);
	}

	void Player::initAnimations()
	{
		this->animationTimer.restart();
		this->animationSwitch = true;
	}

	void Player::initPhysics()
	{
		this->velocityMax = 22.0f;
		this->velocityMin = 1.0f;
		this->acceleration = 4.0f;
		this->drag = 0.83f;
		this->gravity = 4.0f;
		this->velocityMaxY = 15.0f;
	}

}