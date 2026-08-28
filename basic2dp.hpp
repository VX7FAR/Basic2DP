#pragma once
#include<SFML/graphics.hpp>
#include<vector>
#include "utils.hpp"

class Basic2DP{
	sf::RenderWindow& window;
	std::vector<objectbody>& obj_list;
	bool hitx = false;
	bool hity = false;
public:
	Basic2DP(sf::RenderWindow& main_window, std::vector<objectbody>& lst) : window(main_window), obj_list(lst) {}

	void draw_bodies();

	void velocity_updater(sf::Vector2f velocity, bool forall = true, bool increment = false, objectbody* body = nullptr);

	void process_movement(float delta_T);

	void process_wall_collision();

	void process_shape_collision();
};