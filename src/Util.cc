#include "Util.h"

using namespace std;

double Util::calc_cos_similarity(const std::vector<double> & x, const std::vector<double> & y){
	double fenzi = 0, fenmu1 = 0, fenmu2 = 0;
	assert(x.size() == y.size());
	for(int i = 0; i < x.size(); i++){
		fenzi += x[i] * y[i];
		fenmu1 += x[i] * x[i];
		fenmu2 += y[i] * y[i];
	}
	return 1.0 * fenzi / (sqrt(fenmu1 * fenmu2));
}

double Util::calc_euc_distance(double x1, double y1, double x2, double y2){
	double dx = x2 - x1;
	double dy = y2 - y1;
	return sqrt(dx*dx + dy*dy);
}

double Util::get_max_value(const vector<vector<double> > &x) {
	assert(x.size() > 0 && x[0].size() > 0);
	double max_value = -numeric_limits<double>::max();
	for (int i = 0; i < x.size(); ++i) {
		for (int j = 0; j < x[i].size(); ++j) {
			if (max_value < x[i][j]) {
				max_value = x[i][j];
			}
		}
	}
	return max_value;
}

double Util::get_min_value(const vector<vector<double> > &x) {
	assert(x.size() > 0 && x[0].size() > 0);
	double min_value = numeric_limits<double>::max();
	for (int i = 0; i < x.size(); ++i) {
		for (int j = 0; j < x[i].size(); ++j) {
			if (min_value > x[i][j]) {
				min_value = x[i][j];
			}
		}
	}
	return min_value;
}


void Util::multiply(vector<vector<double> > &x, double y) {
	for (int i = 0; i < x.size(); ++i) {
		for (int j = 0; j < x[i].size(); ++j) {
			x[i][j] *= y;
		}
	}
}

double Util::calc_mean(const std::vector<double> & v) {
	int n = v.size();
	assert(n > 0);
	double sum;
	for (int i = 0; i < n; ++i) {
		sum += v[i];
	}
	return sum / n;
}

std::string Util::to_lower_copy(const std::string& s) {
	std::string res = s;
	for (int i = 0; i < res.size(); ++i) {
		if (std::isalpha(res[i]) && std::isupper(res[i])) {
			res[i] = std::tolower(res[i]);
		}
	}
	return res;
}

vector<double> Util::read_line_doubles(const string &line)
{
	stringstream ss(line);
	vector<double> res;
	double number;
	while(ss.good()){
		ss >> number;
		res.push_back(number);
	}
	return res;
}

vector<int> Util::read_line_ints(const string &line)
{
	stringstream ss(line);
	vector<int> res;
	int number;
	while(ss.good()){
		ss >> number;
		res.push_back(number);
	}
	return res;
}


int Util::get_number_of_spaces(const string &line)
{
	int count = 0;
	for(int i = 0; i < line.size(); i++){
		if(line[i] == ' ' || line[i] == '\t'){
			count++;
		}
	}
	return count;
}

bool Util::try_to_read_file(const std::string &filename, std::ifstream &ifs)
{
	ifs.open(filename.c_str());
	if (ifs.fail()) {
		cerr << "Read file " << filename << " error." << endl;
		return false;
	} else {
		return true;
	}
}

void Util::write_matrix(const std::vector<std::vector<double> > &matrix, std::ofstream &ofs) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			if (j > 0) {
				ofs << " ";
			}
			ofs << matrix[i][j];
		}
		ofs << std::endl;
	}
}

