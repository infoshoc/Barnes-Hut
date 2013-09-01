#include "point.hpp"

typedef double mass_t;
typedef double force_t;
typedef point_t speed_t;
typedef point_t acceleration_t;
typedef double time_t;

const time_t MOVEMENT_TIME = 42.0;
const coord_t EPS = 1e-9;
const force_t GRAVITATIONAL_CONSTANT = 6.67384e-11;

struct body_t : public point_t{
    mass_t mass;
};
inline bool operator != (const body_t &a, const body_t &b ){
    return fabs(a.x-b.x) > EPS || fabs(a.y-b.y) > EPS  || fabs(a.mass-b.mass) > EPS;
}

inline point_t get_force ( const body_t &a, const body_t &b ){
    point_t direction = b-a;
    return GRAVITATIONAL_CONSTANT * a.mass * b.mass / direction.length2() / direction.length() * direction;
}

void move_body( body_t &body, speed_t &speed, const point_t &force, const time_t time = MOVEMENT_TIME ){
    acceleration_t acceleration = force / body.mass;
    body += time * ( speed + time / 2.0 * acceleration );
    speed += time * acceleration;
}