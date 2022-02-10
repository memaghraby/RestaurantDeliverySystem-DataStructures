#ifndef __PROMOTION_EVENT_H_
#define __PROMOTION_EVENT_H_

#include"Events\Event.h"


//class for the arrival event
class PromotionEvent: public Event
{
   double ExMon;
public:
	PromotionEvent(int eTime, int oID, double eMoney);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function
};

#endif