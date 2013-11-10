#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

const double EPS = 1e-2;

double random( double max ){
    return 2.0 * max * rand() / (double)RAND_MAX - max;
}

int main( int argc, char **argv ){

    unsigned int body_number = 30000;
    double radius = 1e7, max_abs_speed = 1e5, max_mass = 1e20;

    unsigned int seed = time ( NULL );
    for ( int i = 1; i < argc; ++i ){
        if ( strcmp ( "-bodynumber", argv[i] ) == 0 ){
            body_number = atoll ( argv[++i] );
        } else if ( strcmp ( "-radius", argv[i] ) == 0 ){
            radius = atof ( argv[++i] );
        } else if ( strcmp ( "-seed", argv[i] ) == 0 ){
            seed = atoll ( argv[++i] );
        } else if ( strcmp ( "-maxabsspeed", argv[i] ) == 0 ){
            max_abs_speed = atof ( argv[++i] );
        } else if ( strcmp ( "-maxmass", argv[i] ) == 0 ){
            max_mass = atof ( argv[++i] );
        } else {
            fprintf ( stderr, "Unknown param %s\n", argv[i] );
        }
    }

    srand ( seed );

    printf ( "%u\n%E\n", body_number, radius );
    int **coord = new int*[4*body_number];
    for ( unsigned int i = 0; i < 4*body_number; ++i ){
        coord[i] = new int[2];
        coord[i][0] = coord[i][1] = i - 2*body_number;
    }
    for ( unsigned int i = 0; i < 4*body_number; ++i ){
        for ( short j = 0; j < 2; ++j ){
            swap ( coord[i][j], coord[rand()%(4*body_number)][j] );
        }
    }

    for ( unsigned int i = 0; i < body_number; ++i ){
        double x = coord[i][0] * radius / 2 / body_number,
               y = coord[i][1] * radius / 2 / body_number;
        printf (
            "%E %E %E %E %E %d %d %d\n",
            x, y,
            random( max_abs_speed ), random( max_abs_speed ),
            abs ( random( max_mass - EPS )+EPS ),
            255, 255, 0
        );
    }

    return 0;
}
