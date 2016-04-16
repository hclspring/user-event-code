#include <string>

#include "Process.h"

using namespace std;

int main(const int argc, const char** argv)
{
	if(argc < 6){
		cout << "Usage: " << argv[0] << " IN_ATTR_FILE IN_EVENT_CAP_FILE IN_USER_LOC_FILE IN_EVENT_LOC_FILE OUT_ALL_FILE" << endl;
		return 0;
	}
	string in_attr_file = argv[1];
	string in_event_cap_file = argv[2];
	string in_user_loc_file = argv[3];
	string in_event_loc_file = argv[4];
	string out_all_file = argv[5];

	Process proc;
	proc.read_attr_file(in_attr_file);
	proc.read_event_capacity_file(in_event_cap_file);
	proc.read_user_pos_file(in_user_loc_file);
	proc.read_event_pos_file(in_event_loc_file);

	proc.calc_input_content();

	proc.write_preprocessed_data(out_all_file);
	return 0;
}

