#include <cstdio>
#include <string>
#include "barnes_hut.hpp"
using namespace std;

body_t bodies[MAX_BODIES_NUMBER];
speed_t speed[MAX_BODIES_NUMBER];
force_t force[MAX_BODIES_NUMBER];

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

    /*Emulation*/

    return 0;
}
