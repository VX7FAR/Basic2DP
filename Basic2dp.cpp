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

void Editor::process_String(std::string str) {

}