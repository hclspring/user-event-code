#include <unistd.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <igraph.h>

#include "RunnerManager.h"
#include "Runner.h"
//#include "step_test.h"
#include "Constant.h"
#include "Parameter.h"

int main(int argc, char** argv) {
	srand(time(NULL));

	if (argc < 2) {
		return RunnerManager::help();
	}

	RunnerPtr runner = RunnerManager::instance()->get_runner(std::string(argv[1]));
	if (runner == NULL) {
		return RunnerManager::help();
	}

	Parameter para(argc - 1, argv + 1, runner->get_short_options().c_str(), runner->get_long_options());
	if (para.get_help()) {
		runner->help();
	} else {
		runner->run(para);
	}

	return 0;
}
