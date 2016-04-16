#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	if(argc < 7){
		cerr << "Usage: " << argv[0] << " INPUT_FILE ASSIGNMENT_FILE OUTPUT_FILE ALPHA BETA GAMMA" << endl;
		return 0;
	}

	string input_file = argv[1];
	string assignment_file = argv[2];
	string output_file = argv[3];
	double alpha = atof(argv[4]);
	double beta = atof(argv[5]);
	double gamma = atof(argv[6]);

	Process p;
	p.read_preprocessed_data(input_file);
	p.read_assignment_data(assignment_file);
	p.calc_cut_cost(alpha, beta, gamma);
	p.calc_clique_cost(alpha, beta, gamma);
	p.write_assignment_costs(output_file);
	return 0;
}

