#include "NPC.h"

NPC::NPC()
{
	init();
}

void NPC::init()
{
	scale = { 0.15f,0.15f };
	velocity = 10.0f;
	position = { 600.0f, 400.0f };
	randomNum = rand() % 360;

	float radians = randomNum * (3.14f / 180.0f);
	direction = { std::cos(radians), std::sin(radians) };

	rotation = sf::degrees(randomNum + 90.0f);

	if (!tieTexture.loadFromFile("ASSETS\\IMAGES\\TIE.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading X-Wing" << std::endl;
	}

	tie.setTexture(tieTexture, true);// to reset the dimensions of texture
	tie.setPosition(position);
	tie.setScale(scale);
	tie.setOrigin(sf::Vector2f{ 230.5f, 283.0f });
	tie.setRotation(rotation);
	std::cout << "Tie Rotation: " << randomNum << std::endl;
}

void NPC::update()
{
	position.x += direction.x * velocity;
	position.y += direction.y * velocity;

	tie.setPosition(position);

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
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(tie);
}
