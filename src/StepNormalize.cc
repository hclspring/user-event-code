#include "StepNormalize.h"

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

StepNormalize StepNormalize::_step_normalize;

StepNormalize::StepNormalize(): Runner() {
	_short_options = "h";
	_long_options = new struct option[100]{
		{"help",			no_argument,		NULL,	OPT_HELP},
		{"input_file",		required_argument,	NULL,	OPT_INPUT_FILE},
		{"output_file",		required_argument,	NULL,	OPT_OUTPUT_FILE},
		{NULL,			0,					NULL,  0 } //must end with {0, 0, 0, 0}
	};
	RunnerManager::instance()->install("normalize", this);
}

void StepNormalize::help() {
	std::cout << "\nFunctionality: Normalize the input file and write the results into the output file.\n";
	std::cout << "Option list:\n";
	std::cout << "\t* --help (or -h): [ no argument ] print this help information.\n";
	std::cout << "\t* --input_file: [ string argument ] an input file which contains what I don't know.\n";
	std::cout << "\t* --output_file: [ string argument ] the output file which contains normalized information of the input file.\n";
	std::cout << std::endl;
}

int StepNormalize::run(const Parameter& para) {
	normalize(para);
	return 0;
}

void StepNormalize::normalize(const Parameter& para) {
	std::ifstream ifs(para.get_input_file().c_str());
	if(ifs.fail()){
		std::cerr << "Read file " << para.get_input_file() << " error." << std::endl;
		return;
	}

	std::ofstream ofs(para.get_output_file().c_str());
	if(ofs.fail()){
		std::cerr << "Write file " << para.get_output_file() << " error." << std::endl;
		return;
	}

	std::string line;
	// Read the first line
	getline(ifs, line, '\n');
	int events, users;
	std::stringstream sstr(line);
	sstr >> events >> users;
	ofs << events << " " << users << std::endl;

	// Read the following 2*users lines
	for(int i = 0; i < 2*users; i++){
		getline(ifs, line, '\n');
		std::stringstream sstr(line);
		double sum = 0.0, num;
		std::vector<double> numbers;
		while(sstr.good()){
			sstr >> num;
			numbers.push_back(num);
			sum += num;
		}
		for(int j = 0; j < numbers.size(); j++){
			if(j > 0){
				ofs << " ";
			}
			ofs << 1.0 * numbers[j] / sum;
		}
		ofs << std::endl;
	}

	while(getline(ifs, line, '\n')){
		ofs << line << std::endl;
	}

	ofs.close();
	ifs.close();
	return;
}


