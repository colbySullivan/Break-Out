#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/*
 *	Class that acts as the game engine.
 *	Wrapper class.
*/

class Game{
private:
    // Variables
    float gameWidth;
    float gameHeight;
    sf::Vector2f paddleSize;

    //Window setup
    sf::RenderWindow* window;

    // Set font
    sf::Font font;

    // Create text
    sf::Text defaultMessage;

    // Create paddles
    sf::RectangleShape paddle;
    sf::Texture paddleTexture;

    // Create ball
    sf::CircleShape ball;
    sf::Texture ballTexture;

    //Running events
    sf::Event event;

    void initVariables();
    void initWindow();
    void initFonts();
	void initMessages();
    void initPaddle();
public:
	//Constructors / Destructors
	Game();

	//Accessors
	const bool running() const;

    //Functions
    void pollEvents();
    void rungame();
};