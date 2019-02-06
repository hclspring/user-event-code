#ifndef _UTIL_H_
#define _UTIL_H_

#include <vector>
#include <cassert>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>

class Util{
public:
	// Mathematics:
	static double calc_cos_similarity(const std::vector<double> & x, const std::vector<double> & y);
	static double calc_euc_distance(double x1, double y1, double x2, double y2);

	// Matrix:
	static double get_max_value(const std::vector<std::vector<double> > &x);
	static double get_min_value(const std::vector<std::vector<double> > &x);
	static void multiply(std::vector<std::vector<double> > &x, double y);

	// Vector:
	static double calc_mean(const std::vector<double> & v);

	// parse strings:
	static std::vector<double> read_line_doubles(const std::string &line);
	static std::vector<int> read_line_ints(const std::string &line);
	static int get_number_of_spaces(const std::string &line);

	// read file:
	static bool try_to_read_file(const std::string &filename, std::ifstream &ifs);

	// write file:
	static void write_matrix(const std::vector<std::vector<double> > &matrix, std::ofstream &ofs);

};
#endif
