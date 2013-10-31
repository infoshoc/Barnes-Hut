#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>

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
    double *x = new double[body_number], *y = new double[body_number];
    for ( unsigned int i = 0; i < body_number; ++i ){
        double mass = abs ( random( max_mass ) );
        while ( mass < EPS ){
            mass = abs ( random( max_mass ) );
        }
        double new_x = random( radius ), new_y = random( radius );
        bool incorrect = true;
        while ( incorrect ) {
            incorrect = false;
            for ( unsigned int j = 0; j < i; ++j ){
                if ( abs ( new_x - x[j] ) < EPS && abs ( new_y - y[j] ) < EPS  ){
                    new_x = random( radius );
                    new_y = random( radius );
                    incorrect = true;
                    break;
                }
            }
        }
        x[i] = new_x;
        y[i] = new_y;
        printf (
            "%E %E %E %E %E %d %d %d\n",
            new_x, new_y,
            random( max_abs_speed ), random( max_abs_speed ),
            mass,
            255, 255, 0
        );
    }

    return 0;
}
