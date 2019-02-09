#include "StepCalcCost.h"

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

StepCalcCost StepCalcCost::_step_calc_cost;

StepCalcCost::StepCalcCost(): Runner() {
	_short_options = "h";
	_long_options = new struct option[100]{
		{"help",			no_argument,		NULL,	OPT_HELP},
		{"input_file",		required_argument,	NULL,	OPT_INPUT_FILE},
		{"input_assignment_file",	required_argument,	NULL,	OPT_INPUT_ASSIGNMENT_FILE},
		{"output_file",		required_argument,	NULL,	OPT_OUTPUT_FILE},
		{"alpha",			required_argument,	NULL,	OPT_ALPHA},
		{"beta",			required_argument,	NULL,	OPT_BETA},
		{"gamma",			required_argument,	NULL,	OPT_GAMMA},
		{"target_function",	required_argument,	NULL,	OPT_TARGET_FUNCTION},
		{NULL,			0,					NULL,  0 } //must end with {0, 0, 0, 0}
	};
	RunnerManager::instance()->install("calc_cost", this);
}

void StepCalcCost::help() {
	std::cout << "\nFunctionality: Calculate cost of the given assignment file, with target function being CLIQUE or CUT.\n";
	std::cout << "Option list:\n";
	std::cout << "\t* --help (or -h): [ no argument ] print this help information.\n";
	std::cout << "\t* --input_file: [ string argument ] preprocessed input file of the problem.\n";
	std::cout << "\t* --input_assignment_file: [ string argument ] assignment file of the problem, which must be given previously.\n";
	std::cout << "\t* --output_file: [ string argument ] output file of this problem. If this argument is not given, i.e. output_file.size() == 0, then the results will be shown on screen.\n";
	std::cout << "\t* --alpha: [ double argument ] alpha in the target function.\n";
	std::cout << "\t* --beta: [ double argument ] beta in the target function.\n";
	std::cout << "\t* --gamma: [ double argument ] gamma in the target function.\n";
	std::cout << "\t* --target_function: [ string argument ] target function, which has three values here: CLIQUE, or CUT, or CLIQUE_AND_CUT.\n";
	std::cout << std::endl;
}

int StepCalcCost::run(const Parameter& para) {
	get_calc_assignment_cost(para);
	return 0;
}

void StepCalcCost::get_calc_assignment_cost(const Parameter& para) {
	Process p;
	p.read_preprocessed_data(para.get_input_file());
	p.read_assignment_data(para.get_input_assignment_file());
	double cost_clique, cost_cut;
	int type = 0;
	switch (para.get_target_function()) {
		case CLIQUE: {
						type = 1;
						cost_clique = p.calc_clique_cost(para.get_alpha(), para.get_beta(), para.get_gamma());
						break;
					 }
		case CUT:	{
						type = 2;
						cost_cut = p.calc_cut_cost(para.get_alpha(), para.get_beta(), para.get_gamma());
						break;
					}
		case CLIQUE_AND_CUT: {
								type = 3;
								cost_clique = p.calc_clique_cost(para.get_alpha(), para.get_beta(), para.get_gamma());
								cost_cut = p.calc_cut_cost(para.get_alpha(), para.get_beta(), para.get_gamma());
								break;
							 }
		default: {
					 type = -1;
					 std::cerr << "Error: target function must be CLIQUE or CUT." << std::endl;
					 return;
				 }
	}
	if (para.get_output_file().size() > 0) {
		if (type == 1 || type == 2) {
			p.write_assignment_costs(para.get_output_file(), type == 1 ? "clique" : "cut");
		} else if (type == 3) {
			p.write_assignment_costs(para.get_output_file());
		}
	} else {
		if (type == 1 || type == 3) {
			std::cout << "Clique cost is " << cost_clique << std::endl;
		}
		if (type == 2 || type == 3) {
			std::cout << "Cut cost is " << cost_cut << std::endl;
		}
	}
	return;
}


