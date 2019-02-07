#include "Config.h"

Config::Config()
{
	load_config_file();
}

Config::~Config(){}

double Config::get_sa_R(){
	return sa_R;
}

int Config::get_sa_T0(){
	return sa_T0;
}

int Config::get_sa_deltaT(){
	return sa_deltaT;
}

int Config::get_sa_worse_count_th(){
	return sa_worse_count_th;
}

bool Config::load_config_file(){
	std::ifstream ifs(config_filename.c_str());
	if (ifs.fail()) {
		std::cerr << "Read file " << config_filename << " error." << std::endl;
		return false;
	}

	std::string line;
	while(getline(ifs, line, '\n')){
		std::stringstream sstr(line);
		if (line.size() == 0 || line[0] == '#') {
			continue;
		}
		std::string key, value;
		sstr >> key >> value;
		if(key.compare("sa_R") == 0) {
			sa_R = atof(value.c_str());
		} else if(key.compare("sa_T0") == 0) {
			sa_T0 = atoi(value.c_str());
		} else if(key.compare("sa_deltaT") == 0) {
			sa_deltaT = atoi(value.c_str());
		} else if(key.compare("sa_worse_count_th") == 0) {
			sa_worse_count_th = atoi(value.c_str());
		} else {
			std::cerr << "Parameter " << key << " is not accepted." << std::endl;
			return false;
		}
	}

	ifs.close();
	return true;
}

