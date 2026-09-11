#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Player
{
public:
	Player();

	void init();

	void update();

	void draw(sf::RenderWindow &t_window);

private:
	sf::Texture xWingTexture;
	sf::Sprite xWing{ xWingTexture };
	sf::Vector2f scale{};
	sf::Vector2f position;
	sf::Vector2f direction;
	float randomNum;
	sf::Angle rotation;
	float velocity;
};