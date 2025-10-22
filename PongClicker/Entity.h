#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	sf::RectangleShape shape;
	sf::Vector2f position, velocity;

	float acc, fric, maxSpeed, breakFac;

	Entity(float x, float y, float width, float height, sf::Color color);

	void move(bool moveUp, bool moveDown, sf::Time dt);
	void update(sf::Time dt, float windowHeight);
};

