#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Config{
private:
	std::string config_filename = "config.txt";
	double sa_R;
	int sa_T0;
	int sa_deltaT;
	int sa_worse_count_th;

public:
	Config();
	~Config();

	double get_sa_R();
	int get_sa_T0();
	int get_sa_deltaT();
	int get_sa_worse_count_th();

private:
	bool load_config_file();
};
