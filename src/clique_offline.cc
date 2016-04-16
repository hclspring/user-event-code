#include <iostream>
#include <cstdio>
#include <string>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	if(argc < 3){
		cout << "Usage: " << argv[0] << " INPUTFILE OUTPUTFILE" << endl;
		return 0;
	}

	string input_file = argv[1];
	string output_file = argv[2];

	Process proc;
	proc.read_preprocessed_data(input_file);
	proc.calc_assignments_clique_offline();
	proc.write_assignment_result(output_file);

	return 0;
}
