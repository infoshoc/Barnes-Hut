#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

const char format[] = "Body #%u: force: (%Lf; %Lf) ";

int main( int argc, char **argv ){

	if ( argc < 4 ) {
		printf ( "Arguments are:\n\t[1] - input\n\t[2] - output\n\t[3] - correct answer\n\t[4] - verdict file (optional)" );
		return 1;
	}

	FILE *inp = fopen ( argv[1], "r" );
	if ( inp == NULL ) {
		printf ( "Could not open \"%s\" for reading\n", argv[1] );
		return 2;
	}
	FILE *out = fopen ( argv[2], "r" );
	if ( out == NULL ) {
		printf ( "Could not open \"%s\" for reading\n", argv[2] );
		return 3;
	}
	FILE *ans = fopen ( argv[3], "r" );
	if ( ans == NULL ) {
		printf ( "Could not open \"%s\" for reading\n", argv[3] );
		return 2;
	}
	FILE *ver = argc >= 5 ? fopen ( argv[4], "w" ) : stdout;

	unsigned int body_number;
	fscanf ( inp, "%u ", &body_number );
	fclose ( inp );

	long double max_relative_value = 0.0;
	long double average_relative_value = 0.0;
	unsigned int max_relative_idx;

	for ( unsigned int i = 0; i < body_number; ++i ) {
		static unsigned int body_idx[2];
		static long double x, y, absolute, relative, abs_force[2];

		if ( fscanf ( ans, format, &body_idx[0], &x, &y ) < 3 ) {
			printf ( "Can not find all answer information about body #%u\n", i+1 );
			return 5;
		}
		abs_force[0] = sqrt ( x * x + y * y );

		if ( fscanf ( out, format, &body_idx[1], &x, &y ) < 3 ) {
			printf ( "Can not find all answer information about body #%u\n", i+1 );
			return 6;
		}
		abs_force[1] = sqrt ( x * x + y * y );

		if ( body_idx[0] != body_idx[1] ){
			fprintf ( ver, "Body #%u found. Expected #%u\n", body_idx[1], body_idx[0] );
			break;
		}

		absolute = abs ( abs_force[1] - abs_force[0] );
		relative = abs ( absolute / abs_force[0] );

		average_relative_value += relative;
		
		if ( relative > max_relative_value ) {
			max_relative_value = relative;
			max_relative_idx = body_idx[0];
		}

		fprintf ( ver, "Body #%u:\n\tAbsolute:%Lf\n\tRelative:%Lf\n", body_idx[0], absolute, relative );
	}

	average_relative_value /= body_number;
	
	fprintf ( ver, "Maximal Relative Body #%u value = %Lf\n", max_relative_idx, max_relative_value );
	fprintf ( ver, "Average Relative %Lf\n", average_relative_value );

	fclose ( ver );

	printf ( "%Lf ", average_relative_value );

	return 0;
}
