//1m = 100units (pixels)
/*
Assumptions made:
1. There is no air drag and friction among the bodies and border
*/
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<map>
using namespace std;


struct objectbody {
	sf::Shape* body_shape;
	float radius;
	float weight;

	float x_velocity;
	float y_velocity;
	float x_position;
	float y_position;
};

vector<objectbody> bodies;

class Basic2DP {
	sf::RenderWindow& window;
public:
	Basic2DP(sf::RenderWindow& main_window) : window(main_window) {
	}

	void drawbodies() {
		for (objectbody &body : bodies) {
				window.draw(*body.body_shape);
		}
	}

	void process_movement(float delta_t) {
		for (objectbody &body : bodies) {
			
		}
	}
};

objectbody make_objectbody(float radius, sf::Vector2f position = { 0.0,0.0 }, sf::Color clr = sf::Color::Red, float weight = 1) {
	sf::CircleShape circle(radius);
	circle.setPosition(position);
	circle.setOrigin({ radius, radius });
	circle.setFillColor(clr);
	objectbody obj;
	obj.body_shape = new sf::CircleShape(circle);
	obj.radius = radius;
	obj.weight = weight;
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

int main() {

	sf::RenderWindow window = windowmaker();
	
	bodies.push_back(make_objectbody(20.0, {100.0,300.0} , sf::Color::Green));
	bodies.push_back(make_objectbody(20.0, {-200.0,-200.0}, sf::Color::Blue));
	bodies.push_back(make_objectbody(20.0, {0.0,0.0}, sf::Color::Yellow));

	Basic2DP manager(window);
	sf::Clock clock;
	sf::Time dt;

	sf::RectangleShape border({ 840,640 });
	border.setFillColor(sf::Color::Transparent);
	border.setOrigin(sf::Vector2f{ 420.0,320.0 });
	border.setOutlineThickness(-20);
	border.setOutlineColor(sf::Color::Red);

	while (window.isOpen()) {
		cout << clock.reset().asMicroseconds() << '/n';
		window.clear();
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		manager.drawbodies();
		window.draw(border);
		window.display();

	}
}