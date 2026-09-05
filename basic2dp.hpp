#pragma once
#include<SFML/graphics.hpp>
#include<vector>
#include "utils.hpp"

class Basic2DP{
	sf::RenderWindow& window;
	std::vector<objectbody>& obj_list;
public:
	sf::Vector2f gravity;
	float& delta_T;

	Basic2DP(sf::RenderWindow& main_window, std::vector<objectbody>& lst, sf::Vector2f g, float &dt) : window(main_window), obj_list(lst), gravity(g), delta_T(dt) {}

	void draw_bodies();

	void process_wall_collision();

	void process_shape_collision();

	void update_velocity(sf::Vector2f velocity, bool forall = true, bool increment = false, objectbody* body = nullptr);

	void apply_force(sf::Vector2f force, bool forall = true, bool increment = false, objectbody* body = nullptr);

	sf::Vector2f predict_movement(const objectbody &body);

	void wall_collision_corrector(objectbody &body, sf::Vector2f predicted_pos);

	void process_movement();
};