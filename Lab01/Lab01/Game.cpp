/// <summary>
/// author Pete Lowe May 2026
/// you need to change the above line or lose marks
/// </summary>


#include "Game.h"
#include <iostream>




/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{1000U, 800U}, 32U }, "SFML Game 3.1" },
	m_DELETEexitGame{false} //when true game will exit
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sound
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but method needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{	
	while ( std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			sf::Event::KeyPressed newKeypress;
			newKeypress = *newEvent->getIf<sf::Event::KeyPressed>();
			processKeyPress(newKeypress);
		}
		if (newEvent->is < sf::Event::MouseButtonPressed>()) // user pressed mouse button
		{
			sf::Event::MouseButtonPressed newMousePress;
			newMousePress = *newEvent->getIf<sf::Event::MouseButtonPressed>();
			processMousePress(newMousePress);
		}
		//could also check for mouse move, mouse wheel, text entered, window resized etc.
		// sf::Event::KeyReleased
		// sf::Event::MouseMoved
		// sf::Event::MouseButtonReleased
		// sf::Event::TextEntered

	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeyPress(sf::Event::KeyPressed t_keyPress)
{	
	if (sf::Keyboard::Key::Escape == t_keyPress.code)
	{
		m_DELETEexitGame = true; // only need one of these, but this is an example of checking events rather than state
	}
}

/// <summary>
/// deal with mouse button presses
/// </summary>
/// <param name="t_event">Mouse press event</param>
void Game::processMousePress(sf::Event::MouseButtonPressed t_mousePress)
{

}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; // only need one of these, but this is an example of checking state rather than events
	}
}

/// <summary>
/// check current status of mouse
/// </summary>
void Game::checkMouseState()
{
	
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	checkMouseState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{	
	player.draw(m_window);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupTexts()
{

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{
	//if (!m_DELETElogoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	//{
	//	// simple error message if previous call fails
	//	std::cout << "problem loading logo" << std::endl;
	//}
	//
	//m_DELETElogoSprite.setTexture(m_DELETElogoTexture,true);// to reset the dimensions of texture
	//m_DELETElogoSprite.setPosition(sf::Vector2f{ 100.0f, 50.0f });
}

/// <summary>
/// load sound file and assign buffers
/// </summary>
void Game::setupAudio()
{
	
}
