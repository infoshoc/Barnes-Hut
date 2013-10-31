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
	unsigned int max_relative_idx;

	for ( unsigned int i = 0; i < body_number; ++i ) {
		static unsigned int body_idx[2];
		static long double force[2][2], absolute[2], relative[2];
		
		if ( fscanf ( ans, format, &body_idx[0], &force[0][0], &force[0][1] ) < 3 ) {
			printf ( "Can not find all answer information about body #%u\n", i+1 );
			return 5;
		}

		if ( fscanf ( out, format, &body_idx[1], &force[1][0], &force[1][1] ) < 3 ) {
			printf ( "Can not find all answer information about body #%u\n", i+1 );
			return 6;
		}

		if ( body_idx[0] != body_idx[1] ){
			fprintf ( ver, "Body #%u found. Expected #%u\n", body_idx[1], body_idx[0] );
			break;
		}

		absolute[0] = abs ( force[1][0] - force[0][0] );
		absolute[1] = abs ( force[1][1] - force[0][1] );
		relative[0] = abs ( absolute[0]*100.0 / force[0][0] );
		relative[1] = abs ( absolute[1]*100.0 / force[0][1] );

		if ( max ( relative[0], relative[1] ) > max_relative_value ) {
			max_relative_value = max ( relative[0], relative[1] );
			max_relative_idx = body_idx[0];
		}

		fprintf ( ver, "Body #%u:\n\tAbsolute:(%Lf; %Lf)\n\tRelative:(%Lf%%; %Lf%%)\n", body_idx[0], absolute[0], absolute[1], relative[0], relative[1] );
	}

	fprintf ( ver, "Maximal Relative Body #%u value = %Lf%%\n", max_relative_idx, max_relative_value );

	fclose ( ver );

	return 0;
}