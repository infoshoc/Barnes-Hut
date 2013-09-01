#include <cstdio>
#include <cstdlib>
#include "barnes_hut.hpp"
#include <string>
using namespace std;

const int CMD_PARAMETER_NUMBER = 4;
enum {FILE_NAME, STEPS_NUMER, MIN_COORD, MAX_COORD};
const string PARAMETER_NAME[CMD_PARAMETER_NUMBER] = { "-file", "-steps_number", "-min_coord", "-max_coord" };
string parameter_value[CMD_PARAMETER_NUMBER] = { "input.dat", "42", "-42.0", "42.0" };

const int MAX_BODIES_NUMBER = 42;
body_t bodies[MAX_BODIES_NUMBER];

node_t root;

int main( int argc, char **argv ){

    for ( int arg_i = 1; arg_i < argc-1; ++arg_i ){
        string argument = argv[arg_i];
        for ( int parameter_i = 0; parameter_i < CMD_PARAMETER_NUMBER; ++parameter_i ){
            if ( PARAMETER_NAME[parameter_i] == argument ){
                parameter_value[parameter_i] = argv[arg_i+1];
                break;
            }
        }
    }

    char *endprt;
    coord_t min_coord = strtod( parameter_value[MIN_COORD].c_str(), &endprt );
    point_t min_point = {min_coord, min_coord};
    coord_t max_coord = strtod( parameter_value[MAX_COORD].c_str(), &endprt );
    point_t max_point = {max_coord, max_coord};


    FILE *fh = fopen(parameter_value[FILE_NAME].c_str(), "r");
    if ( fh == NULLPTR ){
        fprintf ( stderr, "File Not Found\n" );
        return 1;
    }
    unsigned int body_number;
    if ( scanf("%u ", &body_number) != 1 ) {
        fprintf ( stderr, "Bodies number not found\n");
        return 2;
    }
    for ( unsigned int i = 0; i < body_number; ++i ){
        if ( scanf ( "%lf %lf %lf ", &bodies[i].mass, &bodies[i].x, &bodies[i].y ) != 3 ){
            printf ( "Body #%u not found\n", i+1 );
            return 3;
        }
        add_body( &root, bodies + i, min_point, max_point );
    }
    fclose(fh);

    return 0;
}
