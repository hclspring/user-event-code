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
	int area;
//	std::set<int> assigned_users_indices;

public:
	UserEventBase();
	UserEventBase(int id);
	~UserEventBase();

public:
	int get_id() const;
	std::vector<double> get_attr() const;
	double get_xpos() const;
	double get_ypos() const;
	int get_upper_capacity() const;
	int get_area() const;

public:
	void set_id(int id);
	void set_attr(const std::vector<double> & attr);
	void set_xpos(double xpos);
	void set_ypos(double ypos);
	void set_upper_capacity(int upper_capacity);
	void set_area(int area);
};

#endif
