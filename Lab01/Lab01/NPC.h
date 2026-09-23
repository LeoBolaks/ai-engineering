#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Player.h"
#include "SteeringBehaviour.h"

class NPC
{
public:
	NPC(SteeringBehaviour* t_behaviour, float t_speed);

	void init();

	void update(sf::Time t_deltaTime);

	void setPlayer(Player* t_player) { playerTarget = t_player; }

	void setRotationInDir();

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
	float speed;

	SteeringBehaviour* behaviour{ nullptr };
	Player* playerTarget{ nullptr };
};