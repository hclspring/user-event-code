#ifndef _GAIN_MATRIX_H_
#define _GAIN_MATRIX_H_

#include <vector>

class GainMatrix{
private:
	std::vector<std::vector<bool> > inheap_matrix; // out: user; in: event
	std::vector<std::vector<double> > gain_matrix; // out: user, in: event

	double value_maxgain;
	int user_maxgain;
	int event_maxgain;

public:
	GainMatrix();
	~GainMatrix();

	void initialize(int num_users, int num_events);
	void update(int user, int event, double gain);
	void pop_maximum(int & user, int & event, double & gain);
};


#endif
