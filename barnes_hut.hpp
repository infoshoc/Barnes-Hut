#pragma once

#include <cmath>
#include "body.hpp"

struct node_t;
void add_body(node_t*, const body_t*, const point_t, const point_t);

const void *NULLPTR = (void*)0;

const int CHILDREN_NUMBER = 4;
const int BORDERS_NUMBER = 3;
const coord_t THETA = 0.5;

struct node_t : public body_t{
    bool is_empty;
    bool is_body;
    node_t *child[CHILDREN_NUMBER];
};

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

