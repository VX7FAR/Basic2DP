//1m = 100units (pixels)
/*
Assumptions made:
1. There is no air drag and friction among the bodies and border
*/
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<math.h>
#include "utils.hpp"
#include "basic2dp.hpp"
using namespace std;


int main() {
	vector<objectbody> bodies_list;
	sf::RenderWindow window = windowmaker();
	Basic2DP basic2dp_manager(window, bodies_list);

	sf::Clock clock;
	float dt;
	dt = 1.0 / 60.0;

	sf::RectangleShape border({ 840,640 });
	border.setFillColor(sf::Color::Transparent);
	border.setOrigin(sf::Vector2f{ 420.0 ,320.0});
	border.setOutlineThickness(-20);
	border.setOutlineColor(sf::Color::Red);

	bodies_list.push_back(make_objectbody(20.0, { 0.0,0.0 }, sf::Color::Magenta));
	basic2dp_manager.velocity_updater({ 100.0, 100.0 });
	
	while (window.isOpen()) {
		window.clear();
		dt = (float)clock.restart().asMilliseconds() / 1000.0;
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		basic2dp_manager.process_wall_collision();
		basic2dp_manager.process_movement(dt);
		basic2dp_manager.draw_bodies();
		window.draw(border);
		window.display();
	}
}