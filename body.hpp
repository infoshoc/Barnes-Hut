#pragma once

#include "point.hpp"

typedef double mass_t;
typedef point_t force_t;
typedef point_t speed_t;
typedef point_t acceleration_t;
typedef double duration_t;

const coord_t EPS = 1e-9;
const double GRAVITATIONAL_CONSTANT = 1;//6.6738467e-11;

struct body_t : public point_t{
    mass_t mass;
	//short red, green, blue;
};
inline bool operator != (const body_t &a, const body_t &b ){
    return fabs(a.x-b.x) > EPS || fabs(a.y-b.y) > EPS  || fabs(a.mass-b.mass) > EPS;
}

inline force_t get_force ( const body_t &a, const body_t &b ){
    point_t direction = b-a;
    return GRAVITATIONAL_CONSTANT * a.mass * b.mass / direction.length2() / direction.length() * direction;
}

void move_body( body_t &body, speed_t &speed, const point_t &force, duration_t time ){
    acceleration_t acceleration = force / body.mass;
	speed += time * acceleration;
	body += time * speed;
}
