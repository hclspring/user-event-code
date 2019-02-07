#include <iostream>
#include <cstdio>
#include <string>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	if(argc < 7){
		cout << "Usage: " << argv[0] << " INPUTFILE OUTPUTFILE ALPHA BETA GAMMA TYPE" << endl;
		cout << " Note: TYPE has two possible values: cut, or clique." << endl;
		return 0;
	}

	srand(time(NULL));
	string input_file = argv[1];
	string output_file = argv[2];
	double alpha = atof(argv[3]);
	double beta = atof(argv[4]);
	double gamma = atof(argv[5]);
	string type = argv[6];

	Process proc;
	proc.read_preprocessed_data(input_file);
	proc.calc_assignments_annealing_offline(type, alpha, beta, gamma);
	proc.write_assignment_result(output_file);

	return 0;
}
