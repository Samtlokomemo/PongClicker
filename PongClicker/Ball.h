#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Ball(float x, float y, float radius, sf::Color color);
    
    void update(sf::Time dt, float windowHeight);

    void bounceY();
    void bounceX();

    void reset(sf::Vector2f position, sf::Vector2f startVelocity);
};

