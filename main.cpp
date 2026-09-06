//1m = 100units (pixels)
/*
acceleration due to gravity, g = 980.665 cm/s^2
*/
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<math.h>
#include "utils.hpp"
#include "basic2dp.hpp"
using namespace std;


int main() {
	int pause;
	//cin >> pause;

	sf::Clock clock;
	float dt = 0;

	sf::Vector2f gravity = { 0.0,-980.0};
	vector<objectbody> bodies_list;
	sf::RenderWindow window = windowmaker();
	Basic2DP basic2dp_manager(window, bodies_list, gravity, dt);


	sf::RectangleShape border({ 840,640 });
	border.setFillColor(sf::Color::Transparent);
	border.setOrigin(sf::Vector2f{ 420.0 ,320.0});
	border.setOutlineThickness(-20);
	border.setOutlineColor(sf::Color::Red);


	bodies_list.push_back(make_objectbody(20.0, { 200.0, -100.0 }, sf::Color::Blue, 0.8));
	bodies_list.push_back(make_objectbody(40.0, { 0.0, 0.0 }, sf::Color::White, 0.5,10.0));
	bodies_list.push_back(make_objectbody(20.0, { 0.0, 0.0 }, sf::Color::Red, 0.7));
	bodies_list.push_back(make_objectbody(20.0, { 0.0, 0.0 }, sf::Color::Red, 0.64));
	bodies_list.push_back(make_objectbody(20.0, { 0.0, 0.0 }, sf::Color::Red, 0.8));
	basic2dp_manager.update_velocity({ -1200.0f, 600.0f }, false, false, &bodies_list[0]);
	basic2dp_manager.update_velocity({ 200.0f, -180.0f }, false, false, &bodies_list[1]);
	basic2dp_manager.update_velocity({ 147.0f, 150.0f }, false, false, &bodies_list[2]);
	basic2dp_manager.update_velocity({ 40.0f, 70.0f }, false, false, &bodies_list[3]);
	basic2dp_manager.update_velocity({ 9.0f, -110.0f }, false, false, &bodies_list[4]);
					 
	while (window.isOpen()) {
		window.clear();
		dt = (float)clock.restart().asMilliseconds() / 1000.0;
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		if (bodies_list.size() > 0) {basic2dp_manager.process_shape_collision(); }
		basic2dp_manager.process_movement();
		window.draw(border);
		basic2dp_manager.process_wall_collision();
		basic2dp_manager.draw_bodies();
		window.display();
	}
}