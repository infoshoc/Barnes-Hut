#include <cmath>

typedef double coord_t;
typedef double mass_t;
typedef double force_t;
typedef double time_t;

const void *NULLPTR = (void*)0;

const int MAX_BODIES_NUMBER = 42;
const int CHILDREN_NUMBER = 4;
const int BORDERS_NUMBER = 3;
const coord_t THETA = 0.5;
const coord_t EPS = 1e-9;
const force_t GRAVITATIONAL_CONSTANT = 6.67384e-11;
const time_t MOVEMENT_TIME = 42.0;

struct point_t;
typedef point_t speed_t;
typedef point_t acceleration_t;
struct body_t;
struct node_t;

void add_body(node_t*, const body_t*, const point_t, const point_t);
void push_to_children(node_t*, const body_t*, const point_t&, const point_t&);

int main(){

    FILE *fh = fopen (  );

    return 0;
}

struct point_t{
    coord_t x, y;
    double length()const;
    double length2()const;
};
inline point_t operator + ( const point_t &a, const point_t &b ){
    return { a.x+b.x, a.y+b.y };
}
inline point_t operator - ( const point_t &a, const point_t &b ){
    return { a.x-b.x, a.y-b.y };
}
inline point_t operator * ( const coord_t k, const point_t &p ){
    return {p.x * k, p.y * k};
}
inline point_t operator / ( const point_t &p, const coord_t k ){
    return {p.x / k, p.y / k};
}
inline point_t& operator += ( point_t &a, const point_t &b ){
    a.x += b.x;
    a.y += b.y;
    return a;
}
inline double point_t::length()const{
    return sqrt(x*x+y*y);
}
inline double point_t::length2()const{
    return x*x+y*y;
}

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

struct node_t : public body_t{
    bool is_empty;
    bool is_body;
    node_t *child[CHILDREN_NUMBER];
};

void add_body(node_t *node, const body_t *body, const point_t min, const point_t max){
    if ( body->x < min.x || body->x > max.x || body->y < min.y || body->y > max.y ){
        return;
    }
    node->x *= node->mass;
    node->y *= node->mass;
    node->x += body->x * body->mass;
    node->y += body->y * body->mass;
    node->mass += body->mass;
    node->x /= node->mass;
    node->y /= node->mass;

    if ( node->is_empty ){
        node->is_body = true;
        node->is_empty = false;
        return;
    }
    if ( node->is_body  ){
        for ( int child_idx = 0; child_idx < CHILDREN_NUMBER; ++child_idx ){
            node->child[child_idx] = new node_t();
        }
        push_to_children( node, node, min, max );
        node->is_body = false;
    }
    push_to_children(node, body, min, max );
}

void push_to_children(node_t *node, const body_t *body, const point_t &min, const point_t &max){
    point_t point[3] = { min, {(min.x+max.x)/2.0,(min.y+max.y)/2.0}, max };
    for ( int y_idx = 1, child_idx = 0; y_idx < BORDERS_NUMBER; ++y_idx ){
        for ( int x_idx = 1; x_idx < BORDERS_NUMBER; ++x_idx, ++child_idx ){
            add_body(
                     node->child[child_idx],
                     body,
                     {
                         point[x_idx-1].x,
                         point[y_idx-1].y
                     },
                     {
                         point[x_idx].x,
                         point[y_idx].y
                     }
            );
        }
    }
}

point_t calculate_force( const node_t &node, const body_t &body, const coord_t &size ){
    if ( node.is_body || size / (node-body).length() < THETA ){
        return get_force(body, node);
    }
    point_t result = {0.0, 0.0};
    for ( int i = 0; i < CHILDREN_NUMBER; ++i ){
        result += calculate_force( *node.child[i], body, size/2.0 );
    }
    return result;
}

void move_body( body_t &body, speed_t &speed, const point_t &force, const time_t time = MOVEMENT_TIME ){
    acceleration_t acceleration = force / body.mass;
    body += time * ( speed + time / 2.0 * acceleration );
    speed += time * acceleration;
}
