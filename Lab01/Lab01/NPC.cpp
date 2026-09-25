#include "NPC.h"
#include "CollisionAvoidance.h"

NPC::NPC(SteeringBehaviour* t_behaviour, int t_behaviourType, float t_speed, int t_id) : behaviour(t_behaviour), behaviourType(t_behaviourType), speed(t_speed), id(t_id)
{
	init();
}
void NPC::init()
{
	active = true;
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
	if (!nameFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "Problem loading font" << std::endl;
	}
	nameText.setFont(nameFont);
	nameText.setCharacterSize(20);
	nameText.setFillColor(sf::Color::White);
	nameText.setPosition(position - textOffset);

	switch (behaviourType)
	{
	case 1:
	{
		nameText.setString("Seeking");
		break;
	}
	case 2:
	{
		nameText.setString("Wandering");
		break;
	}
	case 3:
	{
		nameText.setString("Arriving");
		break;
	}
	case 4:
	{
		nameText.setString("Pursuing");
		break;
	}
	}

	std::cout << "Tie Rotation: " << randomNum << std::endl;
}

void NPC::update(sf::Time t_deltaTime)
{

	if (active)
	{
		steeringOutput totalSteering{ { 0.0f,0.0f }, 0.0f };
		nameText.setFillColor(sf::Color::White);
		if (behaviour != nullptr)
		{
			totalSteering = behaviour->getSteering(position, playerTarget->getPosition(), velocity, playerTarget->getVelocityVector(), speed);
		}

		if (avoidBehaviour != nullptr)
		{
			steeringOutput avoidSteering = avoidBehaviour->getSteering(position, { 0.0f,0.0f }, velocity, { 0.0f,0.0f }, 100.0f);

			if (avoidSteering.linear.x != 0 || avoidSteering.linear.y != 0)
			{
				totalSteering.linear += avoidSteering.linear;
			}
		}
		velocity += totalSteering.linear * t_deltaTime.asSeconds();

		position += velocity * t_deltaTime.asSeconds();
	}
	else
	{
		nameText.setFillColor(sf::Color::Red);
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
	nameText.setPosition(position - textOffset);
	velocity.x *= 0.97f;
	velocity.y *= 0.97f;
}

void NPC::setupAvoidance(std::vector<NPC*>* t_npcList)
{
	CollisionAvoidance* avoidance = new CollisionAvoidance;
	avoidance->setParameters(this, t_npcList);
	avoidBehaviour = avoidance;
}

void NPC::setRotationInDir()
{
	rotation = sf::radians(atan2(velocity.y, velocity.x)) + sf::degrees(90.0f);
	tie.setRotation(rotation);
}

bool NPC::checkIfInsideVisionCone(sf::Vector2f t_targetPos)
{
	sf::Vector2f dirToTarget = t_targetPos - position;
	float distance = std::sqrt((dirToTarget.x * dirToTarget.x) + (dirToTarget.y * dirToTarget.y));

	if (distance > 200.0f || distance == 0.0f)
	{
		return false;
	}

	sf::Vector2f normDir = dirToTarget / distance;

	float forwardRadians = rotation.asRadians() - (3.14f / 2.0f);
	sf::Vector2f myOrientation = { std::cos(forwardRadians), std::sin(forwardRadians) };

	float dotProduct = (normDir.x * myOrientation.x) + (normDir.y * myOrientation.y);
	if (dotProduct < -1.0f) dotProduct = -1.0f;
	if (dotProduct > 1.0f) dotProduct = 1.0f;

	float angleDegrees = std::acos(dotProduct) * (180.0f / 3.14f);

	return angleDegrees < 90.0f;
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(tie);
	t_window.draw(nameText);
}
