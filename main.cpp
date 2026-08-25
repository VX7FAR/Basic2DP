//1m = 100units (pixels)
/*
Assumptions made:
1. There is no air drag and friction among the bodies and border
*/
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;


struct objectbody {
	sf::Shape* body_shape;
	float radius;
	float mass;

	float x_velocity;
	float y_velocity;

	float x_position;
	float y_position;
};

struct normals {
	float x;
	float y;
};

vector<objectbody> bodies;

class Basic2DP {
	sf::RenderWindow& window;
	bool hitx = false;;
	bool hity = false;;
public:
	Basic2DP(sf::RenderWindow& main_window) : window(main_window) {
	}

	void drawbodies() {
		for (objectbody &body : bodies) {
			window.draw(*body.body_shape);
		}
	}

	void velocity_updater(float x_velo, float y_velo, bool forall = true, bool increment = false, objectbody* body = nullptr) {
		objectbody*& body_Ref = body;
		if (forall) {
			if (increment) {
				for (objectbody& body : bodies) {
					body.x_velocity += x_velo;
					body.y_velocity += y_velo;
				}
			}
			else
			{
				for (objectbody& body : bodies) {
					body.x_velocity = x_velo;
					body.y_velocity = y_velo;
				}
			}
		}
		else
		{
			if (increment) {
				body_Ref->x_velocity += x_velo;
				body_Ref->y_velocity += y_velo;
			}
			else
			{
				body_Ref->x_velocity = x_velo;
				body_Ref->y_velocity = y_velo;
			}
		}
	}


	void process_movement(float delta_t) {
		for (objectbody &body : bodies) {
			body.x_position += body.x_velocity * delta_t;
			body.y_position += body.y_velocity * delta_t;
			body.body_shape->setPosition({ body.x_position, body.y_position });
		}
	}

	void process_collision() {
		for (objectbody &body : bodies) {
			float x = body.x_position;
			float y = body.y_position;
			if (((window.getSize().x / 2.0) - 20.0 - abs(x)) < body.radius && !hitx) { 
				body.x_velocity = -body.x_velocity;
				cout << "hit x" << endl;
				hitx = true;
			}
			else if(((window.getSize().x / 2.0) - 20.0 - abs(x)) > body.radius && hitx)
			{
				hitx = false;
			}
			if (((window.getSize().y / 2.0) - 20.0 - abs(y)) < body.radius && !hity) {
				body.y_velocity = -body.y_velocity;
				cout << "hit y" << endl;
				hity = true;
			}
			else if(((window.getSize().y / 2.0) - 20.0 - abs(y)) > body.radius && hity)
			{
				hity = false;
			}
		}
	}
};

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

int main() {

	sf::RenderWindow window = windowmaker();

	bodies.push_back(make_objectbody(20.0, {0.0,0.0}, sf::Color::Yellow));

	Basic2DP manager(window);
	sf::Clock clock;
	float dt;
	dt = 1.0 / 60.0;

	sf::RectangleShape border({ 840,640 });
	border.setFillColor(sf::Color::Transparent);
	border.setOrigin(sf::Vector2f{ 420.0,320.0 });
	border.setOutlineThickness(-20);
	border.setOutlineColor(sf::Color::Red);

	manager.velocity_updater(-500.0, -50.0);

	while (window.isOpen()) {
		window.clear();
		dt = (float)clock.restart().asMilliseconds() / 1000.0;
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		manager.process_collision();
		manager.process_movement(dt);
		manager.drawbodies();
		window.draw(border);
		window.display();
	}
}