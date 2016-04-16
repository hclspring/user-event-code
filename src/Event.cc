#include "Event.h"

using namespace std;

Event::Event(){
}

Event::Event(int id){
	set_id(id);
}

Event::~Event(){
	attr.clear();
}

int Event::get_id(){
	return id;
}

std::vector<double> Event::get_attr(){
	return attr;
}

double Event::get_xpos(){
	return xpos;
}

double Event::get_ypos(){
	return ypos;
}

int Event::get_upper_capacity(){
	return upper_capacity;
}

void Event::set_id(int id){
	this->id = id;
}

void Event::set_attr(const std::vector<double> & attr){
	this->attr = attr;
}

void Event::set_xpos(double xpos){
	this->xpos = xpos;
}

void Event::set_ypos(double ypos){
	this->ypos = ypos;
}

void Event::set_upper_capacity(int upper_capacity){
	this->upper_capacity = upper_capacity;
}






