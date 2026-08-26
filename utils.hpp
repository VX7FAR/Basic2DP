#pragma once
#include<SFML/Graphics.hpp>

struct objectbody {
	sf::Shape* body_shape;
	float radius;
	float mass;

	float x_velocity;
	float y_velocity;

	float x_position;
	float y_position;
};

struct normals {
	float x_normal;
	float y_normal;
};

static objectbody make_objectbody(float radius, sf::Vector2f position = { 0.0,0.0 }, sf::Color clr = sf::Color::Red, float mass = 1);

sf::RenderWindow windowmaker();