#pragma once
#include <SFML/graphics.hpp>
#include <vector>
#include "utils.hpp"
#include <string>	
#include <filesystem>

//Manages main processing task related to collision, physics and graphics
class Basic2DP{
public:
	sf::RenderWindow& window;
	std::vector<objectbody>& obj_list;
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

//Manages input from terminal
class Editor {
public:
	std::vector<Theme> theme_list;
	Theme current_theme;
	Basic2DP& basic;
	sf::RectangleShape& border;
	std::filesystem::path thm;	//Stores folder location of themes

	Editor(Basic2DP& bdp, sf::RectangleShape& rec) : basic(bdp), border(rec){}

	std::vector<std::string> parse(std::string str);

	void set_theme(size_t set_to);

	void add_theme(bool init, std::string name, sf::Vector3u bg, sf::Vector3u border, sf::Vector3u shape = {260,260,260});

	void getinfo();
	//Fetches themes from folder at beginning of code
	void themeget_iterator(std::filesystem::path dir);
};