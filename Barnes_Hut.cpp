#include <cstdio>
#include <string>
#include "barnes_hut.hpp"
using namespace std;

body_t bodies[MAX_BODIES_NUMBER];
speed_t speed[MAX_BODIES_NUMBER];
force_t forces[MAX_BODIES_NUMBER];

int main( int argc, char **argv ){

    /*CMD params*/
    string file_name = argc >= 2 ? string( argv[1] ) : "input.dat";

    /*Input file read*/
    FILE *fh = fopen ( file_name.c_str(), "r" );
    if ( NULL == fh ){
        printf ( "File %s not found\n", file_name.c_str() );
        return 1;
    }

    duration_t movement_time = 0.1;
    unsigned int bodies_number;
    coord_t space_radius;

    if ( fscanf( fh, "%u ", &bodies_number ) != 1 ){
        printf ( "Bodies number not found\n" );
        return 2;
    }

    /*Input file read*/
    if ( fscanf ( fh, "%lf ", &space_radius ) != 1 ){
        printf ( "Space radius not found\n" );
        return 3;
    }

    for ( unsigned int i = 0; i < bodies_number; ++i ){
        static int red, green, blue;
        if ( fscanf (
                fh,
                "%lf %lf %lf %lf %lf %d %d %d ",
                &bodies[i].x, &bodies[i].y,
                &speed[i].x, &speed[i].y,
                &bodies[i].mass,
                &red, &green, &blue
            ) != 8 ){
            printf ( "Full information about body #%d not found\n", i+1 );
            return 4;
        }
    }

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
    file_name = argc >= 3 ? argv[2] : "output.txt";
    fh = fopen(file_name.c_str(), "w");
    for ( unsigned int i = 0; i < bodies_number; ++i ){
        fprintf ( fh, "Body #%u: force:(%lf; %lf)\n", i+1, forces[i].x, forces[i].y );
    }
    fclose(fh);

    return 0;
}
