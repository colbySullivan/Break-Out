#include "Game.h"
#include <string> 

/**
 * Initialize global variables
 *
 * Includes variables for the height and width of the window
 *
 */
void Game::initVariables(){
    this->gameWidth = 800;
    this->gameHeight = 600;
    this->paddleSize = sf::Vector2f(50, 100);
    this->paddleSpeed = 400.f;
}

/**
 * Creates a new window instance with the global size variables
 */
void Game::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight), 32), "Template",
                            sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);
}

/**
 * Font file can be found in the resource file
 * 
 * return True if file is found
 */
void Game::initFonts(){
    if (!this->font.loadFromFile("resources/tuffy.ttf"))
        return exit(0);
}

/**
 * Creates a global text variable that is meant to display
 * a simple message on the window.
 *
 */
void Game::initMessages(){
    this->defaultMessage.setFont(font);
    this->defaultMessage.setCharacterSize(40);
    this->defaultMessage.setPosition(170.f, 200.f);
    this->defaultMessage.setFillColor(sf::Color::White);
    this->defaultMessage.setString("Everything is set up correctly!\n\nPress esc to exit the window.");
}

void Game::initPaddle(){
      // Create the left paddle
    this->paddle.setSize(paddleSize - sf::Vector2f(3, 3));
    this->paddle.setOutlineThickness(3);
    this->paddle.setOutlineColor(sf::Color::Black);
    this->paddle.setFillColor(sf::Color(100, 100, 200));
    this->paddle.setOrigin(paddleSize / 2.f);
    if(!this->paddleTexture.loadFromFile("resources/leftpaddle.png"))
        return exit(0);
    this->paddle.setTexture(&paddleTexture);
}

void Game::movePaddles(){
    float deltaTime = clock.restart().asSeconds();
    // Move user paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        (paddle.getPosition().x - paddleSize.y / 2 > 5.f)){
        paddle.move(-paddleSpeed * deltaTime, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        (paddle.getPosition().x + paddleSize.y / 2 < gameWidth - 5.f)){
        paddle.move(paddleSpeed * deltaTime, 0.f);
    }
}

/**
 * return True if window is still opened
 */
const bool Game::running() const{
	return this->window->isOpen();
}

/**
 * Checks if any key has been pressed and runs an event accordingly
 */
void Game::pollEvents(){
    while (this->window->pollEvent(this->event)){
            // Window closed or escape key pressed: exit
            if ((this->event.type == sf::Event::Closed) ||
               ((this->event.type == sf::Event::KeyPressed) && (this->event.key.code == sf::Keyboard::Escape))){
                this->window->close();
                break;
            }
        }
}

/**
 * Main run file that polls and displays
 */
void Game::rungame(){
    // Handle events
    this->pollEvents();

    // Clear the window
    this->window->clear(sf::Color(0, 0, 0));

    // Move user paddle
    this->movePaddles();

    //Display default message
    this->window->draw(defaultMessage);
    this->window->draw(paddle); // Need to center

    // Display things on screen
    this->window->display();
}

/**
 * Default global variables for new game class instance
 *
 */
Game::Game(){
	this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initMessages();
    this->initPaddle();
}