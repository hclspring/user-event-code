#include "Parameter.h"

#include <string>
//#include <boost/lexical_cast.hpp>
#include "Util.h"
#include "UtilConstant.h"
#include "Constant.h"

Parameter::Parameter() {}

Parameter::Parameter(const Parameter& para) {
	this->_help = para._help;
	this->_input_file = para._input_file;
	this->_input_attribute_file = para._input_attribute_file;
	this->_input_user_capacity_file = para._input_user_capacity_file;
	this->_input_event_capacity_file = para._input_event_capacity_file;
	this->_input_user_location_file = para._input_user_location_file;
	this->_input_event_location_file = para._input_event_location_file;
	this->_input_event_conflict_file = para._input_event_conflict_file;
	this->_input_user_arrival_file = para._input_user_arrival_file;
	this->_input_assignment_file = para._input_assignment_file;
	this->_output_file = para._output_file;
	this->_output_dir = para._output_dir;
	this->_online = para._online;
	this->_count = para._count;
	this->_alpha = para._alpha;
	this->_beta = para._beta;
	this->_gamma = para._gamma;
	this->_problem = para._problem;
	this->_target_function = para._target_function;
	this->_algorithm = para._algorithm;
	/*
	this->_net_type = para._net_type;
	this->_net_inroot = para._net_inroot;
	this->_net_injson = para._net_injson;
	this->_net_volunteers = para._net_volunteers;
	this->_out_dir = para._out_dir;
	this->_part_str_length = para._part_str_length;
	this->_disease = para._disease;
	this->_infect_rate = para._infect_rate;
	this->_infect_rate_seconds = para._infect_rate_seconds;
	this->_infectious_rate = para._infectious_rate;
	this->_infectious_rate_seconds = para._infectious_rate_seconds;
	this->_recover_rate = para._recover_rate;
	this->_recover_rate_seconds = para._recover_rate_seconds;
	this->_seconds_per_weight = para._seconds_per_weight;
	this->_seconds_per_step = para._seconds_per_step;
	this->_source_count = para._source_count;
	this->_max_sim_days = para._max_sim_days;
	this->_snapshot_coverage = para._snapshot_coverage;
	this->_repeat_times = para._repeat_times;
	this->_source_identification_method = para._source_identification_method;
	this->_ub_r = para._ub_r;
	this->_source_identification_knowntime = para._source_identification_knowntime;
	this->_start_part = para._start_part;
	this->_end_part = para._end_part;
	this->_last_parts_threshold = para._last_parts_threshold;
	this->_calc_edges = para._calc_edges;
	this->_net_friendship = para._net_friendship;
	this->_fd_func = para._fd_func;
	this->_evolve_para_alpha = para._evolve_para_alpha;
	this->_evolve_para_a = para._evolve_para_a;
	this->_evolve_para_b = para._evolve_para_b;
	this->_if = para._if;
	this->_ie = para._ie;
	this->_merge_parts = para._merge_parts;
	*/
}

