//1m = 100units (pixels)

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "utils.hpp"
#include "basic2dp.hpp"
#include <string>
#include <thread>
#include <atomic>
#include <exception>
using namespace std;

atomic<bool> exit_requested = false;
atomic<bool> info_requested = false;

//Seperate thread for CLI
void INPUT(Basic2DP& b, sf::RectangleShape& border) {
	string str;
	Editor cli(b, border);
	vector<string> tokens;

	try {

		filesystem::path theme_dir = filesystem::current_path() / "Basic2DPThemes";
		filesystem::create_directories(theme_dir);
		cli.themeget_iterator(theme_dir);


		while (true) {
			std::cout << "\033[93m";
			std::cout << ">  ";
			std::getline(cin, str);
			tokens = cli.parse(str);
			std::cout << "\033[96m";

			if (tokens[0] == "exit" || tokens[0] == "e") {
				exit_requested = true;
				break;
			}
			else if (tokens[0] == "getinfo")
			{
				cli.getinfo();
			}
			else if (tokens[0] == "setgravity" && tokens.size() == 3) {
				sf::Vector2f g = { stof(tokens[1]), stof(tokens[2]) };
				b.gravity = g;
			}
			else if (tokens[0] == "applyforce" && tokens.size() >= 3) {
				tokens.resize(4);
				sf::Vector2f F = { stof(tokens[1]) , stof(tokens[2]) };
				b.apply_force(F, true, stob(tokens[3], "increment", "change"));
			}
			else if (tokens[0] == "updatevelocity" && tokens.size() >= 3) {
				tokens.resize(4);
				sf::Vector2f V = { stof(tokens[1]) , stof(tokens[2]) };
				b.apply_force(V, true, stob(tokens[3], "increment", "change"));
			}
			else if (tokens[0] == "addbody") {
				if (tokens.size() > 1 && tokens.size() == 4) {
					float radius = stof(tokens[1]);
					float pos_X = stof(tokens[2]);
					float pos_y = stof(tokens[3]);

					b.obj_list.push_back(make_objectbody(radius, { pos_X, pos_y }));
				}
				else
				{
					b.obj_list.push_back(make_objectbody(5.0, { 0.0, 0.0 }, sf::Color::White, 0.8));
				}
			}
			else if (tokens[0] == "theme") {
				if (tokens.size() == 2) {
					if (stoi(tokens[1]) <= cli.theme_list.size() && stoi(tokens[1]) > 0) {
						cli.set_theme(stoi(tokens[1]) - 1);
					}
					else { std::cout << "Invalid Index" << endl; }
				}
				else {
					for (int i = 0; i < cli.theme_list.size(); i++) {
						std::cout << i + 1 << ". " << cli.theme_list[i].name << endl;
					}
				}
			}
			else if (tokens[0] == "addtheme") {
				bool exists = false;
				string name, temp;
				sf::Vector3u bg, border, shape;
				vector<unsigned> clr;
				std::cout << "Name: ";
				std::cout << "\033[94m";
				std::getline(cin, name);
				for (Theme t : cli.theme_list) {
					if (t.name == name) {
						exists = true;
						std::cout << "Theme already exists" << endl;
						break;
					}
				}
				std::cout << "\033[96m";

				if (!exists) {
					std::cout << "Background Colour: ";
					std::cout << "\033[94m";
					std::getline(cin, temp);
					clr.push_back(stoi(cli.parse(temp)[0])); clr.push_back(stoi(cli.parse(temp)[1])); clr.push_back(stoi(cli.parse(temp)[2]));
					bg = { clr[0], clr[1], clr[2] };
					clr.clear();
					std::cout << "\033[96m";

					std::cout << "Border Colour: ";
					std::cout << "\033[94m";
					std::getline(cin, temp);
					clr.push_back(stoi(cli.parse(temp)[0])); clr.push_back(stoi(cli.parse(temp)[1])); clr.push_back(stoi(cli.parse(temp)[2]));
					border = { clr[0], clr[1], clr[2] };
					clr.clear();
					std::cout << "\033[96m";

					std::cout << "Shape Colour: ";
					std::cout << "\033[94m";
					std::getline(cin, temp);
					clr.push_back(stoi(cli.parse(temp)[0])); clr.push_back(stoi(cli.parse(temp)[1])); clr.push_back(stoi(cli.parse(temp)[2]));
					shape = { clr[0], clr[1], clr[2] };
					clr.clear();
					std::cout << "\033[96m";

					cli.add_theme(false, name, bg, border, shape);
				}
			}
			else
			{
				std::cout << "Invalid Input" << endl;
			}
		}
	}
	catch (exception& e) {
		std::cout << "In f{INPUT} -> " << e.what() << std::endl;
	}
}

int main() {
	try {
		sf::Clock clock;
		float dt = 0;

		sf::Vector2f gravity = { 0.0,0.0 };
		vector<objectbody> bodies_list;
		sf::RenderWindow window = windowmaker();

		sf::Color bg(15,18,30);
		sf::Color bord(60,70,100);
		sf::Color shp(100,150,255);

		Basic2DP basic2dp_manager(window, bodies_list, gravity, dt);

		sf::RectangleShape border({ 840,640 });
		border.setFillColor(bg);
		border.setOrigin(sf::Vector2f{ 420.0 ,320.0 });
		border.setOutlineThickness(-20);
		border.setOutlineColor(bord);


		for (int i = 0; i < 5; i++) {
			bodies_list.push_back(make_objectbody(5.0, { 200.0, -100.0 }, shp, 0.8));

		}

		basic2dp_manager.update_velocity({ -1200.0f, 600.0f }, false, false, &bodies_list[0]);
		basic2dp_manager.update_velocity({ 200.0f, -180.0f }, false, false, &bodies_list[1]);
		basic2dp_manager.update_velocity({ 147.0f, 150.0f }, false, false, &bodies_list[2]);
		basic2dp_manager.update_velocity({ 40.0f, 70.0f }, false, false, &bodies_list[3]);
		basic2dp_manager.update_velocity({ 9.0f, -110.0f }, false, false, &bodies_list[4]);

		thread input_processor(INPUT, ref(basic2dp_manager), ref(border));	//Thread started here

		while (window.isOpen()) {
			if (exit_requested) {
				window.close();
				break;
			}

			window.clear();
			dt = (float)clock.restart().asMilliseconds() / 1000.0;
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) { window.close(); }
			}


			if (bodies_list.size() > 0) { basic2dp_manager.process_shape_collision(); }
			basic2dp_manager.process_movement();
			window.draw(border);
			basic2dp_manager.process_wall_collision();
			basic2dp_manager.draw_bodies();
			window.display();
		}

		input_processor.join();
	}
	catch (exception& e) {
		cout << "Err in main() -> " << e.what() << endl;
	}

}