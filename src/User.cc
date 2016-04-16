#include "User.h"

User::User(){
}

/*
User::User(int id){
	set_id(id);
}
*/

User::~User(){
	attr.clear();
}

/*
int User::get_id(){
	return id;
}
*/
std::vector<double> User::get_attr(){
	return attr;
}

double User::get_xpos(){
	return xpos;
}

double User::get_ypos(){
	return ypos;
}
/*
void User::set_id(int id){
	this->id = id;
}
*/
void User::set_attr(const std::vector<double> & attr){
	this->attr = attr;
}

void User::set_xpos(double xpos){
	this->xpos = xpos;
}

void User::set_ypos(double ypos){
	this->ypos = ypos;
}






