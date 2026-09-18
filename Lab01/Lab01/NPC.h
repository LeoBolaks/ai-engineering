#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "SteeringBehaviour.h"

class NPC
{
public:
	NPC(SteeringBehaviour* t_behaviour);

	void init();

	void update();

	void draw(sf::RenderWindow& t_window);

private:
	sf::Texture tieTexture;
	sf::Sprite tie{ tieTexture };
	sf::Vector2f scale{};
	sf::Vector2f position;
	sf::Vector2f direction;
	float randomNum;
	sf::Angle rotation;
	sf::Vector2f velocity;

	SteeringBehaviour* behaviour;
};