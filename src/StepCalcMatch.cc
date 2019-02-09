#include "StepCalcMatch.h"

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include "unistd.h"

#include "Runner.h"
#include "RunnerManager.h"
#include "Parameter.h"
//#include "undirected_graph.h"
#include "Util.h"
//#include "util_boost.h"
#include "Process.h"

StepCalcMatch StepCalcMatch::_step_calc_match;

StepCalcMatch::StepCalcMatch(): Runner() {
	_short_options = "h";
	_long_options = new struct option[100]{
			{"help",					no_argument,		NULL,	OPT_HELP},
			{"input_file",				required_argument,	NULL,	OPT_INPUT_FILE},
			{"online",					no_argument,	NULL,	OPT_ONLINE},
			{"offline",					no_argument,	NULL,	OPT_OFFLINE},
			{"algorithm",				required_argument,	NULL,	OPT_ALGORITHM},
			{"alpha",					required_argument,	NULL,	OPT_ALPHA},
			{"output_dir",				required_argument,	NULL,	OPT_OUTPUT_DIR},
			{NULL,			0,					NULL,  0 } //must end with {0, 0, 0, 0}
	};
	RunnerManager::instance()->install("calc_match", this);
}

void StepCalcMatch::help() {
	std::cout << "\nFunctionality: Calculate assignment of users to events with preprocess file and some configurations.";
	std::cout << "Option list:\n";
	std::cout << "\t* --help (or -h): [ no argument ] print this help information.\n";
	std::cout << "\t* --input_file: [ string argument ] the input preprocess file of the problem.\n";
	std::cout << "\t* --online: [ no argument ] denote the problem is online (the default configuration is offline). This should NOT appear together with \"--offline\".\n";
	std::cout << "\t* --offline: [ no argument ] denote the problem is offline (the default configuration is offline). This should NOT appear together with \"--online\".\n";
	std::cout << "\t* --count: [ int argument ] denote the number of different user arrival orders generated randomly. This is ONLY USEFUL in online case, and should NOT appear together with \"--input_user_arrival_file\". Default value is 1.\n";
	std::cout << "\t* --algorithm: [ string argument ] the algorithm to solve the problem. Three algorithms: GREEDY (online), FGREEDY (online), FDTA (offline), PDTA (online). The default algorithm, which is used in online case, is GREEDY.\n";
	std::cout << "\t* --alpha: [ double argument ] argument of target function.\n";
	std::cout << "\t* --output_file: [ string argument ] output match file of this problem. Only USEFUL in offline case.\n";
	std::cout << "\t* --output_dir: [ string argument ] output arrival and assignment directory of this problem. This should be used instead of \"--output_file\" in online case.\n";
	std::cout << std::endl;
}

int StepCalcMatch::run(const Parameter& para) {
	calc_match(para);
	return 0;
}

void StepCalcMatch::calc_match(const Parameter& para) {
	Process p;
	p.read_preprocessed_data(para.get_input_file());
	if (para.get_online()) { // online case
		std::vector<double> match_utilities, running_times;
		for (int i = 0; i < para.get_count(); ++i) {
			p.gen_rand_arrival();
			double theta;
			switch (para.get_algorithm()) {
				case GREEDY:	p.calc_matches_online_greedy(para.get_alpha()); break;
				case FGREEDY:	p.calc_matches_onlineF_greedy(para.get_alpha(), theta); break;
				case PDTA:		p.calc_matches_PDTA(para.get_alpha()); break;
				default:
					std::cerr << "Error: illegal algorithm. Legal algorithms are GREEDY, FGREEDY, and PDTA." << std::endl; return;
			}
			running_times.push_back(p.get_running_time_ms());
			std::string out_arrival_file = para.get_output_dir();
			std::string out_match_file = para.get_output_dir();
			std::string count_str = std::to_string(i + 1);
			out_arrival_file.append("/arrival_users.").append(count_str).append(".txt");
			out_match_file.append("/match.alpha").append(std::to_string(para.get_alpha())).append(".").append(count_str).append(".txt");
			p.write_arrival_sequence(out_arrival_file);
			p.write_match_result(out_match_file, para.get_alpha());
			match_utilities.push_back(p.calc_match_utility(para.get_alpha()));
		}
		std::cout << "Utility mean: " << Util::calc_mean(match_utilities) << std::endl;
		std::cout << "Running time mean: " << Util::calc_mean(running_times) << " ms" << std::endl;
	} else { // offline case
		assert(para.get_algorithm() == FDTA);
		p.calc_matches_offline_FDTA(para.get_alpha());
		p.write_match_result(para.get_output_file(), para.get_alpha());
	}
	return;
}

