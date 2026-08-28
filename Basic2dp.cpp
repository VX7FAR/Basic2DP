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

void Basic2DP::velocity_updater(sf::Vector2f velocity, bool forall, bool increment, objectbody* body) {
	objectbody*& body_Ref = body;
	if (forall) {
		if (increment) {
			for (objectbody& body : obj_list) {
				body.velocity.x += (float)velocity.x;
				body.velocity.y += (float)velocity.y;
			}
		}
		else
		{
			for (objectbody& body : obj_list) {
				body.velocity.x = (float)velocity.x;
				body.velocity.y = (float)velocity.y;
			}
		}
	}
	else
	{
		if (increment) {
			body_Ref->velocity.x += (float)velocity.x;
			body_Ref->velocity.y += (float)velocity.y;
		}
		else
		{
			body_Ref->velocity.x = (float)velocity.x;
			body_Ref->velocity.y = (float)velocity.y;
		}
	}
}

void Basic2DP::process_movement(float delta_T) {
	for (objectbody& body : obj_list) {
		body.position.x += body.velocity.x * delta_T;
		body.position.y += body.velocity.y * delta_T;
		body.body_shape->setPosition({ body.position.x, body.position.y });
	}
}

void Basic2DP::process_wall_collision() {
	float screen_x = (window.getSize().x / 2.0) - 20.0;
	float screen_y = (window.getSize().y / 2.0) - 20.0;
	for (objectbody& body : obj_list) {
		float x_pos = body.position.x;
		float y_pos = body.position.y;
		if ((screen_x - body.position.x < body.radius || screen_x - body.position.x > 780.0) && !hitx) {
			body.velocity.x = -body.velocity.x;
			hitx = true;
			std::cout << "Hit x" << std::endl;
		}
		else if (!(screen_x - body.position.x < body.radius || screen_x - body.position.x > 780.0))
		{
			hitx = false;
		}
		if ((screen_y - body.position.y < body.radius || screen_y - body.position.y > 580.0) && !hity) {
			body.velocity.y = -body.velocity.y;
			hitx = true;
			std::cout << "Hit x" << std::endl;
		}
		else if (!(screen_y - body.position.y < body.radius || screen_y - body.position.y > 580.0))
		{
			hity = false;
		}
	}
}

void Basic2DP::process_shape_collision() {
	for (int i = 0; i < obj_list.size(); i++) {
		for (int j = 0; j < obj_list.size(); j++) {
			float collisionx = 0.0;
			float collisiony = 0.0;
			
			vector_scalar_pair distancepair = find_distance(obj_list[i].body_shape, obj_list[j].body_shape);
			if (distancepair.scalar < obj_list[i].radius + obj_list[j].radius) {
				collisionx = distancepair.distance_vector.x / distancepair.scalar;
				collisiony = distancepair.distance_vector.y / distancepair.scalar;
			}
		}
	}
}