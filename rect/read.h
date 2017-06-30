#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <./boost/geometry.hpp>
#include <./boost/geometry/geometries/point_xy.hpp>
#include <./boost/geometry/geometries/polygon.hpp>

using namespace std;
namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point_type;
typedef bg::model::polygon<point_type> polygon_type;

vector<string> read(string filepath){
	ifstream in(filepath);
	string temp;
	vector<string> poly;
	if (in){
		while (getline(in, temp))
		{
			/*cout << temp << endl;*/
			poly.push_back(temp);
		}
	}
	else{
		cout << "error" << endl;
	}
	in.close();
	return poly;
}

vector<polygon_type> createPoly(string filepath){
	vector<polygon_type> mps;
	vector<string> poly;
	vector<string>::iterator it;
	poly = read(filepath);
	for (it = poly.begin(); it != poly.end(); it++){
		polygon_type poly;
		bg::read_wkt(*it, poly);
		mps.push_back(poly);
	}
	return mps;
}