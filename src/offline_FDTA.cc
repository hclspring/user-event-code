#include <ctime>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	srand(time(NULL));
	Process proc;
	string input_file, output_dir;
	double alpha;

	// read parameters
	if (argc < 4) {
		cout << "Usage: " << argv[0] << " InputFile Alpha OutputDir" << endl;
		return -1;
	} else {
		input_file = argv[1];
		alpha = atof(argv[2]);
		output_dir = argv[3];
	}

	proc.read_preprocessed_data(input_file);
	proc.calc_matches_offline_FDTA(alpha);
	string output_file = output_dir;
	output_file.append("/assignment.alpha").append(to_string(alpha)).append(".txt");
	proc.write_match_result(output_file, alpha);
	return 0;
}
