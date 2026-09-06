#pragma once
#include<SFML/Graphics.hpp>

struct objectbody {
	sf::Shape* body_shape;
	float radius;
	float mass;
	float e;

	bool hitx = false;
	bool hity = false;
	bool displace = true;

	sf::Vector2f velocity;

	sf::Vector2f current_position;
	sf::Vector2f predicted_position;
};

struct vector_scalar_pair {
	sf::Vector2f distance_vector;
	float scalar;
};

objectbody make_objectbody(float radius, sf::Vector2f current_current_position = { 0.0,0.0 }, sf::Color clr = sf::Color::Red,float co_e=1.0, float mass = 1);

sf::RenderWindow windowmaker();

vector_scalar_pair find_distance(sf::Shape* shp1, sf::Shape* shp2);

float dotproduct(sf::Vector2f a, sf::Vector2f b);