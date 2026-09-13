#include "utils.hpp"
#include <SFML/graphics.hpp>
#include <vector>

objectbody make_objectbody(float radius, sf::Vector2f current_position, sf::Color clr, float co_e, float mass) {
	sf::CircleShape circle(radius);
	circle.setPosition(current_position);
	circle.setOrigin({ radius, radius });
	circle.setFillColor(clr);
	objectbody obj;
	obj.body_shape = new sf::CircleShape(circle);
	obj.radius = radius;
	obj.mass = mass;
	obj.current_position.x = circle.getPosition().x;
	obj.current_position.y = circle.getPosition().y;
	obj.velocity.x = 0.0;
	obj.velocity.y = 0.0;
	obj.e = co_e;
	return obj;
}

sf::RenderWindow windowmaker() {
	sf::View view;
	sf::RenderWindow window(sf::VideoMode({ 840,640 }), "Basic2DP", sf::Style::None);
	window.setFramerateLimit(60);
	view.setSize({ 840,-640 });
	view.setCenter({ 0,0 });
	window.setView(view);
	return window;
}

vector_scalar_pair find_distance(sf::Shape* shp1, sf::Shape* shp2) {
	vector_scalar_pair pair;
	pair.distance_vector.x = shp1->getPosition().x - shp2->getPosition().x;
	pair.distance_vector.y = shp1->getPosition().y - shp2->getPosition().y;
	pair.scalar = sqrt((pair.distance_vector.x * pair.distance_vector.x) + (pair.distance_vector.y * pair.distance_vector.y));
	return pair;
}

bool stob(std::string s, std::string t_con, std::string f_con) {
	if (t_con == f_con) {
		return true;
	}
	else if (s == "true" || s == "1" || s == t_con) {
		return true;
	}
	else if (s == "false" || s == "0" || s == f_con) {
		return false;
	}
}

float dotproduct(sf::Vector2f a, sf::Vector2f b) {
	return (a.x * b.x) + (a.y * b.y);
}

void correct_colour(sf::Vector3u& clr) {
	if (clr.x > 255 || clr.x < 0) {
		clr.x = 255;
	}
	if(clr.y > 255 ||clr.y < 0)
	{
		clr.y = 255;
	}
	if (clr.z > 255 || clr.z < 0)
	{
		clr.z = 255;
	}
}

std::string filename_to_name(std::string filename) {
	filename.erase(filename.size() - 4);
	return filename;
}