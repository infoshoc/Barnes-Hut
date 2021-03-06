#pragma once

#pragma warning ( disable : 4996 )

#include <cstdio>
#include <omp.h>
#include <string>
using namespace std;

void read_test(const int argc, char *argv[], unsigned int &bodies_number, double *x, double *y, double *mass, double *speed_x, double *speed_y ){
    string file_name = argc >= 2 ? string( argv[1] ) : "input.dat";

    FILE *fh = fopen ( file_name.c_str(), "r" );
    if ( NULL == fh ){
        printf ( "File %s not found\n", file_name.c_str() );
        exit(1);
    }

    if ( fscanf( fh, "%u ", &bodies_number ) != 1 ){
        printf ( "Bodies number not found\n" );
        exit(2);
    }

	double space_radius;
    if ( fscanf ( fh, "%lf ", &space_radius ) != 1 ){
        printf ( "Space radius not found\n" );
        exit(3);
    }

    for ( unsigned int i = 0; i < bodies_number; ++i ){
        static int red, green, blue;
        if ( fscanf (
                fh,
                "%lf %lf %lf %lf %lf %d %d %d ",
                &x[i], &y[i],
                &speed_x[i], &speed_y[i],
                &mass[i],
                &red, &green, &blue
            ) != 8 ){
            printf ( "Full information about body #%d not found\n", i+1 );
            exit(4);
        }
    }
}

void write_forces( const int argc, char *argv[], const unsigned int bodies_number, const double *forces_x, const double *forces_y ){
    string file_name = argc >= 3 ? argv[2] : "output.txt";
    FILE *fh = fopen(file_name.c_str(), "w");
    for ( unsigned int i = 0; i < bodies_number; ++i ){
		fprintf ( fh, "Body #%u: force: (%f; %f)\n", i+1, forces_x[i], forces_y[i] );
    }
    fclose(fh);
}



static double start, finish;
inline void timer_start(){
#ifdef STUDIO 
	start = omp_get_wtime();
#endif
}
inline void timer_finish(){
#ifdef STUDIO
	finish = omp_get_wtime();
#endif
}
inline double timer_duration(){
	return finish-start;
}