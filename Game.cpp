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
    this->paddleSize = sf::Vector2f(200, 50);
    this->paddleSpeed = 400.f;
    this->isPlaying = false;
    this->ballAngle = 0.f; // TODO
    this->ballRadius = 40.f;
    this->pi = 3.14159f;
    this->ballSpeed = 400.f;
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
    if (!this->font.loadFromFile("resources/cheeseburger.ttf"))
        return exit(0);
}

/**
 * Creates a global text variable that is meant to display
 * a simple message on the window.
 */
void Game::initMessages(){
    this->defaultMessage.setFont(font);
    this->defaultMessage.setCharacterSize(40);
    this->defaultMessage.setPosition(170.f, 200.f);
    this->defaultMessage.setFillColor(sf::Color::White);
    this->defaultMessage.setString("Everything is set up correctly!\n\nPress esc to exit the window.");
}

/**
 * Creates paddle that moves along the x axis
 */
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

void Game::initBall(){
    // Create the rum ball
    this->ball.setRadius(ballRadius - 3);
    //this->ball.setOutlineThickness(2);
    this->ball.setOutlineColor(sf::Color::Black);
    this->ball.setFillColor(sf::Color::White);
    this->ball.setOrigin(ballRadius / 1, ballRadius / 1);
    if (!this->balltexture.loadFromFile("resources/rumball.png"))
        return exit(0);
    this->ball.setTexture(&balltexture);
}

/**
 * Polls for left and right arrows to move paddle
 */
void Game::movePaddle(){
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
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
    //     (paddle.getPosition().x - paddleSize.y / 2 > 5.f)){
    //     paddle.move(0.f, -paddleSpeed * deltaTime);
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
    //     (paddle.getPosition().x + paddleSize.y / 2 < gameWidth - 5.f)){
    //     paddle.move(0.f, paddleSpeed * deltaTime);
    // }
    float factor = ballSpeed * deltaTime;
    ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
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
            if (((this->event.type == sf::Event::KeyPressed) && (this->event.key.code == sf::Keyboard::Space)) ||
                (this->event.type == sf::Event::TouchBegan)){
                if (!this->isPlaying){
                    // (re)start the game
                    this->isPlaying = true;
                    clock.restart();

                    // Reset the position of the paddles and ball
                    paddle.setPosition(10.f + paddleSize.x / 2.f, gameHeight - 10.f - paddleSize.y);
                    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);

                    // Reset the ball angle
                    do{
                        // Make sure the ball initial angle is not too much vertical
                        ballAngle = static_cast<float>(std::rand() % 360) * 2.f * pi / 360.f;
                    }
                    while (std::abs(std::cos(ballAngle)) < 0.7f);
                }
            }
            // TODO menu screen button
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                this->defaultMessage.setString("Everything is set up correctly!\n\nPress esc to exit the window.");
                this->window->draw(defaultMessage);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                this->defaultMessage.setString("YOU PRESSED UP!\n\nPress esc to exit the window.");
                this->window->draw(defaultMessage);   
            }
                 
        }
}

void Game::checkCollisions(){
    // Check collisions between the ball and the screen
    const std::string inputString = "Press space to restart or\nescape to exit.";
    if (ball.getPosition().x <= 0.f){
        this->ballAngle = pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;
        this->ball.setPosition(0.1f, ball.getPosition().y);
    }
    if (ball.getPosition().x > gameWidth){
        this->ballAngle = pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;
        this->ball.setPosition(gameWidth, ball.getPosition().y);
    }
    if (ball.getPosition().y - ballRadius < 0.f){
        this->ballAngle = -ballAngle;
        this->ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
    }
    if (ball.getPosition().y + ballRadius > gameHeight){
        this->isPlaying = false;
        defaultMessage.setString("You Lost!\n\n" + inputString);
    }
    // Check the collisions between the ball and the paddles
    // TODO need to fix y axis collision
    if (ball.getPosition().x - ballRadius < paddle.getPosition().x + paddleSize.x / 2 &&
        ball.getPosition().x - ballRadius > paddle.getPosition().x - paddleSize.x / 2 &&
        ball.getPosition().y + ballRadius >= paddle.getPosition().y - paddleSize.y / 2 + 0.1f &&
        ball.getPosition().y - ballRadius <= paddle.getPosition().y + paddleSize.y / 2 + 0.1f){
        if (ball.getPosition().x >= paddle.getPosition().x)// TODO may need to change this to reflect x axis
            this->ballAngle = pi + ballAngle + static_cast<float>(std::rand() % 20) * pi / 180;
        else
            this->ballAngle = pi + ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;
        
        this->ball.setPosition(ball.getPosition().x, paddle.getPosition().y - ballRadius - paddleSize.y / 2 - 0.1f);
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
    if (this->isPlaying){
        // Move user paddle
        this->movePaddle();
        //Display default message
        // this->window->draw(defaultMessage);
        this->window->draw(ball);
        this->window->draw(paddle); // Need to center
        this->checkCollisions();
    }
    else{
        this->window->draw(defaultMessage);
    }

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
    this->initBall();
}