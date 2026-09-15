#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include "basic2dp.hpp"
#include "utils.hpp"
#include <filesystem>
#include <fstream>
#include <exception>

void Basic2DP::draw_bodies() {
	for (objectbody& body : obj_list) {
		window.draw(*body.body_shape);
	}
}

sf::Vector2f Basic2DP::predict_movement(const objectbody& body) {
	sf::Vector2f p_pos = { 0.0,0.0 };
	p_pos.x = body.current_position.x + (body.velocity.x * delta_T);
	p_pos.y = body.current_position.y + (body.velocity.y * delta_T);
	return p_pos;
}

void Basic2DP::process_wall_collision() {
	for (objectbody& body : obj_list) {
		sf::Vector2f predicted_pos;
		sf::Vector2f minimum = { -400.0,-300.0 };
		sf::Vector2f maximum = { 400.0,300.0 };
		sf::Vector2u hit;
		predicted_pos = predict_movement(body);
		hit = { body.hitx, body.hity };
		float penetration = 0.0;

		if (!body.hitx) {
			if (predicted_pos.x < minimum.x + body.radius) {	//LEFT WALL
				penetration = minimum.x - predicted_pos.x;
				body.predicted_position.x = predicted_pos.x + penetration + body.radius;
				body.hitx = true;
			}
			else if (predicted_pos.x > maximum.x - body.radius) {	//RIGHT WALL
				penetration = predicted_pos.x - maximum.x;
				body.predicted_position.x = predicted_pos.x - penetration - body.radius;
				body.hitx = true;
			}
		}
		else
		{
			body.velocity.x *= -1 * body.e;
			body.hitx = false;
		}
		if (!body.hity) {
			if (predicted_pos.y < minimum.y + body.radius) {//BOTTOM WALL
				penetration = minimum.y - predicted_pos.y;
				body.predicted_position.y = predicted_pos.y + penetration + body.radius;
				body.hity = true;
			}
			else if (predicted_pos.y > maximum.y - body.radius) {	//TOP WALL
				penetration = predicted_pos.y - maximum.y;
				body.predicted_position.y = predicted_pos.y - penetration - body.radius;
				body.hity = true;
			}
		}
		else
		{
			body.velocity.y *= -1 * body.e;
			body.hity = false;
		}
	}
}

void Basic2DP::process_shape_collision() {
	if (obj_list.size() > 0) {
		sf::Vector2f relative_Velocity;

		vector_scalar_pair distance;
		float velocity_component;
		sf::Vector2f collision_normal;

		float impulse;

		for (int i = 0; i < obj_list.size(); i++) {
			objectbody& a = obj_list[i];

			for (int j = i + 1; j < obj_list.size(); j++) {
				objectbody& b = obj_list[j];
				distance = find_distance(a.body_shape, b.body_shape);
				relative_Velocity = { b.velocity.x - a.velocity.x, b.velocity.y - a.velocity.y };
				collision_normal = { distance.distance_vector.x / distance.scalar, distance.distance_vector.y / distance.scalar };

				if (a.radius + b.radius > distance.scalar && dotproduct(relative_Velocity, collision_normal) > 0) {
					velocity_component = (a.e + b.e) * dotproduct(relative_Velocity, collision_normal);
					impulse = velocity_component / ((1 / a.mass) + (1 / b.mass));

					a.velocity = a.velocity + (impulse * collision_normal) / a.mass;
					b.velocity = b.velocity - (impulse * collision_normal) / b.mass;
				}

			}
		}
	}
}

void Basic2DP::update_velocity(sf::Vector2f velocity, bool forall, bool increment, objectbody* body) {
	objectbody*& body_Ref = body;
	if (increment) {
		if (forall) {
			for (objectbody& body : obj_list) {
				body.velocity += {velocity.x / body.mass, velocity.y / body.mass};
			}
		}
		else
		{
			body_Ref->velocity += {velocity.x / body->mass, velocity.y / body->mass};
		}
	}
	else
	{
		if (forall) {
			for (objectbody& body : obj_list) {
				body.velocity = { velocity.x / body.mass, velocity.y / body.mass };
			}
		}
		else
		{
			body_Ref->velocity = { velocity.x / body_Ref->mass, velocity.y / body_Ref->mass };
		}
	}
}

void Basic2DP::apply_force(sf::Vector2f force, bool forall, bool increment, objectbody* body) {
	objectbody*& body_Ref = body;
	if (increment) {
		if (forall) {
			for (objectbody& body : obj_list) {
				body.velocity += {force.x / body.mass, force.y / body.mass};
			}
		}
		else
		{
			body_Ref->velocity += {force.x / body->mass, force.y / body->mass};
		}
	}
	else
	{
		if (forall) {
			for (objectbody& body : obj_list) {
				body.velocity = { force.x / body.mass, force.y / body.mass };
			}
		}
		else
		{
			body_Ref->velocity = { force.x / body_Ref->mass, force.y / body_Ref->mass };
		}
	}
}

