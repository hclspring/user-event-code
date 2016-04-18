#include <cstring>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	enum AlgoType {CLIQUE, CUT};
	if(argc < 7){
		cerr << "Usage: " << argv[0] << " INPUT_FILE ASSIGNMENT_FILE ALPHA BETA GAMMA TYPE" << endl;
		cerr << " Note: TYPE have two possible values: cut, or clique." << endl;
		return 0;
	}

	string input_file = argv[1];
	string assignment_file = argv[2];
	double alpha = atof(argv[3]);
	double beta = atof(argv[4]);
	double gamma = atof(argv[5]);

	AlgoType type;
	if (strcmp(argv[6], "clique") == 0) {
		type = CLIQUE;
	} else {
		type = CUT;
	}

	Process p;
	p.read_preprocessed_data(input_file);
	p.read_assignment_data(assignment_file);
	if (type == CLIQUE) {
		cout << p.calc_clique_cost(alpha, beta, gamma) << endl;
	} else {
		cout << p.calc_cut_cost(alpha, beta, gamma) << endl;
	}
	return 0;
}

