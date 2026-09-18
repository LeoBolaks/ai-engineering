#include "Player.h"

Player::Player()
{
	init();
}

void Player::init()
{
	scale = { 0.15f,0.15f };
	velocity = 0.0f;
	turnSpeed = 2.5f;
	position = { 100.0f, 400.0f };
	randomNum = rand() % 360;
	rotation = randomNum;

	float radians = rotation * (3.14f / 180.0f);
	direction = { std::cos(radians), std::sin(radians) };

	rotationDegrees = sf::degrees(rotation + 90.0f);

	if (!xWingTexture.loadFromFile("ASSETS\\IMAGES\\X-WING.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading X-Wing" << std::endl;
	}

	xWing.setTexture(xWingTexture, true);// to reset the dimensions of texture
	xWing.setPosition(position);
	xWing.setScale(scale);
	xWing.setOrigin(sf::Vector2f{ 300.0f, 330.5f });
	xWing.setRotation(rotationDegrees);
	std::cout << "X-Wing Rotation: " << randomNum << std::endl;
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		turnSpeed -= 0.4f;
		if (turnSpeed < -3.0f)
		{
			turnSpeed = -3.0f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		turnSpeed += 0.4f;
		if (turnSpeed > 3.0f)
		{
			turnSpeed = 3.0f;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (turnSpeed < 0)
		{
			turnSpeed += 0.2f;
			if (turnSpeed > 0.1)
			{
				turnSpeed = 0;
			}
		}
		if (turnSpeed > 0)
		{
			turnSpeed -= 0.2f;
			if (turnSpeed < 0.1)
			{
				turnSpeed = 0;
			}
		}
	}

	rotation += turnSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		velocity += 0.4f;
		if (velocity > 15.0f)
		{
			velocity = 15.0f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		velocity -= 0.3f;
		if (velocity < 0.0f)
		{
			velocity = 0.0f;
		}
	}

	float radians = rotation * (3.14 / 180.0f);
	direction = { std::cos(radians), std::sin(radians) };

	rotationDegrees = sf::degrees(rotation + 90.0f);
	xWing.setRotation(rotationDegrees);

	position.x += direction.x * velocity;
	position.y += direction.y * velocity;

	if (position.x < -20)
	{
		position.x = 1010;
	}
	else if (position.x > 1020)
	{
		position.x = -10;
	}

	if (position.y < -20)
	{
		position.y = 810;
	}
	else if (position.y > 820)
	{
		position.y = -10;
	}

	xWing.setPosition(position);

}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(xWing);
}
