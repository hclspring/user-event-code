#ifndef _STEP_PREPROCESS_H_
#define _STEP_PREPROCESS_H_

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


class StepPreprocess: public Runner {
private:
	static StepPreprocess _step_preprocess;

	StepPreprocess();

public:
	virtual void help();
	virtual int run(const Parameter& para);

private:
	void preprocess(const Parameter& para);
};


#endif // _STEP_PREPROCESS_H_
