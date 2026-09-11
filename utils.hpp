#pragma once
#include<SFML/Graphics.hpp>
#include<filesystem>
#include <string>

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

struct Theme {
	std::string name;
	sf::Color background;
	sf::Color border;
	sf::Color shape_clr;
};

objectbody make_objectbody(float radius, sf::Vector2f current_current_position = { 0.0,0.0 }, sf::Color clr = sf::Color::Red,float co_e=0.75, float mass = 1);

sf::RenderWindow windowmaker();

vector_scalar_pair find_distance(sf::Shape* shp1, sf::Shape* shp2);

bool stob(std::string s, std::string t_con = "true", std::string f_con = "false");

float dotproduct(sf::Vector2f a, sf::Vector2f b);

void correct_colour(sf::Vector3u& clr);

std::string filename_to_name(std::string filename);