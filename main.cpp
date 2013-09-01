#include <cstdio>
#include "barnes_hut.hpp"
#include <string>
using namespace std;

const int CMD_PARAMETER_NUMBER = 2;
enum PARAMETER_INDEX{FILE_NAME, STEPS_NUMER};
const string PARAMETER_NAME[CMD_PARAMETER_NUMBER] = { "-file", "-steps_number" };
string parameter_value[CMD_PARAMETER_NUMBER] = { "input.dat", "42" };

int main( int argc, string argv[] ){

    for ( int arg_i = 1; arg_i < argc-1; ++arg_i ){
        for ( int parameter_i = 0; parameter_i < CMD_PARAMETER_NUMBER; ++parameter_i ){
            if ( PARAMETER_NAME[parameter_i] == argv[arg_i] ){
                parameter_value[parameter_i] = argv[arg_i+1];
                break;
            }
        }
    }

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
        double mass, x, y;
        if ( scanf ( "%lf %lf %lf ", &mass, &x, &y ) != 3 ){
            printf ( "Body #%u not found\n", i+1 );
            return 3;
        }
    }
    fclose(fh);

    return 0;
}
