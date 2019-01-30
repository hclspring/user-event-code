#include "MarginalGain.h"


MarginalGain::MarginalGain(int user, int event, double gain){
	this->user = user;
	this->event = event;
	this->gain = gain;
}

MarginalGain::MarginalGain(const MarginalGain &m){
	user = m.user;
	event = m.event;
	gain = m.gain;
}

void MarginalGain::operator=(const MarginalGain &m) {
	user = m.user;
	event = m.event;
	gain = m.gain;
}

bool MarginalGain::operator> (const MarginalGain & m2){
	return this->gain > m2.gain;
}

bool MarginalGain::operator< (const MarginalGain & m2){
	return this->gain < m2.gain;
}

bool MarginalGain::compare_asc(const MarginalGain &m1, const MarginalGain &m2) {
	return m1.gain < m2.gain;
}

bool MarginalGain::compare_desc(const MarginalGain &m1, const MarginalGain &m2) {
	return m1.gain > m2.gain;
}


void MarginalGain::set_gain(double gain){
	this->gain = gain;
}

int MarginalGain::get_user() const {
	return user;
}

int MarginalGain::get_event() const {
	return event;
}

double MarginalGain::get_gain() const {
	return gain;
}

void MarginalGain::print() const {
	printf("user = %d, event = %d, gain = %f\n", user, event, gain);
}
