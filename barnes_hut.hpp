#pragma once

#include <omp.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "body.hpp"
#include "theta.hpp"
using namespace std;

/*API*/
void build(body_t*, const unsigned int, const point_t, const point_t);
void calculate(const body_t*, unsigned int, force_t*, const point_t, const point_t);

const int CHILDREN_NUMBER = 4;
const int BORDERS_NUMBER = 3;
const unsigned int MAX_BODIES_NUMBER = 500042;

struct node_t : public body_t{
    bool is_body;
    node_t* child[CHILDREN_NUMBER];
#ifdef _OPENMP
	omp_lock_t lock;
#endif
} *root = new node_t(); 

void add_body ( node_t *, const body_t, const point_t, const point_t ) ;
void push_to_children(node_t *node, const body_t body, const point_t &min, const point_t &max){
    point_t point[3] = { min, {(min.x+max.x)/2.0,(min.y+max.y)/2.0}, max };
    for ( int y_idx = 1, child_idx = 0; y_idx < BORDERS_NUMBER; ++y_idx ){
        for ( int x_idx = 1; x_idx < BORDERS_NUMBER; ++x_idx, ++child_idx ){
			point_t min = make_point (
                point[x_idx-1].x,
                point[y_idx-1].y
            );
			point_t max = make_point (
					point[x_idx].x,
					point[y_idx].y
			);
			if ( body.x < min.x || body.x > max.x || body.y < min.y || body.y > max.y ){
				continue;
			}
            if ( node->child[child_idx] == NULL ){
                node->child[child_idx] = new node_t();
#ifdef _OPENMP
				omp_init_lock(&node->child[child_idx]->lock);
#endif
            }
#ifdef _OPENMP
			omp_unset_lock(&node->lock);
#endif
            add_body(
                node->child[child_idx],
                body,
				min,
				max                     
            );
#ifdef _OPENMP
			omp_set_lock(&node->lock);
#endif
			return;
        }
    }
#ifdef _DEBUG
	printf ( "Body was not added\n" );
#endif
}

void add_body(node_t *node, const body_t body, const point_t min, const point_t max){
#ifdef _DEBUG
	printf ( "Thread: %d\tNode: %u\n", omp_get_thread_num(), node );
#endif
#ifdef _OPENMP
	omp_set_lock(&node->lock);
#endif
    if ( node->mass < EPS ){
        memcpy ( node, &body, sizeof(body_t) );
        node->is_body = true;
#ifdef _OPENMP
		omp_unset_lock(&node->lock);
#endif
        return;
    }
    if ( node->is_body ){
        node->is_body = false;
        push_to_children( node, *node, min, max );
    }
    node->x *= node->mass;
    node->y *= node->mass;
    node->x += body.x * body.mass;
    node->y += body.y * body.mass;
    node->mass += body.mass;
    node->x /= node->mass;
    node->y /= node->mass;
    push_to_children(node, body, min, max );
#ifdef _OPENMP
	omp_unset_lock(&node->lock);
#endif
}

force_t calculate_force( const node_t node, const body_t &body, const coord_t &size ){
    if ( node.mass < EPS || (body-node).length2() < EPS ){
        return make_point ( 0.0, 0.0 );
    }
    if ( node.is_body || fabs(size / (node-body).length()) < THETA ){
        return get_force(body, node);
    }
    force_t result = {0.0, 0.0};
    for ( int i = 0; i < CHILDREN_NUMBER; ++i ){
        if ( node.child[i] == NULL ){
            continue;
        }
        result += calculate_force( *node.child[i], body, size/2.0 );
    }
    return result;
}

void build ( body_t *bodies, const int bodies_number, const point_t min_point, const point_t max_point ){
    memset(root, 0, sizeof(node_t));
#ifdef _OPENMP
	omp_init_lock(&root->lock);
#endif
#pragma omp parallel for
    for ( int i = 0; i < bodies_number; ++i ){
        add_body(root, bodies[i], min_point, max_point );
    }
}
void calculate( const body_t *bodies, const int bodies_number, force_t *forces, const point_t min_point, const point_t max_point ){
    static coord_t size = min_point.x - max_point.x;
#pragma omp parallel for schedule (dynamic)
    for ( int i = 0; i < bodies_number; ++i ){
        forces[i] = calculate_force(*root, bodies[i], size );
    }
}

void movement ( body_t *bodies, const int bodies_number, const force_t *forces, speed_t *speeds, const duration_t time ){
#pragma omp parallel for schedule (static)
    for ( int i = 0; i < bodies_number; ++i ){
        move_body(bodies[i], speeds[i], forces[i], time );
    }
}
