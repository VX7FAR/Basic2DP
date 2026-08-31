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
	int pause;
	//cin >> pause;

	sf::Vector2f min;
	sf::Vector2f max;

	vector<objectbody> bodies_list;
	sf::RenderWindow window = windowmaker();
	Basic2DP basic2dp_manager(window, bodies_list, min, max);

	sf::Clock clock;
	float dt;
	dt = 1.0 / 60.0;

	sf::RectangleShape border({ 840,640 });
	border.setFillColor(sf::Color::Transparent);
	border.setOrigin(sf::Vector2f{ 420.0 ,320.0});
	border.setOutlineThickness(-20);
	border.setOutlineColor(sf::Color::Red);

	bodies_list.push_back(make_objectbody(20.0, { -247.0,  136.0 }, sf::Color::Magenta));
	bodies_list.push_back(make_objectbody(20.0, { 183.0, -192.0 }, sf::Color::Green));
	bodies_list.push_back(make_objectbody(20.0, { 42.0,  231.0 }, sf::Color::Cyan));
	bodies_list.push_back(make_objectbody(20.0, { -116.0, -104.0 }, sf::Color::Yellow));
	bodies_list.push_back(make_objectbody(20.0, { 294.0,   57.0 }, sf::Color::Blue));
	bodies_list.push_back(make_objectbody(20.0, { -331.0, -215.0 }, sf::Color::Red));
	basic2dp_manager.velocity_updater({ 73.0f, -41.0f }, false, false, &bodies_list[0]);
	basic2dp_manager.velocity_updater({ -28.0f, 86.0f }, true, true, &bodies_list[1]);
	basic2dp_manager.velocity_updater({ 52.0f, 19.0f }, false, true, &bodies_list[2]);
	basic2dp_manager.velocity_updater({ -91.0f, -34.0f }, true, false, &bodies_list[3]);
	basic2dp_manager.velocity_updater({ 17.0f, 68.0f }, false, false, &bodies_list[4]);
	basic2dp_manager.velocity_updater({ -64.0f, 27.0f }, true, true, &bodies_list[5]);
	
	while (window.isOpen()) {
		window.clear();
		dt = (float)clock.restart().asMilliseconds() / 1000.0;
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { window.close(); }
		}

		basic2dp_manager.process_wall_collision();
		if (bodies_list.size() > 0) {
			basic2dp_manager.process_shape_collision();
		}
		basic2dp_manager.process_movement(dt);
		basic2dp_manager.draw_bodies();
		window.draw(border);
		window.display();
		cout << bodies_list[0].velocity.x << ", " << bodies_list[0].velocity.y << " | " << bodies_list[1].velocity.x << ", " << bodies_list[1].velocity.y << endl;
	}
}