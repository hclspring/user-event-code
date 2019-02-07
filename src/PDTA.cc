#include <ctime>

#include "Process.h"
#include "Util.h"

using namespace std;

int main(const int argc, const char** argv)
{
	srand(time(NULL));
	Process proc;
	string input_file, output_dir;
	int count = 1;
	double alpha;

	// read parameters
	if (argc < 5) {
		cout << "Usage: " << argv[0] << " InputFile Alpha Count OutputDIR" << endl;
		return -1;
	} else {
		input_file = argv[1];
		alpha = atof(argv[2]);
		count = atoi(argv[3]);
		output_dir = argv[4];
	}

	proc.read_preprocessed_data(input_file);
	vector<double> match_utilities;
	vector<double> running_times;
	for (int i = 0; i < count; ++i) {
		proc.gen_rand_arrival();
		proc.calc_matches_PDTA(alpha);
		running_times.push_back(proc.get_running_time_ms());

		string out_arrival_file = output_dir, out_match_file = output_dir;
		string count_str = to_string(i + 1);

		out_arrival_file.append("/arrival_users.").append(count_str).append(".txt");
		out_match_file.append("/assignment.alpha").append(to_string(alpha)).append(".").append(count_str).append(".txt");

		proc.write_arrival_sequence(out_arrival_file);
		proc.write_match_result(out_match_file, alpha);

		match_utilities.push_back(proc.calc_match_utility(alpha));
	}
	cout << "Utility mean: " << Util::calc_mean(match_utilities) << endl;
	cout << "Running time mean: " << Util::calc_mean(running_times) << " ms" << endl;
	return 0;
}
