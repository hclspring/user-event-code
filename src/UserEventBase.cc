#include "UserEventBase.h"

using namespace std;

UserEventBase::UserEventBase(){
}

UserEventBase::UserEventBase(int id){
	set_id(id);
}

UserEventBase::~UserEventBase(){
	attr.clear();
}

int UserEventBase::get_id() const {
	return id;
}

std::vector<double> UserEventBase::get_attr() const {
	return attr;
}

double UserEventBase::get_xpos() const {
	return xpos;
}

double UserEventBase::get_ypos() const {
	return ypos;
}

int UserEventBase::get_upper_capacity() const {
	return upper_capacity;
}

int UserEventBase::get_area() const {
	return area;
}


void UserEventBase::set_id(int id){
	this->id = id;
}

void UserEventBase::set_attr(const std::vector<double> & attr){
	this->attr = attr;
}

void UserEventBase::set_xpos(double xpos){
	this->xpos = xpos;
}

void UserEventBase::set_ypos(double ypos){
	this->ypos = ypos;
}

void UserEventBase::set_upper_capacity(int upper_capacity){
	this->upper_capacity = upper_capacity;
}

void UserEventBase::set_area(int area) {
	this->area = area;
}





