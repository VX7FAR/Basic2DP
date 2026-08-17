//1m = 100units (pixels)

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;

enum shapetype
{
	circle, rectange
};

class ShapeManager{
public:
	sf::Shape* createshape(shapetype type, sf::Vector2f size, sf::Vector2f position = sf::Vector2f{ 0.0,0.0 }, sf::Color colour = sf::Color::Blue, float outlinethickness = 0.0, sf::Color outlinecolor = sf::Color::White) {
		if (type == circle) {
			sf::CircleShape circle(size.x);
			circle.setOrigin(sf::Vector2f{ size.x / 2, size.x/2 });
			circle.setFillColor(colour);
			circle.setOutlineThickness(outlinethickness);
			circle.setOutlineColor(outlinecolor);
			circle.setPosition(position);
			return new sf::CircleShape(circle);
		}
		else if (type == rectange) {
			sf::RectangleShape rect(sf::Vector2f{ size.x, size.y });
			rect.setFillColor(colour);
			rect.setOutlineThickness(outlinethickness);
			rect.setOutlineColor(outlinecolor);
			rect.setOrigin(sf::Vector2f{ size.x / 2, size.y/2 });
			rect.setPosition(position);
			return new sf::RectangleShape(rect);
		}
		else {
			return nullptr;
		}
	}
};


int main()
{
	ShapeManager shapemanager;

	float dt = 1 / 60;
	float velocity = 1;
	float thickness = 20.0;
	unsigned int video_X = 800 + (2 * thickness);
	unsigned int video_Y = 600 + (2 * thickness);
	
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u{video_X,video_Y}), "ad");
	window.setMaximumSize(sf::Vector2u{ 800,600 });
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape border(sf::Vector2f(video_X, video_Y));
	border.setFillColor(sf::Color::Black);
	border.setOutlineThickness(-thickness);
	border.setOutlineColor(sf::Color::Cyan);

	sf::CircleShape circle(100.0);
	circle.setFillColor(sf::Color::Green);

	float yscale;
	sf::Shape* rect = shapemanager.createshape(rectange, sf::Vector2f{ 80, 60 }, sf::Vector2f{ 420,320 }, sf::Color::Magenta);


	while (window.isOpen()) {
		window.clear(sf::Color::Black);
		window.draw(border);
		while (const optional event = window.pollEvent()) {
			if (event->is < sf::Event::Closed>()) { window.close(); }
		}

		window.draw(*rect);
		window.display();
	}
}