#ifndef _USER_H_
#define _USER_H_

#include <vector>

class User{
private:
//	int id;
	std::vector<double> attr;
	double xpos;
	double ypos;

public:
	User();
//	User(int id);
	~User();

public:
//	int get_id();
	std::vector<double> get_attr();
	double get_xpos();
	double get_ypos();

public:
//	void set_id(int id);
	void set_attr(const std::vector<double> & attr);
	void set_xpos(double xpos);
	void set_ypos(double ypos);
};

#endif
