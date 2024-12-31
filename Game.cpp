#include "Game.h"

// Init Variables
#pragma region Init_Variables
void Game::initVariables()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxGenBalls = 10;
    this->points = 0;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initFont()
{
    if(!this->font.loadFromFile("/home/povo/workspace/sfml/Fonts/Roboto/Roboto-Black.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::COULD NOT LOAD Roboto-Black.ttf FONT" << "\n";
    }
}

void Game::initText()
{
    //Gui text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(32);

    //Endgame text init
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(40);
    this->endGameText.setPosition(sf::Vector2f(20, 300));
    this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}
#pragma endregion Init_Variables

// Constructors and Destructors
#pragma region Constructors_Desturctors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}
#pragma endregion Constructors_Destructros

// Accessors
#pragma region Accessors
const bool & Game::getEndGame() const
{
    return this->endGame;
}
#pragma endregion Accessors

//Modifiers
#pragma region Modifiers
#pragma endregion Modifiers

//Functions
#pragma region Functions
const bool Game::running() const
{
    return this->window->isOpen();// && this->endGame == false;
}
void Game::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch(this->sfmlEvent.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::spawnGenBalls()
{
    //Timer
    if (this->spawnTimer < this->spawnTimerMax)
    {
        this->spawnTimer += 1.f;
    }
    else
    {
        if(this->gBalls.size() < this->maxGenBalls)
        {
            this->gBalls.push_back(GenBall(*this->window, this->randBallType()));
            this->spawnTimer = 0.f;
        }
    }
}

const int Game::randBallType()
{
    int type = GenBallTypes::DEFAULT;
    int randValue = rand() % 100 + 1;

    if(randValue > 60 && randValue <= 80)
    {
        type = GenBallTypes::DAMAGING;
    }
    else if (randValue > 80 && randValue <=100)
    {
        type = GenBallTypes::HEALING;
    }

    return type;
}

void Game::updateCollision()
{
    //Check the collision
    for (size_t i = 0; i < this->gBalls.size(); i ++)
    {
        if(this->player.getShape().getGlobalBounds().intersects(this->gBalls[i].getShape().getGlobalBounds()))
        {
            switch(this->gBalls[i].getType())
            {
                case GenBallTypes::DEFAULT:
                    this->points++;
                    break;
                case GenBallTypes::DAMAGING:
                    this->player.takeDamage(1);
                    break;
                case GenBallTypes::HEALING:
                    this->player.gainHealth(1);
                    break;
            }
            // Remove the ball
            this->gBalls.erase(this->gBalls.begin() + i);
        }
    }
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << " Points: " << this->points << "\n"
        << " - Health: " << this->player.getHp() 
        << "/" << this->player.getHpMax() << "\n";
    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();

    if(this->endGame == false)
    {
        this->spawnGenBalls();
        this->updatePlayer();
        this->updateCollision();
        this->updateGUI();
    }
}

void Game::updatePlayer()
{
    this->player.update(this->window);

    if(this->player.getHp() <= 0)
    {
        this->endGame = true;
    }
}

void Game::renderGUI(sf::RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear();

    //Render stuff
    this->player.render(this->window);
    
    for (auto i : this->gBalls)
    {
        i.render(*this->window);
    }

    //Render gui
    this->renderGUI(this->window);

    //Rendet end text
    if(this->endGame == true)
    {
        this->window->draw(this->endGameText);
    }
    this->window->display();
}
#pragma endregion Functions
