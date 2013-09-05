#include <cstdio>
#include <cmath>

const int MAXN = 30042;

double mass[MAXN];

struct point{
    double x, y;
} position[MAXN], forces[MAXN];

point operator - ( point a, point b ){
    return {a.x-b.x, a.y-b.y};
}

point operator + ( point a, point b ){
    return {a.x+b.x, a.y+b.y};
}
point operator * ( double a, point b ){
    return {a*b.x, a*b.y};
}

double length2(point p){
    return p.x*p.x+p.y*p.y;
}

point direction(point p){
    return 1.0/sqrt(length2(p))*p;
}

int main(int argc, char **argv){

    freopen(argc >= 2 ? argv[1] : "input.txt" , "r", stdin );
    freopen(argc >= 3 ? argv[2] : "output.txt", "w", stdout);

    int n;
    scanf ( "%d %*lf ", &n );
    for ( int i = 0; i < n; ++i ){
        scanf ( "%lf %lf %*lf %*lf %lf %*d %*d %*d ", &position[i].x, &position[i].y, &mass[i] );
    }

    for ( int i = 0; i < n; ++i ){
        forces[i] = {0.0, 0.0};
        for ( int j = 0; j < n; ++j ){
            if ( i == j ){
                continue;
            }
            forces[i] = forces[i] + (mass[i] * mass[j] / length2(position[j]-position[i])) * direction(position[j]-position[i]);
        }
        printf ( "#%u: (%lf; %lf)\n", i+1, forces[i].x, forces[i].y );
    }
}