Parameter::Parameter(int argc, char*const* argv, 
		const char* shortopts, const struct option* longopts) {
	int opt_key;
	while ((opt_key = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
		if (optarg != NULL) {
			set_para(UtilConstant::int2OptionKey(opt_key), std::string(optarg));
		} else {
			set_para(UtilConstant::int2OptionKey(opt_key));
		}
	}
}

int Parameter::set_para(OptionKey opt_key, const std::string& opt_val) {
	switch (opt_key) {
		case OPT_INPUT_FILE:				_input_file = opt_val; return 0;
		case OPT_INPUT_ATTRIBUTE_FILE:		_input_attribute_file = opt_val; return 0;
		case OPT_INPUT_USER_CAPACITY_FILE:	_input_user_capacity_file = opt_val; return 0;
		case OPT_INPUT_EVENT_CAPACITY_FILE:	_input_event_capacity_file = opt_val; return 0;
		case OPT_INPUT_USER_LOCATION_FILE:	_input_user_location_file = opt_val; return 0;
		case OPT_INPUT_EVENT_LOCATION_FILE:	_input_event_location_file = opt_val; return 0;
		case OPT_INPUT_USER_ARRIVAL_FILE:	_input_user_arrival_file = opt_val; return 0;
		case OPT_INPUT_ASSIGNMENT_FILE:		_input_assignment_file = opt_val; return 0;
		case OPT_OUTPUT_FILE:				_output_file = opt_val; return 0;
		case OPT_OUTPUT_DIR:				_output_dir = opt_val; return 0;
		case OPT_COUNT:						_count = std::stoi(opt_val); return 0;
		case OPT_ALPHA:						_alpha = std::stof(opt_val); return 0;
		case OPT_BETA:						_beta = std::stof(opt_val); return 0;
		case OPT_GAMMA:						_gamma = std::stof(opt_val); return 0;
		case OPT_PROBLEM:					_problem = UtilConstant::toProblem(opt_val); return 0;
		case OPT_TARGET_FUNCTION:			_target_function = UtilConstant::toTargetFunction(opt_val); return 0;
		case OPT_ALGORITHM:					_algorithm = UtilConstant::toAlgorithm(opt_val); return 0;
		default:							return -1;
	}
}

int Parameter::set_para(OptionKey opt_key) {
	switch (opt_key) {
		case OPT_HELP:			_help = true; return 0;
		case OPT_ONLINE:		_online = true; return 0;
		case OPT_OFFLINE:		_online = false; return 0;
		default:				return -1;
	}
}

/*
int Parameter::set_help() {
	_help = true;
	return 0;
}
int Parameter::set_input_file(const std::string& val) {
	_input_file = val;
	return 0;
}
int Parameter::set_input_attribute_file(const std::string& val) {
	_input_attribute_file = val;
	return 0;
}
int Parameter::set_input_user_capacity_file(const std::string& val) {
	_input_user_capacity_file = val;
	return 0;
}
int Parameter::set_net_volunteers(const std::string& val) {
	_net_volunteers = val;
	return 0;
}
int Parameter::set_out_dir(const std::string& val) {
	_out_dir = val;
	return 0;
}
int Parameter::set_part_str_length(const std::string& val) {
//	_part_str_length = std::stoi(val);
	_part_str_length = boost::lexical_cast<int>(val);
	return 0;
}
int Parameter::set_disease(const std::string& val) {
	_disease = UtilConstant::toDiseaseModel(val);
	return 0;
}
int Parameter::set_infect_rate(const std::string& val) {
	_infect_rate = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_infect_rate_seconds(const std::string& val) {
	_infect_rate_seconds = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_infectious_rate(const std::string& val) {
	_infectious_rate = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_infectious_rate_seconds(const std::string& val) {
	_infectious_rate_seconds = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_recover_rate(const std::string& val) {
	_recover_rate = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_recover_rate_seconds(const std::string& val) {
	_recover_rate_seconds = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_seconds_per_weight(const std::string& val) {
	_seconds_per_weight = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_seconds_per_step(const std::string& val) {
	_seconds_per_step = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_source_count(const std::string& val) {
	_source_count = boost::lexical_cast<int>(val);
	return 0;
}
int Parameter::set_max_sim_days(const std::string& val) {
	_max_sim_days = boost::lexical_cast<int>(val);
	return 0;
}
int Parameter::set_snapshot_coverage(const std::string& val) {
	_snapshot_coverage = boost::lexical_cast<double>(val);
	return 0;
}
int Parameter::set_repeat_times(const std::string& val) {
	_repeat_times = boost::lexical_cast<int>(val);
	return 0;
}
int Parameter::set_source_identification_method(const std::string& val) {
	_source_identification_method = UtilConstant::toSrcIdnMethod(val);
	return 0;
}
int Parameter::set_ub_r(const std::string& val) {
	_ub_r = boost::lexical_cast<int>(val);
	return 0;
}
int Parameter::set_source_identification_knowntime(const std::string& val) {
	_source_identification_knowntime = UtilConstant::toBool(val);
	return 0;
}
int Parameter::set_start_part(const std::string& val) {
//	_start_part = Util::getPartString(std::stoi(val), _part_str_length);
	_start_part = std::stoi(val);
	return 0;
}
int Parameter::set_end_part(const std::string& val) {
//	_end_part = Util::getPartString(std::stoi(val), _part_str_length);
	_end_part = std::stoi(val);
	return 0;
}
int Parameter::set_last_parts_threshold(const std::string& val) {
	_last_parts_threshold = boost::lexical_cast<int>(val);
	return 0;
}
int Parameter::set_calc_edges() {
	_calc_edges = true;
	return 0;
}
int Parameter::set_net_friendship(const std::string& val) {
	_net_friendship = val;
	return 0;
}
int Parameter::set_fd_func(const std::string& val) {
	_fd_func = val;
	return 0;
}
int Parameter::set_evolve_para_alpha(const std::string& val) {
	_evolve_para_alpha = std::stod(val);
	return 0;
}

int Parameter::set_evolve_para_a(const std::string& val) {
	_evolve_para_a = std::stod(val);
	return 0;
}

int Parameter::set_evolve_para_b(const std::string& val) {
	_evolve_para_b = std::stod(val);
	return 0;
}

int Parameter::set_if(const std::string& val) {
	_if = val;
	return 0;
}

int Parameter::set_ie(const std::string& val) {
	_ie = val;
	return 0;
}

int Parameter::set_merge_parts(const std::string& val) {
	_merge_parts = std::stoi(val);
	return 0;
}



int Parameter::set_net_type(const NetType& net_type) {
	this->_net_type = net_type;
	return 0;
}
int Parameter::set_part_str_length(const int& part_str_length) {
	this->_part_str_length = part_str_length;
	return 0;
}
int Parameter::set_disease(const DiseaseModel& disease) {
	this->_disease = disease;
	return 0;
}
int Parameter::set_infect_rate(const double& infect_rate) {
	this->_infect_rate = infect_rate;
	return 0;
}
int Parameter::set_infect_rate_seconds(const double& infect_rate_seconds) {
	this->_infect_rate_seconds = infect_rate_seconds;
	return 0;
}
int Parameter::set_infectious_rate(const double& infectious_rate) {
	this->_infectious_rate = infectious_rate;
	return 0;
}
int Parameter::set_infectious_rate_seconds(const double& infectious_rate_seconds) {
	this->_infectious_rate_seconds = infectious_rate_seconds;
	return 0;
}
int Parameter::set_recover_rate(const double& recover_rate) {
	this->_recover_rate = recover_rate;
	return 0;
}
int Parameter::set_recover_rate_seconds(const double& recover_rate_seconds) {
	this->_recover_rate_seconds = recover_rate_seconds;
	return 0;
}
int Parameter::set_seconds_per_weight(const double& seconds_per_weight) {
	this->_seconds_per_weight = seconds_per_weight;
	return 0;
}
int Parameter::set_seconds_per_step(const double& seconds_per_step) {
	this->_seconds_per_step = seconds_per_step;
	return 0;
}
int Parameter::set_source_count(const int& source_count) {
	this->_source_count = source_count;
	return 0;
}
int Parameter::set_max_sim_days(const int& max_sim_days) {
	this->_max_sim_days = max_sim_days;
	return 0;
}
int Parameter::set_snapshot_coverage(const double& snapshot_coverage) {
	this->_snapshot_coverage = snapshot_coverage;
	return 0;
}
int Parameter::set_repeat_times(const int& repeat_times) {
	this->_repeat_times = repeat_times;
	return 0;
}
int Parameter::set_source_identification_method(const SrcIdnMethod& method) {
	this->_source_identification_method = method;
	return 0;
}
int Parameter::set_ub_r(const double& ub_r) {
	this->_ub_r = ub_r;
	return 0;
}
int Parameter::set_source_identification_knowntime(const bool& knowntime) {
	this->_source_identification_knowntime = knowntime;
	return 0;
}
int Parameter::set_start_part(const int& start_part) {
	this->_start_part = start_part;
	return 0;
}
int Parameter::set_end_part(const int& end_part) {
	this->_end_part = end_part;
	return 0;
}
int Parameter::set_last_parts_threshold(const int& last_parts_threshold) {
	this->_last_parts_threshold = last_parts_threshold;
	return 0;
}
int Parameter::set_evolve_para_alpha(const double& evolve_para_alpha) {
	this->_evolve_para_alpha = evolve_para_alpha;
	return 0;
}
int Parameter::set_evolve_para_a(const double& evolve_para_a) {
	this->_evolve_para_a = evolve_para_a;
	return 0;
}
int Parameter::set_evolve_para_b(const double& evolve_para_b) {
	this->_evolve_para_b = evolve_para_b;
	return 0;
}
int Parameter::set_merge_parts(const int& merge_parts) {
	this->_merge_parts = merge_parts;
	return 0;
}
*/


