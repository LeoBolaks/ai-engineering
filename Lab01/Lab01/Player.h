#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Player
{
public:
	Player();

	void init();

	void update(sf::Time t_deltaTime);

	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getVelocityVector() { return direction * velocity; }

	void draw(sf::RenderWindow& t_window);

private:
	sf::Texture xWingTexture;
	sf::Sprite xWing{ xWingTexture };
	sf::Vector2f scale{};
	sf::Vector2f position;
	sf::Vector2f direction;
	float randomNum;
	sf::Angle rotationDegrees;
	float rotation;

	float turnAccel = 1400.0f;   
	float turnFriction = 720.0f; 
	float maxTurnSpeed = 180.0f; 

	float velAccel = 1400.0f;    
	float velBrake = 1000.0f;    
	float maxVelocity = 900.0f;  

	float velocity;
	float turnSpeed;
};