void Basic2DP::process_movement() {
	for (objectbody& body : obj_list) {
		if (body.hitx) {
			body.current_position.x = body.predicted_position.x;
			body.displace = false;
		}
		if (body.hity) {
			body.current_position.y = body.predicted_position.y;
			body.displace = false;
		}
		if(body.displace)
		{
			body.velocity += gravity * delta_T;
			body.current_position += body.velocity * delta_T;
		}
		body.body_shape->setPosition(body.current_position);
		body.displace = true;
	}
}

std::vector<std::string> Editor::parse(std::string str) {
	std::vector<std::string> tokens;
	std::string token;
	size_t index = 0;
	std::stringstream ss(str);

	while (std::getline(ss, token, ' ')) {
		tokens.push_back(token);
	}

	return tokens;
}

void Editor::getinfo() {
	std::cout << "Display Size: " << "\033[92m" << basic.window.getSize().x << "x" << basic.window.getSize().y << "\033[96m" << std::endl;
	std::cout << "Framerate: " << "\033[92m" << 1 / basic.delta_T << "\033[96m" << std::endl;
	std::cout << "g: " << "\033[92m" << "[" << basic.gravity.x << ", " << basic.gravity.y << "]" << "\033[96m" << std::endl;
	std::cout << "Number of bodies: " << "\033[92m" << basic.obj_list.size() << "\033[96m" << std::endl;
	std::cout << "Theme Folder: " << "\033[92m" << thm.string() << "\033[96m" << std::endl;
	std::cout << "No. of Themes: " << "\033[92m" << theme_list.size() << "\033[96m" << std::endl;
}

void Editor::set_theme(size_t set_to) {
	if (set_to < theme_list.size()) {
		current_theme = theme_list[set_to];
		border.setFillColor(current_theme.background);
		border.setOutlineColor(current_theme.border);
		for (objectbody obj : basic.obj_list) {
			obj.body_shape->setFillColor(current_theme.shape_clr);
		}
	}
}

void Editor::add_theme(bool readonly, std::string name, sf::Vector3u bg, sf::Vector3u border, sf::Vector3u shape) {
	try {
		bool exists = false;
		sf::Color defaultclr(255, 255, 255);
		for (Theme t : theme_list) {
			if (t.name == name) exists = true;
		}
		if (exists) {
			std::cout << "Theme already exists" << std::endl;
		}
		else
		{
			Theme newtheme;
			newtheme.name = name;
			correct_colour(bg);
			sf::Color back(bg.x, bg.y, bg.z);
			newtheme.background = back;
			correct_colour(border);
			sf::Color bord(border.x, border.y, border.z);
			newtheme.border = bord;
			correct_colour(shape);
			sf::Color shp(shape.x, shape.y, shape.z);
			newtheme.shape_clr = shp;

			theme_list.push_back(newtheme);

			if (!readonly) {
				std::fstream write;
				write.open(thm.string() + "\\" + name + ".thm", std::ios::out);

				write << bg.x << " " << bg.y << " " << bg.z << " ";
				write << border.x << " " << border.y << " " << border.z << " ";
				write << shape.x << " " << shape.y << " " << shape.z << " ";
			}
		}
	}
	catch (std::exception& e) {
		std::cout << "Editor::add_theme -> " << e.what() << std::endl;
	}
}

void Editor::themeget_iterator(std::filesystem::path dir) {
	try {
		thm = dir;
		for (const auto& file : std::filesystem::directory_iterator(dir)) {
			if (file.path().extension() == ".thm") {
				std::string s;
				std::fstream themefile;

				std::vector<unsigned> clr;
				themefile.open(file.path());
				if (themefile.is_open()) {
					std::string filename = filename_to_name(file.path().filename().string());
					std::getline(themefile, s);
					std::vector<std::string> code = parse(s);
					sf::Vector3u bg, border, shape;

					clr.push_back(stoi(code[0])); clr.push_back(stoi(code[1])); clr.push_back(stoi(code[2]));
					bg = { clr[0], clr[1], clr[2] };
					clr.clear();
					clr.push_back(stoi(code[3])); clr.push_back(stoi(code[4])); clr.push_back(stoi(code[5]));
					border = { clr[0], clr[1], clr[2] };
					clr.clear();
					clr.push_back(stoi(code[6])); clr.push_back(stoi(code[7])); clr.push_back(stoi(code[8]));
					shape = { clr[0], clr[1], clr[2] };
					clr.clear();
					add_theme(true, filename, bg, border, shape);
				}
			}
		}
	}
	catch (std::exception& e) {
		std::cout << "Editor::themeget_iterator -> " << e.what() << std::endl;
	}
}