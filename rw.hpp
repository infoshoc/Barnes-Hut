#pragma once

#pragma warning ( disable : 4996 )

#include <cstdio>
#include <omp.h>
#include <ctime>
#include <string>
#include "body.hpp"
#include <Windows.h>
using namespace std;

void read_test(const int argc, char *argv[], int &bodies_number, coord_t &space_radius, body_t *bodies, RGBTRIPLE *spheres, speed_t *speed, duration_t &interval ){
    string file_name = argc >= 2 ? string( argv[1] ) : "input.dat";

    FILE *fh = fopen ( file_name.c_str(), "r" );
    if ( NULL == fh ){
        printf ( "File %s not found\n", file_name.c_str() );
        exit(1);
    }

    if ( fscanf( fh, "%d ", &bodies_number ) != 1 ){
        printf ( "Bodies number not found\n" );
        exit(2);
    }

    if ( fscanf ( fh, "%lf ", &space_radius ) != 1 ){
        printf ( "Space radius not found\n" );
        exit(3);
    }

    for ( int i = 0; i < bodies_number; ++i ){
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
            exit(4);
        }
		spheres[i].rgbtBlue = (BYTE)blue;
		spheres[i].rgbtGreen = (BYTE)green;
		spheres[i].rgbtRed = (BYTE)red;
    }

	interval = argc >= 3 ? atoi ( argv[2] ) : 1;
}

void write_forces( const int argc, char *argv[], const int bodies_number, const force_t *forces ){
    string file_name = argc >= 3 ? argv[2] : "output.txt";
    FILE *fh = fopen(file_name.c_str(), "w");
    for ( int i = 0; i < bodies_number; ++i ){
        fprintf ( fh, "Body #%d: force: (%f; %f)\n", i+1, forces[i].x, forces[i].y );
    }
    fclose(fh);
}

void write_bodies ( const int argc, char *argv[], const int bodies_number, const body_t *bodies, const RGBTRIPLE *spheres, const speed_t *speed, const coord_t space_radius ){
    string file_name = argc >= 4 ? argv[3] : "bodies.txt";
    FILE *fh = fopen ( file_name.c_str(), "w" );
    fprintf ( fh, "%d\n%lf\n", bodies_number, space_radius );
    for ( int i = 0; i < bodies_number; ++i ){
        fprintf (
            fh,
            "%lf %lf %lf %lf %lf %d %d %d\n",
            bodies[i].x, bodies[i].y,
            speed[i].x, speed[i].y,
            bodies[i].mass,
            spheres[i].rgbtRed, spheres[i].rgbtGreen, spheres[i].rgbtBlue
        );
    }
    fclose ( fh );
}


static
#ifdef STUDIO
    double
#else
    time_t
#endif
    start, finish;
inline void timer_start(){
	start =
#ifdef STUDIO
    omp_get_wtime();
#else
    time(NULL);
#endif
}
inline void timer_finish(){
    finish =
#ifdef STUDIO
	omp_get_wtime();
#else
    time(NULL);
#endif
}
inline double timer_duration(){
	return
#ifdef STUDIO
		finish-start;
#else
	difftime(finish, start);
#endif
}
