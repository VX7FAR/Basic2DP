//1m = 100units (pixels)

#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
using namespace std;

enum shapetype {
	circle, rectangle
};

sf::Shape* shapemaker(shapetype type, sf::Vector2f size, sf::Color color) {
	if (type == circle) {
		sf::CircleShape circle(size.x);
		circle.setFillColor(color);
		return new sf::CircleShape(circle);
	}
	else if (type == rectangle) {
		sf::RectangleShape rectange(size);
		rectange.setFillColor(color);
		return new sf::RectangleShape(rectange);
	}
	else
	{
		return nullptr;
	}
}

int main() {
	sf::View view;
	sf::RenderWindow window(sf::VideoMode({840,640}), "adad");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	window.display();
	while (window.isOpen()) {
		if (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}
		cout << "FAKJHD";
	}
}