#include <ctime>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	srand(time(NULL));
	Process proc;
	string input_file, output_dir;
	int count = 1;

	// read parameters
	if (argc < 4) {
		cout << "Usage: " << argv[0] << " InputFile Count OutputDIR" << endl;
		return -1;
	} else {
		input_file = argv[1];
		count = atoi(argv[2]);
		output_dir = argv[3];
	}

	proc.read_preprocessed_data(input_file);
	for (int i = 0; i < count; ++i) {
		proc.gen_rand_arrival();
		proc.calc_assignments_cut_online();

		string out_arrival_file = output_dir, out_assignment_file = output_dir;
		string count_str = to_string(i + 1);

		out_arrival_file.append("/arrival_users.").append(count_str).append(".txt");
		out_assignment_file.append("/assignment.").append(count_str).append(".txt");

		proc.write_arrival_sequence(out_arrival_file);
		proc.write_assignment_result(out_assignment_file);
	}
	return 0;
}
