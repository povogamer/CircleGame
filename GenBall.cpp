#include "GenBall.h"

void GenBall::initShape(const sf::RenderWindow& window)
{
    this->shape.setRadius(static_cast<float>(rand()%10+10));
    sf::Color color;
    switch(this->type)
    {
        case DEFAULT:
            color = sf::Color(rand()%255 +1, rand()%255 +1, rand()%255 + 1);
            break;
        case DAMAGING:
            color = sf::Color::Red;
            this->shape.setOutlineColor(sf::Color::Red);
            this->shape.setOutlineThickness(2.f);
            break;
        case HEALING:
            color = sf::Color::Green;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;
    }
    this->shape.setFillColor(color);
    this->shape.setPosition(sf::Vector2f(
        static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
        static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)));
}

GenBall::GenBall(const sf::RenderWindow& window, int type) : type(type)
{
    this->initShape(window);
}

GenBall::~GenBall()
{}

const sf::CircleShape GenBall::getShape() const
{
    return this->shape;
}

const int& GenBall::getType() const
{
    return this->type;
}

void GenBall::update()
{}

void GenBall::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}
