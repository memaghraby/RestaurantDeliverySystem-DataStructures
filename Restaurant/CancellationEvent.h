#ifndef __CANCELLATION_EVENT_H_
#define __CANCELLATION_EVENT_H_

#include"Events\Event.h"


//class for the Cancellation event
class CancellationEvent: public Event
{
private:

public:
	CancellationEvent(int eTime, int oID);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif