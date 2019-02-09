#ifndef _STEP_CALC_COST_H_
#define _STEP_CALC_COST_H_

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


class StepCalcCost: public Runner {
private:
	static StepCalcCost _step_calc_cost;

	StepCalcCost();

public:
	virtual void help();
	virtual int run(const Parameter& para);

private:
	void get_calc_assignment_cost(const Parameter& para);
};


#endif // _STEP_CALC_COST_H_
