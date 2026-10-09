#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Player.h"
#include "SteeringBehaviour.h"

class NPC
{
public:
	NPC(SteeringBehaviour* t_behaviour, int t_behaviourType, float t_speed, int t_id);

	void init();

	void update(sf::Time t_deltaTime);

	void setPlayer(Player* t_player) { playerTarget = t_player; }
	void setupAvoidance(std::vector<NPC*>* t_npcList);

	void setRotationInDir();

	void toggleActive() 
	{ 
		active = !active;
		velocity = { 1.0f, 1.0f };
	}

	void setConeColour(sf::Color t_colour) { coneColour = t_colour; }

	int getID() { return id; }

	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getVelocity() { return velocity; }

	bool checkIfInsideVisionCone(sf::Vector2f t_targetPos);

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
	int id;
	int behaviourType;
	float coneAngle;

	sf::ConvexShape cone;
	sf::Color coneColour;

	bool active;
	bool standardBehaviour;
	bool pursueNPC;
	//bool pauseBehaviour = false;

	//sf::Clock pauseClock;
	//float pauseDuration = 2.0f;

	SteeringBehaviour* behaviour{ nullptr };
	SteeringBehaviour* avoidBehaviour{ nullptr };
	Player* playerTarget{ nullptr };

	steeringOutput totalSteering;

	sf::Font nameFont;
	sf::Text nameText{nameFont};
	sf::Vector2f textOffset{ -30.0f, 70.0f };
};