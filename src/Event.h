#ifndef _Event_H_
#define _Event_H_

#include "UserEventBase.h"

class Event : public UserEventBase{
public:
	Event() : UserEventBase() {};
	Event(int id) : UserEventBase(id) {};
	~Event(){};
};

#endif

