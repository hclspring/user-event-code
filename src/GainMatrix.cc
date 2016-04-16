#include "GainMatrix.h"

using namespace std;

GainMatrix::GainMatrix(){}

GainMatrix::~GainMatrix(){}

void GainMatrix::initialize(int num_users, int num_events)
{
	assert(num_users > 0 && num_events > 0);
	inheap_matrix.clear();
	gain_matrix.clear();
	for(int i = 0; i < num_users; i++){
		vector<double> gain_row;
		vector<bool> inheap_row;
		for(int j = 0; j < num_events; j++){
			gain_row.push_back(0);
			inheap_row.push_back(true);
		}
		inheap_matrix.push_back(inheap_row);
		gain_matrix.push_back(gain_row);
	}
	value_maxgain = 0;
	user_maxgain = 0;
	event_maxgain = 0;
}

void GainMatrix::update(int user, int event, double gain)
{
	inheap_matrix.at(user).at(event) = true;
	gain_matrix.at(user).at(event) = gain;
	if(gain > value_maxgain){
		value_maxgain = gain;
		user_maxgain = user;
		event_maxgain = event;
	}
}

void GainMatrix::pop_maximum(int & user, int & event, double & gain){
	inheap_matrix.at(user_maxgain).at(event_maxgain) = false;
}



