#include <cstdio>
#include <omp.h>
#include "barnes_hut.hpp"
#include "rw.hpp"

body_t bodies[MAX_BODIES_NUMBER];
speed_t speed[MAX_BODIES_NUMBER];
force_t forces[MAX_BODIES_NUMBER];
RGBTRIPLE spheres[MAX_BODIES_NUMBER];
int bodies_number;
duration_t interval;
coord_t space_radius;

int main( int argc, char **argv ){
	
    read_test(argc, argv, bodies_number, space_radius, bodies, spheres, speed, interval);

	timer_start();

	/*Paralell preparation*/

    /*Tree building*/
    point_t min_point = { -space_radius, -space_radius }, max_point = { space_radius, space_radius };
    build(bodies, bodies_number, min_point, max_point );
	
    /*Emulation*/
    calculate(bodies, bodies_number, forces, min_point, max_point);

    timer_finish();

	printf ( "%f ", timer_duration() );

    write_forces ( argc, argv, bodies_number, forces );

    return 0;
}
