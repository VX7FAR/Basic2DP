#include "utils.hpp"
#include <SFML/graphics.hpp>
#include<vector>

objectbody make_objectbody(float radius, sf::Vector2f position = { 0.0,0.0 }, sf::Color clr = sf::Color::Red, float mass = 1) {
	sf::CircleShape circle(radius);
	circle.setPosition(position);
	circle.setOrigin({ radius, radius });
	circle.setFillColor(clr);
	objectbody obj;
	obj.body_shape = new sf::CircleShape(circle);
	obj.radius = radius;
	obj.mass = mass;
	obj.x_position = circle.getPosition().x;
	obj.y_position = circle.getPosition().y;
	obj.x_velocity = 0.0;
	obj.y_velocity = 0.0;
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