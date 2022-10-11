#pragma once

namespace Mac {

	enum PLAYER_STATE
	{
		  IDLE = 0
		, MOVING_LEFT
		, MOVING_RIGHT
		, JUMPING
		, FALLING
	};

	struct Player
	{
		Player();
		virtual ~Player();

		const bool& getAnimationSwitch();
		const sf::FloatRect getGlobalBounds() const;
		const sf::Vector2f getPosition() const;

		void setPosition(const float x, const float y);
		void resetVelocityY();

		void resetAnimationTimer();
		void move(const float dirX, const float dirY);
		void updatePhysics();
		void updateMovement();
		void updateAnimations();
		void update();
		void render(sf::RenderTarget& target);

		void canJump();
		sf::Vector2f setScale(float x, float y);
	private:
		sf::Sprite sprite;
		sf::Texture textureSheet;
		sf::IntRect currentFrame;
		sf::Clock animationTimer;
		sf::Vector2f velocity;
		sf::Vector2f scale;

		short animationState;

		bool moving;
		bool jumping;
		bool animationSwitch;

		float velocityMax;
		float velocityMin;
		float acceleration;
		float drag;
		float gravity;
		float velocityMaxY;

		void initVariables();
		void initTexture();
		void initSprite();
		void initAnimations();
		void initPhysics();
	};
}