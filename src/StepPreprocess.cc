#include "StepPreprocess.h"

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "unistd.h"

#include "Runner.h"
#include "RunnerManager.h"
#include "Parameter.h"
//#include "undirected_graph.h"
#include "Util.h"
//#include "util_boost.h"
#include "Process.h"

StepPreprocess StepPreprocess::_step_preprocess;

StepPreprocess::StepPreprocess(): Runner() {
	_short_options = "h";
	_long_options = new struct option[100]{
		{"help",						no_argument,		NULL,	OPT_HELP},
		{"input_attribute_file",		required_argument,	NULL,	OPT_INPUT_ATTRIBUTE_FILE},
		{"input_user_capacity_file",	required_argument,	NULL,	OPT_INPUT_USER_CAPACITY_FILE},
		{"input_event_capacity_file",	required_argument,	NULL,	OPT_INPUT_EVENT_CAPACITY_FILE},
		{"input_user_location_file",	required_argument,	NULL,	OPT_INPUT_USER_LOCATION_FILE},
		{"input_event_location_file",	required_argument,	NULL,	OPT_INPUT_EVENT_LOCATION_FILE},
		{"input_event_conflict_file",	required_argument,	NULL,	OPT_INPUT_EVENT_CONFLICT_FILE},
		{"output_file",					required_argument,	NULL,	OPT_OUTPUT_FILE},
		{NULL,			0,					NULL,  0 } //must end with {0, 0, 0, 0}
	};
	RunnerManager::instance()->install("preprocess", this);
}

void StepPreprocess::help() {
	std::cout << "\nFunctionality: Preprocess input files with different data, and write a new input file with overall information.";
	std::cout << "Option list:\n";
	std::cout << "\t* --help (or -h): [ no argument ] print this help information.\n";
	std::cout << "\t* --input_attribute_file: [ string argument ] the input attribute file of the problem.\n";
	std::cout << "\t* --input_user_capacity_file: [ string argument ] the input user capacity file of the problem.\n";
	std::cout << "\t* --input_event_capacity_file: [ string argument ] the input event capacity file of the problem.\n";
	std::cout << "\t* --input_user_location_file: [ string argument ] the input user location file of the problem.\n";
	std::cout << "\t* --input_event_location_file: [ string argument ] the input event location file of the problem.\n";
	std::cout << "\t* --input_event_conflict_file: [ string argument ] the input event conflict file of the problem.\n";
	std::cout << "\t* --output_file: [ string argument ] output preprocessed file of this problem.\n";
	std::cout << std::endl;
}

int StepPreprocess::run(const Parameter& para) {
	preprocess(para);
	return 0;
}

void StepPreprocess::preprocess(const Parameter& para) {
	Process p;
	p.read_attr_file(para.get_input_attribute_file());
	p.read_user_capacity_file(para.get_input_user_capacity_file());
	p.read_event_capacity_file(para.get_input_event_capacity_file());
	p.read_user_pos_file(para.get_input_user_location_file());
	p.read_event_pos_file(para.get_input_event_location_file());
	p.read_conflict_events_file(para.get_input_event_conflict_file());
	p.calc_input_content();
	p.write_preprocessed_data(para.get_output_file());
	return;
}


