#include <cstdio>
#include <cmath>
#include <ctgmath>
using namespace std;
const char pattern[] = "Body #%u: force: (%lf; %lf) ";

int main( int argc, char **argv ){

	if ( argc < 4 ) {
		printf ( "Arguments are:\n[1] - first solution file name\n[2] - second solution file name\n[3] - verdict file name\n" );
		return 1;
	}

	FILE *in1 = fopen ( argv[1], "r" );
	FILE *in2 = fopen ( argv[2], "r" );
	FILE *out = fopen ( argv[3], "w" );
	unsigned int i1, i2;
	double x1, x2, y1, y2;
	while ( fscanf ( in1, pattern, &i1, &x1, &y1 ) == 3 && fscanf ( in2, pattern, &i2, &x2, &y2 ) == 3 ) {
		if ( i1 != i2 ) {
			printf ( "Wrong index\n" );
			return 2;
		}
		printf ( "Body #%u:\n\t[1] - (%.10f; %.10f)\n\t[2] - (%.10f; %.10f)\n", i1, x1, y1, x2, y2 );
		double x = (x1+x2)/2.0L;
		double y = (y1+y2)/2.0L;
		double dx1 = abs(x1-x);
		double dy1 = abs(y1-y);
		double dx2 = abs(x2-x);
		double dy2 = abs(y2-y);
		double dx = (dx1+dx2)/2.0L;
		double dy = (dy1+dy2)/2.0L;
		double ex = abs(dx/x);
		double ey = abs(dy/y);
		fprintf ( out, "Body #%u:\n\treal value: (%.10f; %.10f)\n\tabsolute error: (%.10f; %.10f)\n\trelative error: (%.10f; %.10f)\n", i1, x, y, dx, dy, ex, ey );
	}
	fclose ( in1 );
	fclose ( in2 );
	fclose ( out );

	return 0;
}
