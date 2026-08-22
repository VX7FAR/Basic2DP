//1m = 100units (pixels)

#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<map>
using namespace std;

vector<objectbody> bodies;

struct objectbody {
	sf::Shape* body_shape;
	float radius;
	float weight;
	float x_velocity;
	float y_velocity;
	float x_position;
	float y_position;
};

class Basic2DP {
public:
	void add_new_component(objectbody body ) {
		bodies.push_back(body);
	}
	void process_movement(float delta_t) {
		for (objectbody body : bodies) {
			body.body_shape->setPosition({ body.x_position + body.x_velocity * delta_t, body.y_position + body.y_velocity * delta_t });
		}
	}
};


enum shapetype {
	circle, rectangle
};

sf::Shape* shapemaker(shapetype type, sf::Vector2f size, sf::Color color = sf::Color::Blue) {
	if (type == circle) {
		sf::CircleShape circle(size.x);
		circle.setFillColor(color);
		circle.setOrigin(sf::Vector2f{ size.x , size.y });
		return new sf::CircleShape(circle);
	}
	else if (type == rectangle) {
		sf::RectangleShape rectange(size);
		rectange.setFillColor(color);
		rectange.setOrigin(sf::Vector2f{ size.x / (float)2.0, size.y / (float)2.0 });
		return new sf::RectangleShape(rectange);
	}
	else
	{
		return nullptr;
	}
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

int main() {
	Basic2DP manager;

	sf::RenderWindow window = windowmaker();
	
	sf::Shape* circle = shapemaker(shapetype::circle, { 20,20 });
	circle->setPosition({ 0,0 });

	sf::Shape* circle2 = shapemaker(shapetype::circle, { 20,20 }, sf::Color::Cyan);
	circle2->setPosition({ 110,110 });

	sf::Shape* border = shapemaker(shapetype::rectangle, { 840,640 }, sf::Color::Transparent);
	border->setOrigin(sf::Vector2f{ 420.0,320.0 });
	border->setOutlineThickness(-20);
	border->setOutlineColor(sf::Color::Red);

	while (window.isOpen()) {
		window.clear();
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		window.draw(*border);
		window.draw(*circle);
		window.draw(*circle2);
		window.display();

		cout << window.getSize().y << endl;
	}
}