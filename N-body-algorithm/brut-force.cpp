#include <cmath>
#include "rw.hpp"

const unsigned int MAX_BODIES_NUMBER = 30042;

double x[MAX_BODIES_NUMBER], y[MAX_BODIES_NUMBER], mass[MAX_BODIES_NUMBER], speed_x[MAX_BODIES_NUMBER], speed_y[MAX_BODIES_NUMBER], force_x[MAX_BODIES_NUMBER], force_y[MAX_BODIES_NUMBER];

int main( int argc, char **argv ){

	unsigned int bodies_number;
	read_test(argc, argv, bodies_number, x, y, mass, speed_x, speed_y);
	
	timer_start();

	for ( unsigned int i = 0; i < bodies_number; ++i ) {
		force_x[i] = force_y[i] = 0.0;
		for ( unsigned int j = 0; j < bodies_number; ++j ) {
			if ( j == i ) {
				continue;
			}
			double dx = x[j]-x[i], dy = y[j]-y[i], distance = sqrt ( dx*dx + dy*dy );
			force_x[i] += mass[j] * dx / ( distance * distance * distance );
			force_y[i] += mass[j] * dy / ( distance * distance * distance );
		}
		force_x[i] *= mass[i];
		force_y[i] *= mass[i];
	}
	
	timer_finish();
	
	printf ( "%f s\n", timer_duration() );

	write_forces(argc, argv, bodies_number, force_x, force_y );

	return 0;
}