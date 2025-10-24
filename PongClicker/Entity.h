#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

class Entity : Drawable{
public:
	unique_ptr<Shape> shape;
	Vector2f position, velocity;

	float acc, fric, maxSpeed, breakFac;

	Entity(float x, float y, float width, float height, sf::Color color, Shape shape);

	void move(bool moveUp, bool moveDown, sf::Time dt);
	void update(sf::Time dt, float windowHeight);
	void draw(RenderWindow window);
};

