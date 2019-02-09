#ifndef _STEP_NORMALIZE_H_
#define _STEP_NORMALIZE_H_

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


class StepNormalize: public Runner {
private:
	static StepNormalize _step_normalize;

	StepNormalize();

public:
	virtual void help();
	virtual int run(const Parameter& para);

private:
	void normalize(const Parameter& para);
};


#endif // _STEP_NORMALIZE_H_
