#include "StepCalcAssignment.h"

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

StepCalcAssignment StepCalcAssignment::_step_calc_assignment;

StepCalcAssignment::StepCalcAssignment(): Runner() {
	_short_options = "h";
	_long_options = new struct option[100]{
			{"help",					no_argument,		NULL,	OPT_HELP},
			{"input_file",				required_argument,	NULL,	OPT_INPUT_FILE},
			{"input_user_arrival_file",	required_argument,	NULL,	OPT_INPUT_USER_ARRIVAL_FILE},
			{"online",					no_argument,	NULL,	OPT_ONLINE},
			{"offline",					no_argument,	NULL,	OPT_OFFLINE},
			{"target_function",			required_argument,	NULL,	OPT_TARGET_FUNCTION},
			{"algorithm",				required_argument,	NULL,	OPT_ALGORITHM},
			{"output_file",				required_argument,	NULL,	OPT_OUTPUT_FILE},
			{NULL,			0,					NULL,  0 } //must end with {0, 0, 0, 0}
	};
	RunnerManager::instance()->install("calc_assignment", this);
}

void StepCalcAssignment::help() {
	std::cout << "\nFunctionality: Calculate assignment of users to events with preprocess file and some configurations.";
	std::cout << "Option list:\n";
	std::cout << "\t* --help (or -h): [ no argument ] print this help information.\n";
	std::cout << "\t* --input_file: [ string argument ] the input preprocess file of the problem.\n";
	std::cout << "\t* --online: [ no argument ] denote the problem is online (the default configuration is offline). This should NOT appear together with \"--offline\".\n";
	std::cout << "\t* --offline: [ no argument ] denote the problem is offline (the default configuration is offline). This should NOT appear together with \"--online\".\n";
	std::cout << "\t* --input_user_arrival_file: [ string argument ] the input user arrival file of the problem. This is ONLY USEFUL in online case, and should NOT appear together with \"--count\". Default value is an empty string.\n";
	std::cout << "\t* --count: [ int argument ] denote the number of different user arrival orders generated randomly. This is ONLY USEFUL in online case, and should NOT appear together with \"--input_user_arrival_file\". Default value is 1.\n";
	std::cout << "\t* --target_function: [ string argument ] the target function of the problem. Only two arguments are available: CLIQUE, and CUT.\n";
	std::cout << "\t* --algorithm: [ string argument ] the algorithm to solve the problem. Three algorithms: GREEDY, EXHAUSTIVE, and SA (Simulated Annealing). The default algorithm, which is also the one used in online case, is GREEDY.\n";
	std::cout << "\t* --alpha: [ double argument ] argument of EXHAUSTIVE and SA algorithms.\n";
	std::cout << "\t* --beta: [ double argument ] argument of EXHAUSTIVE and SA algorithms.\n";
	std::cout << "\t* --gamma: [ double argument ] argument of EXHAUSTIVE and SA algorithms.\n";
	std::cout << "\t* --output_file: [ string argument ] output assignment file of this problem.\n";
	std::cout << "\t* --output_dir: [ string argument ] output arrival and assignment directory of this problem. This should be used instead of \"--output_file\" when user arrival is generated randomly by this program.\n";
	std::cout << std::endl;
}

int StepCalcAssignment::run(const Parameter& para) {
	calc_assignment(para);
	return 0;
}

void StepCalcAssignment::calc_assignment(const Parameter& para) {
	Process p;
	p.read_preprocessed_data(para.get_input_file());
	TargetFunction tf = para.get_target_function();
	if (tf != CLIQUE && tf != CUT) {
		std::cerr << "The target function is illegal. Only CLIQUE and CUT are allowed." << std::endl;
		return;
	}
	std::string type = (tf == CLIQUE? "clique" : "cut");
	if (para.get_online()) {
		if (para.get_input_user_arrival_file().size() > 0 && para.get_count() == 1) {
			p.read_users_arrival(para.get_input_user_arrival_file());
			p.write_assignment_result(para.get_output_file());
		} else if (para.get_input_user_arrival_file().size() == 0 && para.get_count() > 0) {
			for (int i = 0; i < para.get_count(); ++i) {
				p.gen_rand_arrival();
				std::string out_arrival_file = para.get_output_dir();
				std::string out_assignment_file = para.get_output_dir();
				std::string count_str = std::to_string(i + 1);
				out_arrival_file.append("/arrival_users.").append(count_str).append(".txt");
				out_assignment_file.append("/assignment.").append(count_str).append(".txt");
				p.write_arrival_sequence(out_arrival_file);
				p.write_assignment_result(out_assignment_file);
			}
		}
	} else { // offline case
		switch (para.get_algorithm()) {
			case GREEDY: {
				switch (tf) {
					case CLIQUE:	p.calc_assignments_clique_offline(); break;
					case CUT:		p.calc_assignments_cut_offline(); break;
				}
				break;}
			case EXHAUSTIVE:
				p.calc_assignments_exhaustive_offline(type, para.get_alpha(), para.get_beta(), para.get_gamma());
				break;
			case SA:
				p.calc_assignments_annealing_offline(type, para.get_alpha(), para.get_beta(), para.get_gamma());
				break;
			default:
				std::cerr << "The algorithm is illegal. Only GREEDY, EXHAUSTIVE and SA are allowed." << std::endl;
				return;
		}
		p.write_assignment_result(para.get_output_file());
	}
	return;
}

void StepCalcAssignment::calc_assignment_online_greedy(const Parameter& para, Process& p) {
	p.read_users_arrival(para.get_input_user_arrival_file());
	switch (para.get_target_function()) {
		case CLIQUE:
			p.calc_assignments_clique_online();
			break;
		case CUT:
			p.calc_assignments_cut_online();
			break;
	}
}

