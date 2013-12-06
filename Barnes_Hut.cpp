#include <cstdio>
#include <omp.h>
#include "barnes_hut.hpp"
#include "rw.hpp"

body_t bodies[MAX_BODIES_NUMBER];
speed_t speed[MAX_BODIES_NUMBER];
force_t forces[MAX_BODIES_NUMBER];
<<<<<<< HEAD
int bodies_number;
double interval;
=======
RGBTRIPLE spheres[MAX_BODIES_NUMBER];
int bodies_number;
duration_t interval;
>>>>>>> ef851aa6b73ac454ee38b52b4d620af88b34d411
coord_t space_radius;

int main( int argc, char **argv ){

<<<<<<< HEAD
    read_test(argc, argv, bodies_number, space_radius, bodies, speed, interval );
=======
    read_test(argc, argv, bodies_number, space_radius, bodies, spheres, speed, interval);
>>>>>>> ef851aa6b73ac454ee38b52b4d620af88b34d411

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
