#ifndef _STEP_CALC_ASSIGNMENT_H_
#define _STEP_CALC_ASSIGNMENT_H_

#include <unistd.h>
#include <getopt.h>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <tuple>

#include "Runner.h"

class RunnerManager;
class Parameter;
class Process;


class StepCalcAssignment: public Runner {
private:
	static StepCalcAssignment _step_calc_assignment;

	StepCalcAssignment();

public:
	virtual void help();
	virtual int run(const Parameter& para);

private:
	void calc_assignment(const Parameter& para);
	void calc_assignment_online_greedy(const Parameter& para, Process& p);
};


#endif // _STEP_CALC_ASSIGNMENT_H_
