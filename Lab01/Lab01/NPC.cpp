#include "NPC.h"

NPC::NPC(SteeringBehaviour* t_behaviour, float t_speed) : behaviour(t_behaviour), speed(t_speed)
{
	init();
}
void NPC::init()
{
	scale = { 0.15f,0.15f };
	position = { 600.0f, 400.0f };
	randomNum = rand() % 360;

	float radians = randomNum * (3.14f / 180.0f);
	direction = { std::cos(radians), std::sin(radians) };

	rotation = sf::degrees(randomNum + 90.0f);

	if (!tieTexture.loadFromFile("ASSETS\\IMAGES\\TIE.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Tie" << std::endl;
	}

	tie.setTexture(tieTexture, true);// to reset the dimensions of texture
	tie.setPosition(position);
	tie.setScale(scale);
	tie.setOrigin(sf::Vector2f{ 230.5f, 283.0f });
	tie.setRotation(rotation);
	std::cout << "Tie Rotation: " << randomNum << std::endl;
}

void NPC::update(sf::Time t_deltaTime)
{	
	if (behaviour != nullptr)
	{
		steeringOutput steer = behaviour->getSteering(position, playerTarget->getPosition(), velocity, playerTarget->getVelocityVector(), speed);

		velocity += steer.linear * t_deltaTime.asSeconds();

		position += velocity * t_deltaTime.asSeconds();

	}

	setRotationInDir();

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

	tie.setPosition(position);
	velocity.x *= 0.97f;
	velocity.y *= 0.97f;
}

void NPC::setRotationInDir()
{
	rotation = sf::radians(atan2(velocity.y, velocity.x)) + sf::degrees(90.0f);
	tie.setRotation(rotation);
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(tie);
}
