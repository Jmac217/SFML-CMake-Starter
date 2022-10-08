#include "Ball.h"

namespace Mac {

	Ball::Ball(const sf::RenderWindow& window, int type)
		:type(type)
	{
		this->initShape(window);
	}

	Ball::~Ball()
	{

	}

	const sf::CircleShape Ball::getShape() const
	{
		return this->shape;
	}

	void Ball::update()
	{
		this->shape.move(sf::Vector2f(0.0f, 1.0f));
	}

	void Ball::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
	}

	const int& Ball::getType() const
	{
		return this->type;
	}

	void Ball::initShape(const sf::RenderWindow& window)
	{
		this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
		sf::Color color;
		switch (this->type)
		{
		case DEFAULT:
			color = sf::Color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
			break;
		case DAMAGING:
			color = sf::Color::Red;
			break;
		case HEALING:
			color = sf::Color::Green;
			break;
		}
		this->shape.setPosition(sf::Vector2f(static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
													static_cast<float>(this->shape.getGlobalBounds().height)));
		this->shape.setFillColor(color);
	}

}