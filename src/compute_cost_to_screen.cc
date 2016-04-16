#include <cstring>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	enum AlgoType {CLIQUE, CUT};
	if(argc < 7){
		cerr << "Usage: " << argv[0] << " INPUT_FILE ASSIGNMENT_FILE TYPE ALPHA BETA GAMMA" << endl;
		return 0;
	}

	string input_file = argv[1];
	string assignment_file = argv[2];
	AlgoType type;
	if (strcmp(argv[3], "CLIQUE") == 0) {
		type = CLIQUE;
	} else {
		type = CUT;
	}

	double alpha = atof(argv[4]);
	double beta = atof(argv[5]);
	double gamma = atof(argv[6]);

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

