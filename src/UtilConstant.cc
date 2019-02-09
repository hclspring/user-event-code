#include "UtilConstant.h"

#include <iostream>
//#include <boost/algorithm/string/case_conv.hpp>
#include "Util.h"

Problem UtilConstant::toProblem(const std::string& val) {
	std::string lowercase = Util::to_lower_copy(val);
	if (lowercase.compare("calc_cost") == 0) {
		return CALC_COST;
	} else if (lowercase.compare("preprocess") == 0) {
		return PREPROCESS;
	} else if (lowercase.compare("calc_assignment") == 0) {
		return CALC_ASSIGNMENT;
	} else if (lowercase.compare("calc_match") == 0) {
		return CALC_MATCH;
	} else {
		std::cerr << "Error parsing string: " << val << std::endl;
		exit(-1);
	}
}

TargetFunction UtilConstant::toTargetFunction(const std::string& val) {
	std::string lowercase = Util::to_lower_copy(val);
	if (lowercase.compare("clique") == 0) {
		return CLIQUE;
	} else if (lowercase.compare("cut") == 0) {
		return CUT;
	} else if (lowercase.compare("clique_and_cut") == 0) {
		return CLIQUE_AND_CUT;
	} else if (lowercase.compare("match") == 0) {
		return MATCH;
	} else {
		std::cerr << "Error parsing string: " << val << std::endl;
		exit(-1);
	}
}

Algorithm UtilConstant::toAlgorithm(const std::string& val) {
	std::string lowercase = Util::to_lower_copy(val);
	if (lowercase.compare("exhaustive") == 0) {
		return EXHAUSTIVE;
	} else if (lowercase.compare("sa") == 0) {
		return SA;
	} else if (lowercase.compare("greedy") == 0) {
		return GREEDY;
	} else if (lowercase.compare("fgreedy") == 0) {
		return FGREEDY;
	} else if (lowercase.compare("fdta") == 0) {
		return FDTA;
	} else if (lowercase.compare("pdta") == 0) {
		return PDTA;
	} else {
		std::cerr << "Error parsing string: " << val << std::endl;
		exit(-1);
	}
}

bool UtilConstant::toBool(const std::string& val) {
	std::string lowercase = Util::to_lower_copy(val);
	if (lowercase.compare("true") == 0) {
		return true;
	} else {
		return false;
	}
}

OptionKey UtilConstant::int2OptionKey(const int& val) {
	std::vector<OptionKey> vec = {
		OPT_HELP, // 'h'
		OPT_INPUT_FILE,
		OPT_INPUT_ATTRIBUTE_FILE,
		OPT_INPUT_USER_CAPACITY_FILE,
		OPT_INPUT_EVENT_CAPACITY_FILE,
		OPT_INPUT_USER_LOCATION_FILE,
		OPT_INPUT_EVENT_LOCATION_FILE,
		OPT_INPUT_EVENT_CONFLICT_FILE,
		OPT_INPUT_USER_ARRIVAL_FILE,
		OPT_INPUT_ASSIGNMENT_FILE,
		OPT_OUTPUT_FILE,
		OPT_OUTPUT_DIR,
		OPT_ONLINE,
		OPT_OFFLINE,
		OPT_COUNT,
		OPT_ALPHA,
		OPT_BETA,
		OPT_GAMMA,
		OPT_PROBLEM,
		OPT_TARGET_FUNCTION,
		OPT_ALGORITHM
		/*
		OPT_NET_TYPE,
		OPT_NET_INROOT,
		OPT_NET_INJSON,
		OPT_NET_VOLUNTEERS,
		OPT_OUT_DIR,
		OPT_PART_STR_LENGTH,
		OPT_DISEASE,
		OPT_INFECT_RATE,
		OPT_INFECT_RATE_SECONDS,
		OPT_INFECTIOUS_RATE,
		OPT_INFECTIOUS_RATE_SECONDS,
		OPT_RECOVER_RATE,
		OPT_RECOVER_RATE_SECONDS,
		OPT_SECONDS_PER_WEIGHT,
		OPT_SECONDS_PER_STEP,
		OPT_SOURCE_COUNT,
		OPT_SNAPSHOT_COVERAGE,
		OPT_MAX_SIM_DAYS,
		OPT_REPEAT_TIMES,
		OPT_SRC_IDN_METHOD,
		OPT_UB_R,
		OPT_SRC_IDN_KNOWNTIME,
		OPT_START_PART,
		OPT_END_PART,
		OPT_LAST_PARTS_THRESHOLD,
		OPT_CALC_EDGES,
		OPT_NET_FRIENDSHIP,
		OPT_FD_FUNC,
		OPT_EVOLVE_PARA_ALPHA,
		OPT_EVOLVE_PARA_A,
		OPT_EVOLVE_PARA_B,
		OPT_IF,
		OPT_IE,
		OPT_MERGE_PARTS
		*/
	};
	if (val >= 'h' && val < 'h' + vec.size()) {
		return vec[val - 'h'];
	} else {
		std::cerr << "Error: unknown OptionKey." << std::endl;
		exit(-1);
	}
}

