#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "GenBall.h"

class Game
{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        bool endGame;
        sf::Event sfmlEvent;

        Player player;

        int points;

        sf::Font font;
        sf::Text guiText;
        sf::Text endGameText;

        std::vector<GenBall> gBalls;
        float spawnTimerMax;
        float spawnTimer;
        int maxGenBalls;
        
        void initVariables();
        void initWindow();
        void initFont();
        void initText();
 
    public:
        // Constructors and Destructors
        Game();
        ~Game();

        //Accessors
        const bool& getEndGame() const;

        //Modifiers

        //Functions
        const bool running() const;
        void pollEvents();

        void spawnGenBalls();
        const int randBallType();
        void updateCollision();
        void update();
        void updateGUI();
        void updatePlayer();

        void render();
        void renderGUI(sf::RenderTarget* target);
};
