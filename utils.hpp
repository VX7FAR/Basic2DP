#pragma once
#include<SFML/Graphics.hpp>

struct objectbody {
	sf::Shape* body_shape;
	float radius;
	float mass;

	sf::Vector2f velocity;

	sf::Vector2f position;
};

struct vector_scalar_pair {
	sf::Vector2f distance_vector;
	float scalar;
};

objectbody make_objectbody(float radius, sf::Vector2f position = { 0.0,0.0 }, sf::Color clr = sf::Color::Red, float mass = 1);

sf::RenderWindow windowmaker();

vector_scalar_pair find_distance(sf::Shape* shp1, sf::Shape* shp2);