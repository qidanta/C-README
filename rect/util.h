#include <iostream>
#include <string>
#include <list>

#include <./boost/geometry.hpp>
#include <./boost/geometry/geometries/point_xy.hpp>
#include <./boost/geometry/geometries/polygon.hpp>

using namespace std;
namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point_type;
typedef bg::model::polygon<point_type> polygon_type;

polygon_type string2poly(string pg){
	polygon_type poly;
	bg::read_wkt(pg, poly);
	return poly;
}