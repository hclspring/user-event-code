#ifndef _USER_EVENT_BASE_H_
#define _USER_EVENT_BASE_H_

#include <vector>
#include <set>

class UserEventBase{
protected:
	int id;
	std::vector<double> attr;
	double xpos;
	double ypos;
	int upper_capacity;
//	std::set<int> assigned_users_indices;

public:
	UserEventBase();
	UserEventBase(int id);
	~UserEventBase();

public:
	int get_id();
	std::vector<double> get_attr();
	double get_xpos();
	double get_ypos();
	int get_upper_capacity();

public:
	void set_id(int id);
	void set_attr(const std::vector<double> & attr);
	void set_xpos(double xpos);
	void set_ypos(double ypos);
	void set_upper_capacity(int upper_capacity);
};

#endif
