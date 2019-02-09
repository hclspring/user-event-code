#ifndef _STEP_CALC_MATCH_H_
#define _STEP_CALC_MATCH_H_

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


class StepCalcMatch: public Runner {
private:
	static StepCalcMatch _step_calc_match;

	StepCalcMatch();

public:
	virtual void help();
	virtual int run(const Parameter& para);

private:
	void calc_match(const Parameter& para);
};


#endif // _STEP_CALC_MATCH_H_
