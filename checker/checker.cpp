#include <cstdio>
#include <cmath>
#include <ctgmath>
#include <cstdlib>
using namespace std;
const char pattern[] = "Body #%u: force: (%lf; %lf) ";

int main( int argc, char **argv ){

    FILE **files = new FILE*[argc];

    for ( int i = 1; i < argc; ++i ) {
        files[i] = fopen ( argv[i], "r" );
        if ( files[i] == NULL ){
            fprintf ( stderr, "File #%d not found\n", i );
        }
    }

    double *x = new double[argc];
    double *y = new double[argc];
    bool *success_body = new bool[argc];
    while ( true ){
        static int idx = 1;
        int success_number = 0;
        double x_sum, y_sum;
        for ( int i = 1; i < argc; ++i ){
            success_body[i] = false;
            unsigned int body_idx;
            if ( fscanf ( files[i], pattern, &body_idx, &x[i], &y[i] ) != 3 ){
                fprintf ( stderr, "File #%d cannot read body #%d\n", i, idx );
                continue;
            }
            if ( (int)body_idx != idx ){
                fprintf ( stderr, "File #%d expected body #%d - found body #%d\n", i, idx, body_idx );
                continue;
            }
            x_sum += x[i];
            y_sum += y[i];
            ++success_number;
            success_body[i] = true;
        }
        if ( !success_number ){
            break;
        }
        printf ( "Body #%d\n", idx );
        double real_x = x_sum / success_number, real_y = y_sum / success_number;
        printf ( "\tReal Force = (%.10f, %.10f)\n", real_x, real_y );
        double dx_sum = .0, dy_sum = .0;
        for ( int i = 1; i < argc; ++i ){
            if ( !success_body[i] ){
                continue;
            }
            dx_sum += abs ( real_x - x[i] );
            dy_sum += abs ( real_y - y[i] );
        }
        double abs_error_x = dx_sum / success_number, abs_error_y = dy_sum / success_number;
        printf ( "\tAbsolute Error = (%.10f, %.10f)\n", abs_error_x, abs_error_y );
        printf ( "\tRelative Error = (%.10f%%, %.10f%%)\n", abs_error_x / real_x * 100, abs_error_y / real_y * 100 );
        ++idx;
    }

    for ( int i = 1; i < argc; ++i ) {
        fclose ( files[i-1] );
    }

	return 0;
}
