#ifndef _RUNNER_MANAGER_H_
#define _RUNNER_MANAGER_H_

#include <iostream>
#include <string>
#include <map>

class Runner;
typedef Runner* RunnerPtr;

class RunnerManager {
private:
	std::map<std::string, RunnerPtr> _runners;

public:
	// 根据命令返回适用的runner
	RunnerPtr get_runner(const std::string& name) const {
		return _runners.find(name) == _runners.end() ? NULL : _runners.find(name)->second;
	}

	void install(const std::string& name, RunnerPtr p) {
		_runners.insert(std::make_pair(name, p));
	}

	static RunnerManager* instance() {
		static RunnerManager manager;
		return &manager;
	}

	static int help() {
		std::cout << "\nUsage: ./usereventjob JOBNAME [OPTIONS]\n";
		std::cout << "\tPossible values of JOBNAME are:\n";
		std::cout << "\t* preprocess: preprocess multiple files as input, and give a resulting input file for further problem solvement.\n";
		std::cout << "\t* calc_assignment: solve problems regarding to assignment (multiple users <-> 1 event).\n";
		std::cout << "\t* calc_match: solve problems regarding to match (multiple users <-> multiple events).\n";
		std::cout << "\t* calc_cost: calculate cost of the resulting assignment.\n";
		std::cout << "For help information of any JOBNAME, use the command:\n";
		std::cout << "\t\t ./usereventjob JOBNAME -h\n";
		std::cout << "or\n";
		std::cout << "\t\t ./usereventjob JOBNAME --help\n";
		std::cout << std::endl;
		return 1;
	}

};

#endif // _RUNNER_MANAGER_H_
