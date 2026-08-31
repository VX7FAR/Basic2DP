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

void Basic2DP::velocity_updater(sf::Vector2f force, bool forall, bool increment, objectbody* body) {
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
				body.velocity = {force.x / body.mass, force.y / body.mass};
			}
		}
		else
		{
			body_Ref->velocity = { force.x / body_Ref->mass, force.y / body_Ref->mass };
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
	bool hitx = false;
	bool hity = false;
	float screen_x = (window.getSize().x / 2.0) - 20.0;
	float screen_y = (window.getSize().y / 2.0) - 20.0;
	for (objectbody& body : obj_list) {
		hitx = false;
		hity = false;
		float x_pos = body.position.x;
		float y_pos = body.position.y;
		if ((screen_x - body.position.x < body.radius || screen_x - body.position.x > 780.0) && !hitx) {
			body.velocity.x = -body.velocity.x;
			hitx = true;
		}
		else if (!(screen_x - body.position.x < body.radius || screen_x - body.position.x > 780.0))
		{
			hitx = false;
		}
		if ((screen_y - body.position.y < body.radius || screen_y - body.position.y > 580.0) && !hity) {
			body.velocity.y = -body.velocity.y;
			hitx = true;
		}
		else if (!(screen_y - body.position.y < body.radius || screen_y - body.position.y > 580.0))
		{
			hity = false;
		}
	}
}

void Basic2DP::process_shape_collision() {
	sf::Vector2f relative_Velocity;

	vector_scalar_pair distance;
	float velocity_component;
	sf::Vector2f collision_normal;

	float impulse;

	for (int i = 0; i < obj_list.size(); i++) {
		objectbody &a = obj_list[i];
		
		for (int j = i + 1; j < obj_list.size(); j++) {
			objectbody& b = obj_list[j];
			distance = find_distance(a.body_shape, b.body_shape);
			relative_Velocity = {b.velocity.x - a.velocity.x, b.velocity.y - a.velocity.y};
			collision_normal = { distance.distance_vector.x / distance.scalar, distance.distance_vector.y / distance.scalar };

			if (a.radius + b.radius > distance.scalar && dotproduct(relative_Velocity,collision_normal) > 0) {
				std::cout << "hit" << std::endl;
				velocity_component = (a.e + b.e) * dotproduct(relative_Velocity, collision_normal);
				impulse = velocity_component / ((1 / a.mass) + (1 / b.mass));

				a.velocity = a.velocity + (impulse * collision_normal)/a.mass;
				b.velocity = b.velocity - (impulse * collision_normal)/b.mass;
				
				/*std::cout << "Mass: " << a.mass << " | " << b.mass;
				std::cout << "Mass: " << a.mass << " | " << b.mass;
				std::cout << "Mass: " << a.mass << " | " << b.mass;
				std::cout << "Mass: " << a.mass << " | " << b.mass;*/
			}

		}
	}
}