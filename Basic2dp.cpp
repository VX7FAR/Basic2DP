#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include "basic2dp.hpp"
#include "utils.hpp"

void Basic2DP::draw_bodies() {
	for (objectbody& body : obj_list) {
		window.draw(*body.body_shape);
	}
}

void Basic2DP::velocity_updater(float x_velo, float y_velo, bool forall = true, bool increment = false, objectbody* body = nullptr) {
	objectbody*& body_Ref = body;
	if (forall) {
		if (increment) {
			for (objectbody& body : obj_list) {
				body.x_velocity += x_velo;
				body.y_velocity += y_velo;
			}
		}
		else
		{
			for (objectbody& body : obj_list) {
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

void Basic2DP::process_movement(float delta_T) {
	for (objectbody& body : obj_list) {
		body.x_position += body.x_velocity * delta_T;
		body.y_position += body.y_velocity * delta_T;
		body.body_shape->setPosition({ body.x_position, body.y_position });
	}
}

void Basic2DP::process_wall_collision() {
	float screen_x = (window.getSize().x / 2.0) - 20.0;
	float screen_y = (window.getSize().y / 2.0) - 20.0;
	for (objectbody& body : obj_list) {
		float x_pos = body.x_position;
		float y_pos = body.y_position;
		if ((screen_x - body.x_position < body.radius || screen_x - body.x_position > 780.0) && !hitx) {
			body.x_velocity = -body.x_velocity;
			hitx = true;
			std::cout << "Hit x" << std::endl;
		}
		else if (!(screen_x - body.x_position < body.radius || screen_x - body.x_position > 780.0))
		{
			hitx = false;
		}
		if ((screen_y - body.y_position < body.radius || screen_y - body.y_position > 580.0) && !hity) {
			body.y_velocity = -body.y_velocity;
			hitx = true;
			std::cout << "Hit x" << std::endl;
		}
		else if (!(screen_y - body.y_position < body.radius || screen_y - body.y_position > 580.0))
		{
			hity = false;
		}
	}
}