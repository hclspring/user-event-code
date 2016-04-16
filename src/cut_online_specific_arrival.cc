#include <ctime>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	srand(time(NULL));
	Process proc;
	string input_file, output_file, arrival_file;

	// read parameters
	if (argc < 4) {
		cout << "Usage: " << argv[0] << " InputFile ArrivalFile OutputFile" << endl;
		return -1;
	} else {
		input_file = argv[1];
		arrival_file = argv[2];
		output_file = argv[3];
	}

	proc.read_preprocessed_data(input_file);
	proc.read_users_arrival(arrival_file);
	proc.calc_assignments_cut_online();
	proc.write_assignment_result(output_file);
	return 0;
}
