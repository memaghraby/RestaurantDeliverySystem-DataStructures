#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, int oDistance, double oMoney):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance=oDistance;
	OrdMoney=oMoney;

}

void ArrivalEvent::Execute(Restaurant* pRest)
{

	Order* pOrd = new Order(EventTime,OrderID,OrdType,OrdRegion, OrdDistance, OrdMoney);
	pRest->AddArrivalOrder(pOrd);
}
