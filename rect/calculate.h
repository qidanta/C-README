#include <iostream>
#include <string>
#include <list>
#include <vector>

#include <./boost/geometry.hpp>
#include <./boost/geometry/geometries/point_xy.hpp>
#include <./boost/geometry/geometries/polygon.hpp>
#include <./boost/foreach.hpp>

#include "util.h"

namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point_type;
typedef bg::model::polygon<point_type> polygon_type;

/*@parmet:input string of polygon
 *@func:calculate the area of polygon
 */
double calculate(std::string pg){
	polygon_type poly;
	bg::read_wkt(pg, poly);
	double area = bg::area(poly);
	return area;
}
/*@parmet:input string of muti_polygon
 *@func:calculate the area of muti_polygon(the area of poly1 plus the area of poly2 etc)
 */
double calculatemp(std::string pg){
	bg::model::multi_polygon<polygon_type> mp;
	bg::read_wkt(pg, mp);
	double area = bg::area(mp);
	return area;
}
/*@parmet:input polygon_type and point_type
 *@func:calculate point in/out polygon;in return 1;
 *@return:in return 1;out return 0
 */
bool inside(polygon_type polygon, point_type point){
	return bg::within(point, polygon);
}

/*@parmet:input two polygon_type
*@func:calculate pg1 outer/cross/inside by the num of point of pg1 inside pg2
*@return:outer-0;inside-5
*/
int overlap(polygon_type rect, polygon_type pg){
	int size = rect.outer().size();
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (inside(pg, rect.outer()[i]))
			j++;
	}
	return j;
}

/*@parmet:input two polygon_type
 *@func:calculate the area of intersection part between rect and pg
 *@return:intersection area
*/
double intersection(polygon_type rect, polygon_type pg){
	std::list<polygon_type> output;
	bg::difference(rect, pg, output);
	double differenceArea = 0,
		insectionArea = 0;
	BOOST_FOREACH(polygon_type const& p, output) {
		differenceArea += bg::area(p);
	}
	return (bg::area(rect) - differenceArea);
}

/*main func*/
/**
 * calculate overlap's area(rect, pg)/area(pg)
 *
 * - Params:
 * @rect: look like POLYGON((100 100,100 300,300 300,300 100,100 100)), use for /area(pg)
 * @pg: look like POLYGON((100 100,100 300,300 300,300 100,100 100)), use for overlap's area(rect, pg)
 *
 * - Returns:
 * doule type, area of overlap(rect, pg)/area(pg)
*/
double per(std::string rect, std::string pg){
	polygon_type poly1 = string2poly(rect);
	polygon_type poly2 = string2poly(pg);
	int insidePts = overlap(poly1, poly2);
	int insidePts2 = overlap(poly2, poly1);
	double intersectionArea = 0,
		rectArea = bg::area(poly2);
	if (insidePts == 0) {
		if (bg::overlaps(poly1, poly2))
			intersectionArea = intersection(poly1, poly2);
		else {
			if (insidePts2 == poly2.outer().size() + 1) {
				intersectionArea = bg::area(poly2);
			}
			else if(insidePts2) {
				intersectionArea = bg::area(poly2);
			}
			else {
				intersectionArea = 0;
			}
		}
	}
	else if (insidePts == 5) {
		intersectionArea = bg::area(poly1);
	}
	else {
		if (!bg::overlaps(poly1, poly2))
			intersectionArea = bg::area(poly1);
		else {
			intersectionArea = intersection(poly1, poly2);
		}
	}
	return intersectionArea/rectArea;
}




/*@parmet:input polygon_type
 *@func:cout edge of polygon's point
 */
void for_eachouter(polygon_type polygon){
	int size = polygon.outer().size();
	for (int i = 0; i < size; i++){
		std::cout << bg::wkt(polygon.outer()[i]) << std::endl;
	}
}

