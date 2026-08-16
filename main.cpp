#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Basic2DP");
	window.setMaximumSize(sf::Vector2u{ 800,600 });
	window.setVerticalSyncEnabled(true);	

	float thickness = 20.0;
	sf::RectangleShape border(sf::Vector2f(800.0,600.0));
	border.setFillColor(sf::Color::Black);
	border.setOutlineThickness(-thickness);
	border.setOutlineColor(sf::Color::Cyan);

	sf::CircleShape circle(100.0);
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(sf::Vector2f(200.0, 200.0));

	sf::RectangleShape rect(sf::Vector2f(100, 150));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(sf::Vector2f(0, 0));

	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is < sf::Event::Closed>()) { window.close(); }
		}

		window.clear(sf::Color::Black);
		window.draw(border);
		window.draw(circle);
		window.display();
	}
}