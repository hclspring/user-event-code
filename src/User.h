#ifndef _USER_H_
#define _USER_H_

#include "UserEventBase.h"

class User : public UserEventBase{
public:
	User() : UserEventBase() {};
	User(int id) : UserEventBase(id) {};
	~User(){};

};

#endif
