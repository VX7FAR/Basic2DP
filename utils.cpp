#include "utils.hpp"
#include <SFML/graphics.hpp>
#include<vector>

objectbody make_objectbody(float radius, sf::Vector2f position, sf::Color clr, float mass) {
	sf::CircleShape circle(radius);
	circle.setPosition(position);
	circle.setOrigin({ radius, radius });
	circle.setFillColor(clr);
	objectbody obj;
	obj.body_shape = new sf::CircleShape(circle);
	obj.radius = radius;
	obj.mass = mass;
	obj.position.x = circle.getPosition().x;
	obj.position.y = circle.getPosition().y;
	obj.velocity.x = 0.0;
	obj.velocity.y = 0.0;
	obj.e = 1.0;
	return obj;
}

sf::RenderWindow windowmaker() {
	sf::View view;
	sf::RenderWindow window(sf::VideoMode({ 840,640 }), "adad");
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

float dotproduct(sf::Vector2f a, sf::Vector2f b) {
	return (a.x * b.x) + (a.y * b.y);
}