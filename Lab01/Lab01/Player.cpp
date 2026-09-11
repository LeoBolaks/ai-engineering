#include "Player.h"

Player::Player()
{
	init();
}

void Player::init()
{	
	scale = { 0.2f,0.2f };
	velocity = 10.0f;
	randomNum = rand() % 360;
	rotation = sf::degrees(randomNum);

	if (!xWingTexture.loadFromFile("ASSETS\\IMAGES\\X-WING.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading X-Wing" << std::endl;
	}

	xWing.setTexture(xWingTexture, true);// to reset the dimensions of texture
	xWing.setPosition(sf::Vector2f{ 100.0f, 400.0f });
	xWing.setScale(scale);
	xWing.setOrigin(sf::Vector2f{ 300.0f, 330.5f });
	xWing.setRotation(rotation);
}

void Player::update()
{

}

void Player::draw(sf::RenderWindow &t_window)
{
	t_window.draw(xWing);
}
