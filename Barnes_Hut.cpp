#include <cstdio>
#include "barnes_hut.hpp"
#include "rw.hpp"

body_t bodies[MAX_BODIES_NUMBER];
speed_t speed[MAX_BODIES_NUMBER];
force_t forces[MAX_BODIES_NUMBER];
unsigned int bodies_number;
coord_t space_radius;

int main( int argc, char **argv ){

    read_test(argc, argv, bodies_number, space_radius, bodies, speed);

    /*Tree building*/
    point_t min_point = { -space_radius, -space_radius }, max_point = { space_radius, space_radius };
    build(bodies, bodies_number, min_point, max_point );

    /*Information*/
    /*int max_i = 1;
    for ( int i = 1; i <= max_i; ++i ){
        printf ( "Node #%d", i );
        if ( tree[i].mass < EPS ){
            printf ( "is empty\n");
            continue;
        }
        max_i = max ( max_i, (i<<2)+3 );
        printf ( ":\n\tPosition: (%lf;%lf)\n\tMass: %lf\n\t", tree[i].x, tree[i].y, tree[i].mass );
        if ( tree[i].is_body ){
            printf ( "It's body\n" );
        }
    }*/

    /*Emulation*/
    calculate(bodies, bodies_number, forces, min_point, max_point);

    write_forces ( argc, argv, bodies_number, forces );

    return 0;
}
