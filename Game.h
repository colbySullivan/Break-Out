#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <cmath>
#include <list>

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
    float paddleSpeed;
    sf::Clock clock;
    float pi;
    int menuOption;
    bool ready;

    //Window setup
    sf::RenderWindow* window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

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
    float ballAngle;
    float ballRadius;
    float ballSpeed;
    sf::Texture balltexture;

    //Running events
    sf::Event event;
    bool isPlaying;

    std::list<sf::RectangleShape> m_block_list; 

    void initVariables();
    void initWindow();
    void initFonts();
	void initMessages();
    void initPaddle();
    void initBall();
    void initBlock();

public:
	//Constructors / Destructors
	Game();

	//Accessors
	const bool running() const;
    void checkMenu();

    //Functions
    void pollEvents();
    void movePaddle();
    void checkWallCollisions();
    void checkCollisions(sf::RectangleShape, bool);
    void blockCollisions();
    void displayBlocks();
    void rungame();
};