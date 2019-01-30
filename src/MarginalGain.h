#ifndef _MARGINAL_GAIN_H_
#define _MARGINAL_GAIN_H_

#include <cstdio>

class MarginalGain{
private:
	int user;
	int event;
	double gain;

public:
	MarginalGain(){}
	MarginalGain(int user, int event, double gain);
	MarginalGain(const MarginalGain &m);

	void operator=(const MarginalGain & m);
	bool operator> (const MarginalGain & m2);
	bool operator< (const MarginalGain & m2);
	static bool compare_asc(const MarginalGain & m1, const MarginalGain & m2);//used for sorting in asc order
	static bool compare_desc(const MarginalGain & m1, const MarginalGain & m2);//used for sorting in desc order

	void set_gain(double gain);

	int get_user() const;
	int get_event() const;
	double get_gain() const;
	void print() const;
};

#endif