/*
DiseaseStage UtilConstant::int2DiseaseStage(const int& val) {
	switch (val) {
		case 0: return SUSCEPTIBLE;
		case 1: return EXPOSED;
		case 2: return INFECTIOUS;
		case 3: return RECOVERED;
		default: std::cerr << "Error: unknown DiseaseStage." << std::endl; exit(-1);
	}
}

bool UtilConstant::canBeInfected(const DiseaseStage& stage) {
	return stage == SUSCEPTIBLE;
}

bool UtilConstant::isInfected(const DiseaseModel& disease, const DiseaseStage& stage) {
	switch (stage) {
		case INFECTIOUS: return true;
		case EXPOSED:
			 switch (disease) {
				 case SI:
				 case SIR:
				 case SIS:
					 return false;
				 case SEIR:
					 return true;
				 default:
					 std::cerr << "Error: unknown DiseaseModel." << std::endl;
					 exit(-1);
			 }
		default: return false;
	}
}

bool UtilConstant::isInfectious(const DiseaseModel& disease, const DiseaseStage& stage) {
	return stage == INFECTIOUS;
}

bool UtilConstant::hasBeenInfected(const DiseaseModel& disease, const DiseaseStage& stage) {
	switch (disease) {
		case SI: if (stage == INFECTIOUS) return true; else return false;
		case SIR: if (stage == INFECTIOUS || stage == RECOVERED) return true; else return false;
		case SIS: if (stage == INFECTIOUS) return true; else return false;
		case SEIR: if (stage == EXPOSED || stage == INFECTIOUS || stage == RECOVERED) {
					   return true;
				   } else {
					   return false;
				   }
		default:
			std::cerr << "Error: unknown DiseaseModel." << std::endl;
			exit(-1);
	}
}

std::vector<DiseaseStage> UtilConstant::getUnstableStages(const DiseaseModel& disease) {
	std::vector<DiseaseStage> res;
	switch (disease) {
		case SI:
		case SIS:
		case SIR:
			res.push_back(INFECTIOUS); break;
		case SEIR:
			res.push_back(INFECTIOUS); res.push_back(EXPOSED); break;
		default:
			std::cerr << "Error: unknown DiseaseModel." << std::endl;
			exit(-1);
	}
	return res;
}

bool UtilConstant::isStable(
		const DiseaseModel& disease, 
		const std::vector<DiseaseStage>& stages, 
		const std::vector<DiseaseStage>& unstable_stages) {
	for (int i = 0; i < stages.size(); ++i) {
		if (Util::contains(unstable_stages, stages[i])) {
			return false;
		}
	}
	return true;
}

DiseaseStage UtilConstant::getInitialInfectedStage(const DiseaseModel& disease) {
	switch (disease) {
		case SI:
		case SIS:
		case SIR:
			return INFECTIOUS;
		case SEIR:
			return EXPOSED;
		default:
			std::cerr << "Error: unknown disease." << std::endl;
			exit(-1);
	}
}
*/
