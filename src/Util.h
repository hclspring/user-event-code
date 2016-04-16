#ifndef _UTIL_H_
#define _UTIL_H_

#include <vector>
#include <cassert>
#include <cmath>
#include <sstream>
#include <string>

class Util{
public:
	double calc_cos_similarity(const std::vector<double> & x, const std::vector<double> & y);
	double calc_euc_distance(double x1, double y1, double x2, double y2);

	std::vector<double> read_line_doubles(const std::string &line);
	std::vector<int> read_line_ints(const std::string &line);

	int get_number_of_spaces(const std::string &line);

};
#endif
