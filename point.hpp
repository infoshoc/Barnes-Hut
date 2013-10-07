#pragma once

typedef double coord_t;

struct point_t{
    coord_t x, y;
    double length()const;
    double length2()const;
};
static point_t make_point( const coord_t x, const coord_t y ){
	point_t result;
	result.x = x;
	result.y = y;
	return result;
}

inline point_t operator + ( const point_t &a, const point_t &b ){
    return make_point ( a.x+b.x, a.y+b.y );
}
inline point_t operator - ( const point_t &a, const point_t &b ){
    return make_point ( a.x-b.x, a.y-b.y );
}
inline point_t operator * ( const coord_t k, const point_t &p ){
    return make_point ( p.x * k, p.y * k );
}
inline point_t operator / ( const point_t &p, const coord_t k ){
    return make_point ( p.x / k, p.y / k );
}
inline point_t& operator += ( point_t &a, const point_t &b ){
    a.x += b.x;
    a.y += b.y;
    return a;
}
inline double point_t::length()const{
    return sqrt(x*x+y*y);
}
inline double point_t::length2()const{
    return x*x+y*y;
}
